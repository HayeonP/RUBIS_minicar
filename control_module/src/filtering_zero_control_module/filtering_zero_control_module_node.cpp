#include <control_module.h>

int main
(int argc, char* argv[])
{
	ros::init(argc, argv, "filtering_zero_control_module");
	
	ControlModule app;
	app.Run();

	return 0;
}
