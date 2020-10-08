#!/bin/bash
#This .sh file copy modified some .cpp files of autoware.
#It is required to make autorunner executable.
#The new .cpp files include modified param section to launch with launch file (not a runtime managaer)
#


### STEP 1 modifing src files
## lidar_localizer [1/4]
echo ""
echo "Replace CMakeLists file in lidar_localizer Pakg"

mv ~/autoware.ai/src/autoware/core_perception/lidar_localizer/CMakeLists.txt ~/autoware.ai/src/autoware/core_perception/lidar_localizer/CMakeLists.txt.origin
cp ~/RUBIS_minicar/Modified_Autoware_src/lidar_localizer/ndt_matching/CMakeLists.txt ~/autoware.ai/src/autoware/core_perception/lidar_localizer


echo "Replace ndt_matching.cpp file to ndt_matching_param.cpp"
echo "Copy ~/RUBIS_minicar/Modified_Autoware_src/lidar_localizer/ndt_matching files to..."
echo "~/autoware.ai/src/autoware/core_perception/lidar_localizer/"

cp ~/RUBIS_minicar/Modified_Autoware_src/lidar_localizer/ndt_matching/ndt_matching_param.cpp ~/autoware.ai/src/autoware/core_perception/lidar_localizer/nodes/ndt_matching

echo "lidar_localizer complete [1/4]"



## op_global_planner [2/4]

echo ""
echo "Replace CMakeLists file in op_global_planner Pakg"
mv ~/autoware.ai/src/autoware/core_planning/op_global_planner/CMakeLists.txt ~/autoware.ai/src/autoware/core_planning/op_global_planner/CMakeLists.txt.origin
cp ~/RUBIS_minicar/Modified_Autoware_src/op_global_planner/CMakeLists.txt ~/autoware.ai/src/autoware/core_planning/op_global_planner


echo "Replace op_global_planner.cpp file to op_global_planner_no_output_core.cpp"

echo "Copy ~/RUBIS_minicar/Modified_Autoware_src/op_global_planner/ files to..."
echo "~/autoware.ai/src/autoware/core_planning/op_global_planner/"

cp ~/RUBIS_minicar/Modified_Autoware_src/op_global_planner/*.cpp ~/autoware.ai/src/autoware/core_planning/op_global_planner/nodes
cp ~/RUBIS_minicar/Modified_Autoware_src/op_global_planner/*.h ~/autoware.ai/src/autoware/core_planning/op_global_planner/include

echo "lidar_localizer complete [2/4]"


## points_downsampler [3/4]

echo ""
echo "Replace CMakeLists file in points_downsampler Pakg"

mv ~/autoware.ai/src/autoware/core_perception/points_downsampler/CMakeLists.txt ~/autoware.ai/src/autoware/core_perception/points_downsampler/CMakeLists.txt.origin
cp ~/RUBIS_minicar/Modified_Autoware_src/points_downsampler/voxel_grid_filter/CMakeLists.txt ~/autoware.ai/src/autoware/core_perception/points_downsampler/


echo "Replace voxel_grid_filter.cpp file to voxel_grid_filter_param.cpp"
echo "Copy ~/RUBIS_minicar/Modified_Autoware_src/points_downsampler files to..."
echo "~/autoware.ai/src/autoware/core_perception/points_downsampler/"


cp ~/RUBIS_minicar/Modified_Autoware_src/points_downsampler/voxel_grid_filter/*.cpp ~/autoware.ai/src/autoware/core_perception/points_downsampler/nodes/voxel_grid_filter

echo "points_downsampler complete [3/4]"



## waypoint_follower [4/4]

echo ""
echo "Replace CMakeLists file in waypoint_follower Pakg"
echo "Replace pure_pursuit.cpp file to pure_pursuit_param.cpp"
echo "Replace twist_cmd.cpp file to twist_cmd_param.cpp"
mv ~/autoware.ai/src/autoware/common/waypoint_follower/CMakeLists.txt ~/autoware.ai/src/autoware/common/waypoint_follower/CMakeLists.txt.origin
cp ~/RUBIS_minicar/Modified_Autoware_src/waypoint_follower/twist_filter/CMakeLists.txt ~/autoware.ai/src/autoware/common/waypoint_follower/


echo "Copy ~/RUBIS_minicar/Modified_Autoware_src/waypoint_follower files to..."
echo "~/autoware.ai/src/autoware/common/waypoint_follower"

cp ~/RUBIS_minicar/Modified_Autoware_src/waypoint_follower/twist_filter/*.cpp ~/autoware.ai/src/autoware/common/waypoint_follower/nodes/twist_filter
cp ~/RUBIS_minicar/Modified_Autoware_src/waypoint_follower/pure_pursuit/*.cpp ~/autoware.ai/src/autoware/common/waypoint_follower/nodes/pure_pursuit
cp ~/RUBIS_minicar/Modified_Autoware_src/waypoint_follower/pure_pursuit/*.h ~/autoware.ai/src/autoware/common/waypoint_follower/nodes/pure_pursuit

echo "waypoint_follower complete [4/4]"

### STEP2 build

echo "STEP 1 complete.... STEP 2 Start"


cd ~/autoware.ai/build

echo ""
echo "build lidar_localizer pakg [1/4]"

cd lidar_localizer
make install
cd ..


echo ""
echo "build op_global_planner pakg [2/4]"

cd op_global_planner
make install
cd ..

echo ""
echo "build points_downsampler pakg [3/4]"

cd points_downsampler
make install
cd ..

echo ""
echo "build waypoint_follower pakg [4/4]"

cd waypoint_follower
make install
cd ..