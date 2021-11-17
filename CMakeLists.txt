cmake_minimum_required(VERSION 3.0.2)
project(robot_core)

find_package(catkin REQUIRED COMPONENTS
  move_base_msgs
  fiducial_msgs
  geometry_msgs
  robot_msgs
  roscpp
  rospy
  std_msgs
)

catkin_package(
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(robot_core_sys src/robot_core_sys.cpp)

add_dependencies(robot_core_sys ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(robot_core_sys
  ${catkin_LIBRARIES}
)

add_executable(blth_srv src/blth_srv.cpp)

add_dependencies(blth_srv ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(blth_srv
  ${catkin_LIBRARIES}
)

add_executable(nav_pub src/nav_pub.cpp)

add_dependencies(nav_pub ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(nav_pub
  ${catkin_LIBRARIES}
)

add_executable(docking src/docking.cpp)

add_dependencies(docking ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(docking
  ${catkin_LIBRARIES}
)