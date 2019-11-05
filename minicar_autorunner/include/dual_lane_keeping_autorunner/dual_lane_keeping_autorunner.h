#include <ros/ros.h>
#include <ros_autorunner/ros_autorunner.h>

// Include subscribe message type
#include <autoware_msgs/LaneArray.h>
#include <autoware_msgs/Lane.h>
#include <visualization_msgs/MarkerArray.h>
#include <geometry_msgs/TwistStamped.h>
#include <autoware_msgs/NDTStat.h>

#define TOTAL_STEP_NUM 7 // Need to change when total step number is changed
#define LANE_KEEPING_THRESHOLD 0.1

class DualLaneKeepingAutorunner : public AutorunnerBase{
private:    
    ros::NodeHandle     nh_;
    ROSAutorunner        ros_autorunner_;
private:
    virtual void register_subscribers();
private:
    void ndt_stat_cb(const autoware_msgs::NDTStat& msg);
    void lane_waypoints_array_cb(const autoware_msgs::LaneArray& msg);
    void local_trajectories_cb(const autoware_msgs::LaneArray& msg);
    void behavior_state_cb(const visualization_msgs::MarkerArray& msg);
    void twist_raw_cb(const geometry_msgs::TwistStamped& msg);
public:
    Sub_v               sub_v_;
public:
    DualLaneKeepingAutorunner() {}
    DualLaneKeepingAutorunner(ros::NodeHandle nh) : nh_(nh){}
    virtual void Run();
};