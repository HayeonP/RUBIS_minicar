#include <wf_sim_autorunner/wf_sim_autorunner.h>

int main(int argc, char* argv[]){
    ros::init(argc, argv, "wf_sim_autorunner");
    ros::NodeHandle nh;

    WfSimAutorunner wf_sim_autorunner(nh);
    wf_sim_autorunner.Run();

    return 0;
}