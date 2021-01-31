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

from threading import Lock
import rospy
from std_msgs.msg import Bool
from sensor_msgs.msg import JointState
from mycobot.mycobot import MyCobot

class Driver:
    def __init__(self, serial_port='/dev/ttyUSB0'):
        self.lock = Lock()

        self.robot = MyCobot(serial_port)

        rospy.Subscriber("gripper", Bool, self.gripper_cmd_callback)
        rospy.Subscriber("move_group/fake_controller_joint_states", JointState, self.joints_cmd_callback)
        rospy.Subscriber("joints_gui", JointState, self.joints_gui_callback)

        self.joint_states_pub = rospy.Publisher('joint_states', JointState, queue_size = 1)

        self.joint_names = ['joint2_to_joint1', 
                            'joint3_to_joint2', 
                            'joint4_to_joint3', 
                            'joint5_to_joint4', 
                            'joint6_to_joint5', 
                            'joint6output_to_joint6']

        self.joints_cmd = [0, 0, 0, 0, 0, 0]
        self.joint_states = [0, 0, 0, 0, 0, 0]
        self.gripper_cmd = False
        self.gripper_cmd_ack = True

        self.last_cmd_time = rospy.Time.now()

        self.joint_states_msg = JointState()
        self.joint_states_msg.header.frame_id = 'joint1'
        self.joint_states_msg.header.stamp = rospy.Time.now()
        self.joint_states_msg.name = self.joint_names

        # self.robot.set_claw(False)
        self.robot.power_on()
        control_rate = rospy.Rate(30)
        while not rospy.is_shutdown():
            cur_actuator_angle = self.robot.get_angles_of_radian()
            if len(cur_actuator_angle) == 6:
                self.joint_states = self.invert_joints(cur_actuator_angle)
          
            self.robot.send_angles_by_radian(self.joints_cmd, 80)

            if not self.gripper_cmd_ack:
                rospy.loginfo("GRIPPER %d", self.gripper_cmd)
                self.gripper_cmd_ack = True
                # self.robot.set_claw(self.gripper_cmd)

            self.joint_states_msg.position = self.joint_states
            self.joint_states_msg.header.stamp = rospy.Time.now()
            self.joint_states_pub.publish(self.joint_states_msg)

            control_rate.sleep()

    def gripper_cmd_callback(self, gripper_cmd):
        with self.lock:
            self.gripper_cmd_ack = False
            self.gripper_cmd = gripper_cmd.data

    def joints_cmd_callback(self, joints_cmd):
        with self.lock:
            self.last_cmd_time = rospy.Time.now()
            for joint_name, joint_position in zip(joints_cmd.name, joints_cmd.position):
                try:
                    j_idx = self.joint_names.index(joint_name)
                except ValueError:
                    continue

                invert = -1
                if j_idx == 2:
                    invert = 1

                self.joints_cmd[j_idx] = joint_position * invert

    def joints_gui_callback(self, joints_cmd):
        with self.lock:
            if (rospy.Time.now() - self.last_cmd_time).to_sec() < 0.1:
                return
            for joint_name, joint_position in zip(joints_cmd.name, joints_cmd.position):
                try:
                    j_idx = self.joint_names.index(joint_name)
                except ValueError:
                    continue
                    
                self.joints_cmd[j_idx] = joint_position

    def invert_joints(self, joints):
        for i in range(len(joints)):
            if i != 2:
                joints[i] *= -1.0
        
        return joints

if __name__ == "__main__":
    rospy.init_node('mycobot_driver', anonymous=True)
    d = Driver('/dev/ttyUSB0')
    rospy.spin()