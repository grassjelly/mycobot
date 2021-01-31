#!/usr/bin/env python
import sys
import math
import rospy
from mycobot.commander import MyCobotCommander

if __name__ == "__main__":
    rospy.init_node("moveit_test", anonymous = True, disable_signals=True)
    
    manipulator = MyCobotCommander()

    while not rospy.is_shutdown():
        target_x = 0.15
        target_y = 0.15
        target_z = 0.15
        manipulator.move_to_goal_pose(target_x, 
                                      target_y, 
                                      target_z, 
                                      ref_frame="base_mount")
        rospy.sleep(2)
        manipulator.move_to_goal_pose(target_x, 
                                      0.0, 
                                      target_z, 
                                      roll=0.0,
                                      pitch=0.0,
                                      yaw=0.0,
                                      ref_frame="base_mount")
        break