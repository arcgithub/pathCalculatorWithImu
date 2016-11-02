cmake_minimum_required(VERSION 2.8.3)
project(pathcalculatorwithimu)

find_package(catkin REQUIRED COMPONENTS
  	roscpp
  	rospy
    geometry_msgs
    sensor_msgs
)

catkin_package(
  CATKIN_DEPENDS 
  geometry_msgs
  roscpp
  sensor_msgs
)
   

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(path_calc src/path_calc.cpp)
target_link_libraries(path_calc ${catkin_LIBRARIES})
