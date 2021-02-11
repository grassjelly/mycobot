#!/usr/bin/env python
'''
Copyright (c) 2021, Juan Miguel Jimeno
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the copyright holder nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
'''

import rospy
import sys
import moveit_commander
from moveit_msgs.msg import DisplayTrajectory
from geometry_msgs.msg import Pose, PoseStamped, Quaternion
from std_msgs.msg import Float32
from tf.transformations import quaternion_from_euler, euler_from_quaternion
import tf2_ros
import tf2_geometry_msgs

class MyCobotCommander:
    def __init__(self, group_name="mycobot_arm", position_tolerance=0.001, orientation_tolerance=0.000001):
        moveit_commander.roscpp_initialize(sys.argv)
        self.group = moveit_commander.MoveGroupCommander(group_name)
        self.display_trajectory_publisher = rospy.Publisher('/move_group/display_planned_path',
                                                             DisplayTrajectory, queue_size = 10)

        self.gripper_pub = rospy.Publisher('gripper', Float32, queue_size = 10)

        self.pose_debugger = rospy.Publisher('pose_debug', 
                                              PoseStamped,
                                               queue_size=10)

        self.robot = moveit_commander.RobotCommander()
        self.scene = moveit_commander.PlanningSceneInterface()
        self.planning_frame = self.robot.get_planning_frame()

        self.group.set_goal_position_tolerance(position_tolerance)
        self.group.set_goal_orientation_tolerance(orientation_tolerance)
        self.group.set_end_effector_link('tool0')

    def create_obstacle(self, object_name, pos_x, pos_y, pos_z, size_x, size_y, size_z):
        obstacle = PoseStamped()
        obstacle.header.frame_id = self.robot.get_planning_frame()
        obstacle.pose.position.x = pos_x
        obstacle.pose.position.y = pos_y
        obstacle.pose.position.z = pos_z
        obstacle.pose.orientation = Quaternion(*quaternion_from_euler(0.0, 0.0, 0.0))
        self.scene.add_box(object_name, obstacle, size=(size_x, size_y, size_z))

    def move_joints(self, joints):
        goal_joint = self.group.get_current_joint_values()
        goal_joint[0] = joints[0]
        goal_joint[1] = joints[1]
        goal_joint[2] = joints[2]
        goal_joint[3] = joints[3]
        goal_joint[4] = joints[4]
        goal_joint[5] = joints[5]

        ret = self.group.go(goal_joint, wait=True)
        self.group.stop()

        return ret

    def move_to_goal_pose(self, pos_x, pos_y, pos_z, roll=0.0, pitch=0.0, yaw=0.0, ref_frame=None):
        def transform_pose(input_pose, from_frame, to_frame):
            tf_buffer = tf2_ros.Buffer()
            listener = tf2_ros.TransformListener(tf_buffer)

            pose_stamped = tf2_geometry_msgs.PoseStamped()
            pose_stamped.pose = input_pose
            pose_stamped.header.frame_id = from_frame
            pose_stamped.header.stamp = rospy.Time.now()

            try:
                transform = tf_buffer.lookup_transform(from_frame, to_frame, rospy.Time(0), rospy.Duration(1.0))
                return tf2_geometry_msgs.do_transform_pose(pose_stamped, transform)

            except (tf2_ros.LookupException, tf2_ros.ConnectivityException, tf2_ros.ExtrapolationException):
                raise

        goal_pose = Pose()
        goal_pose.position.x = pos_x
        goal_pose.position.y = pos_y
        goal_pose.position.z = pos_z
        goal_pose.orientation = Quaternion(*quaternion_from_euler(roll, pitch, yaw))

        if ref_frame is not None and ref_frame != self.planning_frame:
            goal_pose = transform_pose(goal_pose, self.planning_frame, ref_frame)

        self.group.set_pose_target(goal_pose)
        ret = self.group.go(wait=True)
        self.group.stop()
        self.group.clear_pose_targets()

        return ret
            
    def visualize_goal_pose(self, pos_x, pos_y, pos_z, orient_roll, orient_pitch, orient_yaw):
        goal_pose = Pose()
        goal_pose.position.x = pos_x
        goal_pose.position.y = pos_y
        goal_pose.position.z = pos_z
        goal_pose.orientation = Quaternion(*quaternion_from_euler(orient_roll, orient_pitch, orient_yaw))

        self.group.set_pose_target(goal_pose)
        plan = self.group.plan()

        goal_pose_stamped = PoseStamped()
        goal_pose_stamped.header.frame_id = self.robot.get_planning_frame()
        goal_pose_stamped.pose = goal_pose

        self.pose_debugger.publish(goal_pose_stamped)

    def open_gripper(self):
        cmd = Float32()
        cmd.data = 0.018
        self.gripper_pub.publish(cmd)

    def close_gripper(self):
        cmd = Float32()
        cmd.data = 0.0
        self.gripper_pub.publish(cmd)

    def set_gripper_dist(self, dist):
        cmd = Float32()
        if dist > 0.018:
            dist = 0.018
        elif dist < 0.0:
            dist = 0.0

        cmd.data = dist
        self.gripper_pub.publish(cmd)
        