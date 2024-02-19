cmake_minimum_required(VERSION 3.8)
project(alw82_ros360_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(rcl_interfaces REQUIRED)
find_package(OpenCV REQUIRED)
find_package(image_transport REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(control_msgs REQUIRED)
find_package(trajectory_msgs REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(moveit_ros_planning_interface REQUIRED)

# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

add_executable(helloWorld src/helloWorld.cpp)
add_executable(examplePublisher src/examplePublisher.cpp)
add_executable(exampleSubscriber src/exampleSubscriber.cpp)
add_executable(randomTurtle src/randomTurtle.cpp)
add_executable(velodyneSubscriber src/velodyneSub.cpp)
add_executable(pmb2_track src/pmb2_track.cpp)
add_executable(tiagoColourFinder src/tiagoColourFinder.cpp)
add_executable(colourClient src/colourClient.cpp)
add_executable(depthSubscriber src/depthSubscriber.cpp)
add_executable(headCtrl src/headCtrl.cpp)
add_executable(torsoCtrl src/torsoCtrl.cpp)
add_executable(tiagoColourFinderWithHead src/tiagoColourFinderWithHead.cpp)
add_executable(alw82Assignment src/alw82Assignment.cpp)

target_include_directories(helloWorld PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(helloWorld PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
add_definitions(${OpenCV_DEFINITIONS})

ament_target_dependencies(examplePublisher rclcpp std_msgs)
ament_target_dependencies(exampleSubscriber rclcpp std_msgs)
ament_target_dependencies(randomTurtle rclcpp geometry_msgs sensor_msgs)
ament_target_dependencies(velodyneSubscriber rclcpp sensor_msgs)
ament_target_dependencies(pmb2_track rclcpp geometry_msgs sensor_msgs)
ament_target_dependencies(tiagoColourFinder rclcpp geometry_msgs)
ament_target_dependencies(colourClient rclcpp rcl_interfaces)
ament_target_dependencies(depthSubscriber sensor_msgs image_transport cv_bridge OpenCV tf2 tf2_ros)
ament_target_dependencies(headCtrl control_msgs trajectory_msgs rclcpp_action rclcpp_components)
ament_target_dependencies(torsoCtrl control_msgs trajectory_msgs rclcpp_action rclcpp_components)
ament_target_dependencies(tiagoColourFinderWithHead rclcpp geometry_msgs tf2 tf2_ros control_msgs trajectory_msgs rclcpp_action rclcpp_components)
ament_target_dependencies(alw82Assignment rclcpp geometry_msgs tf2 tf2_ros control_msgs trajectory_msgs rclcpp_action rclcpp_components sensor_msgs)

install(TARGETS 
helloWorld
examplePublisher
exampleSubscriber
randomTurtle
velodyneSubscriber
pmb2_track
tiagoColourFinder
colourClient
depthSubscriber
headCtrl
torsoCtrl
tiagoColourFinderWithHead
alw82Assignment
DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY
	launch
	DESTINATION share/${PROJECT_NAME}/)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
