#include <ros/ros.h>
#include <geometry_msgs/TwistStamped.h>
#include <std_msgs/Float64.h>
#include <math.h>

#define PI 3.14

class ControlModule{
private:
	ros::NodeHandle nh_;
	ros::Subscriber twist_sub_;
	ros::Publisher vel_pub_;
	ros::Publisher pos_pub_;
	double speed_to_erpm_gain_;
	double speed_to_erpm_offset_;
	double steering_angle_to_servo_gain_;
	double steering_angle_to_servo_offset_;
	double wheelbase_;
	
	bool isKeyboard_;
	double speed_;
	double position_;
	double twist_vel_ = 0;
	int zero_cnt_ = 0;
	geometry_msgs::Twist twist_;

private:
	void twist_cb(const geometry_msgs::TwistStamped& in_twist);
	void get_vesc_value(); // PID control
	void get_vesc_value_k(); // From Keyboard
	void send_vesc_value(); 
	//float control();
	double valMap(double val, double in_min, double in_max, double out_min, double out_max);
	double radian_to_degree(double radian);

public:
	ControlModule(){};
	void Run();
};


