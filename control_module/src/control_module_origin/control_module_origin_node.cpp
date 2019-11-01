#include <control_module.h>

int main
(int argc, char* argv[])
{
	ros::init(argc, argv, "control_module_origin");
	
	ControlModule app;
	app.Run();

	return 0;
}
