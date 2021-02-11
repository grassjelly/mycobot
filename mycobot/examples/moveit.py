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
    manipulator.move_joints(init_joints)

    time.sleep(1)
    manipulator.open_gripper()
    time.sleep(1)
    manipulator.close_gripper()
    time.sleep(1)
    manipulator.open_gripper()
    time.sleep(1)

    while not rospy.is_shutdown():
        target_x = 0.22
        target_y = 0.0
        target_z = 0.10
        manipulator.close_gripper()
        time.sleep(1)

        manipulator.move_to_goal_pose(target_x, 
                                      target_y, 
                                      target_z, 
                                      roll=0.0,
                                      pitch=1.5708,
                                      yaw=0.0)

        manipulator.move_to_goal_pose(target_x, 
                                      target_y, 
                                      target_z-0.05, 
                                      roll=0.0,
                                      pitch=1.5708,
                                      yaw=0.0)

        manipulator.set_gripper_dist(0.009)
        time.sleep(1)

        break