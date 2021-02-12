#!/usr/bin/env python
import sys
import time
import math
import rospy
from mycobot.commander import MyCobotCommander

if __name__ == "__main__":
    rospy.init_node("moveit_test", anonymous = True, disable_signals=True)
    
    manipulator = MyCobotCommander()
    init_joints = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
    #manipulator.add_obstacle('floor', 0.4, 0.52, 0.001, pos_x=0.1)
    #manipulator.add_obstacle('back_wall', 0.0001, 0.52, 0.5, pos_x=-0.2, pos_z=0.25)
    #manipulator.add_obstacle('camera_mount', 0.04, 0.015, 0.5, pos_x=0.25, pos_y=-0.23, pos_z=0.25)
    # manipulator.move_joints(init_joints)

    time.sleep(6)
    manipulator.open_gripper()
    time.sleep(1)
    manipulator.close_gripper()
    time.sleep(1)
    manipulator.open_gripper()
    time.sleep(1)

    while not rospy.is_shutdown():
        target_x = 0.25
        target_y = 0.0
        target_z = 0.10
        manipulator.close_gripper()
        time.sleep(1)

        manipulator.move_to_goal_pose(target_x, 
                                      target_y, 
                                      target_z, 
                                      roll=0.0,
                                      pitch=1.309,
                                      yaw=0.0)

        manipulator.move_to_goal_pose(target_x, 
                                      target_y, 
                                      target_z-0.08, 
                                      roll=0.0,
                                      pitch=1.309,
                                      yaw=0.0)

        manipulator.set_gripper_dist(0.009)
        time.sleep(1)

        break