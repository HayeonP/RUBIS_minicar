#include <control_module.h>
#include <math.h>

void ControlModule::twist_cb
(const geometry_msgs::TwistStamped& in_twist)
{
	twist_ = in_twist.twist;
	send_vesc_value();
	return;
}

void ControlModule::get_vesc_value()
	{
		
	twist_vel_ = twist_.linear.x;
	if(zero_cnt_ >= 20) twist_vel_ = 0;
	if(twist_vel_ <= 0.2) {
		zero_cnt_++;
	}
	else zero_cnt_ = 0;

	std::cout<<"Zero count : " << zero_cnt_ << std::endl;
	std::cout<<"Linear velocity : " << twist_vel_ << std::endl;

	speed_ = twist_vel_ * speed_to_erpm_gain_ + speed_to_erpm_offset_; //twist -> vesc(rpm)
	double current_steering_angle;
	current_steering_angle = atan(wheelbase_* twist_.angular.z / twist_.linear.x);
	if(std::isnan(current_steering_angle) == 1 ) current_steering_angle = 0;
	std::cout<<"\n\nAngle : "<<radian_to_degree(current_steering_angle)<<std::endl;
	position_ = current_steering_angle * steering_angle_to_servo_gain_ + steering_angle_to_servo_offset_;
		

}

void ControlModule::get_vesc_value_k()
{
	double twist_pos = twist_.angular.z;
	
	twist_vel_ = twist_.linear.x;


	speed_ = twist_.linear.x * 500; 
	double angle = -1 * radian_to_degree(twist_.angular.z);
	position_ = valMap(angle, -25.0, 25.0, 0.0, 1.0);
	if (position_ > 0.8) position_ = 0.8;
	else if (position_ < 0.2) position_ = 0.2;
}

void ControlModule::send_vesc_value()
{
	if(isKeyboard_)
		get_vesc_value_k();
	else
		get_vesc_value();

	std_msgs::Float64 velocity;
	std_msgs::Float64 position;
	velocity.data = speed_;
	position.data = position_;
	vel_pub_.publish(velocity);
	pos_pub_.publish(position);

	return;
}

double ControlModule::valMap
(double val, double in_min, double in_max, double out_min, double out_max)
{
	return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

double ControlModule::radian_to_degree
(double radian)
{
	return radian * 180 / PI;
}


void ControlModule::Run()
{
	nh_.param<bool>("keybaord", isKeyboard_, false);
	nh_.param<double>("speed_to_erpm_gain", speed_to_erpm_gain_, 0.0);
	nh_.param<double>("speed_to_erpm_offset", speed_to_erpm_offset_, 0.0);
	nh_.param<double>("steering_angle_to_servo_gain", steering_angle_to_servo_gain_, 0.0);
	nh_.param<double>("steering_angle_to_servo_offset", steering_angle_to_servo_offset_, 0.0);
	nh_.param<double>("wheelbase", wheelbase_, 0.25);

	ROS_WARN("Keyboard : %s", isKeyboard_ ? "true" : "false");
	twist_sub_ = nh_.subscribe("/twist_cmd", 10, &ControlModule::twist_cb, this);
	vel_pub_ = nh_.advertise<std_msgs::Float64>("/commands/motor/speed", 10);
	pos_pub_ = nh_.advertise<std_msgs::Float64>("/commands/servo/position", 10);
	twist_ = geometry_msgs::Twist();
	
	ROS_WARN("Control module START ! ");
	ros::spin();
}

