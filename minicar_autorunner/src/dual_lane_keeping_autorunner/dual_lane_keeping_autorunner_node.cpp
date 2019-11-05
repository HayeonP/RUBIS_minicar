#include <dual_lane_keeping_autorunner/dual_lane_keeping_autorunner.h>

int main(int argc, char* argv[]){
    ros::init(argc, argv, "dual_lane_keeping_autorunner");
    ros::NodeHandle nh;

    DualLaneKeepingAutorunner dual_lane_keeping_autorunner(nh);
    dual_lane_keeping_autorunner.Run();

    return 0;
}