cmake_minimum_required(VERSION 3.0.2)
project(mycobot)

find_package(catkin REQUIRED COMPONENTS
  rospy
)

catkin_python_setup()

install(FILES
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

