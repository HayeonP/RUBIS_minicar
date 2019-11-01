#include <lane_keeping_autorunner/lane_keeping_autorunner.h>

int main(int argc, char* argv[]){
    ros::init(argc, argv, "lane_keeping_autorunner");
    ros::NodeHandle nh;

    LaneKeepingAutorunner lane_keeping_autorunner(nh);
    lane_keeping_autorunner.Run();

    return 0;
}