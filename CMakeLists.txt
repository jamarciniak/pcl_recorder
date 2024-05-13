cmake_minimum_required(VERSION 3.8)
project(pcl_recorder)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(pluginlib REQUIRED)
find_package(point_cloud_interfaces REQUIRED)
find_package(point_cloud_transport REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(draco REQUIRED)
find_package(draco_point_cloud_transport REQUIRED)

# Include directories for draco_point_cloud_transport
include_directories(${draco_point_cloud_transport_INCLUDE_DIRS})

# Uncomment the following lines if needed for linking directories
# link_directories(${draco_point_cloud_transport_LIBRARY_DIRS})

add_executable(pcl_recorder src/pcl_recorder.cpp)
ament_target_dependencies(pcl_recorder 
  point_cloud_transport 
  rclcpp 
  sensor_msgs 
  draco_point_cloud_transport)


target_include_directories(pcl_recorder PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(pcl_recorder PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

install(TARGETS pcl_recorder
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # The following line skips the linter which checks for copyrights
  # Comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # The following line skips cpplint (only works in a git repo)
  # Comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
