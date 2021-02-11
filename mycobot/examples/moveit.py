#!/usr/bin/env python
import sys
import math
import rospy
from mycobot.commander import MyCobotCommander

if __name__ == "__main__":
    rospy.init_node("moveit_test", anonymous = True, disable_signals=True)
    
    manipulator = MyCobotCommander()
    manipulator.open_gripper()
    while not rospy.is_shutdown():
        target_x = 0.2
        target_y = 0.0
        target_z = 0.055
        manipulator.open_gripper()
        manipulator.move_to_goal_pose(target_x, 
                                      target_y, 
                                      target_z, 
                                      roll=0.0,
                                      pitch=1.5708,
                                      yaw=0.0)

        manipulator.set_gripper_dist(0.001)
        break