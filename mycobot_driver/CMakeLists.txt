cmake_minimum_required(VERSION 3.0.2)
project(mycobot_driver)

find_package(catkin REQUIRED COMPONENTS
  rospy
)

install(FILES
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

