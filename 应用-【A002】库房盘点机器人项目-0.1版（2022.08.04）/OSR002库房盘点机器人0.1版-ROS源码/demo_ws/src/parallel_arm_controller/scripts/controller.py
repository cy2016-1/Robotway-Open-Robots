#!/usr/bin/env python
from __future__ import print_function

import sys
import rospy
from geometry_msgs.msg import Point
from std_srvs.srv import Trigger, TriggerResponse
from std_msgs.msg import Float32
from protobot_motor_ros.srv import GetMotorStatus
from math import sqrt, pi, atan2, acos

ARM_D = 100
ARM_A = 350
ARM_B = 330

class arm_controller:
    def __init__(self):
        self.init_service = rospy.Service('init_arm', Trigger, self.init_callback)
        rospy.wait_for_service('motor_l/enable')
        rospy.wait_for_service('motor_r/enable')
        self.enable_z = rospy.ServiceProxy('motor_z/enable', Trigger)
        self.enable_l = rospy.ServiceProxy('motor_l/enable', Trigger)
        self.enable_r = rospy.ServiceProxy('motor_r/enable', Trigger)
        self.z_pos_pub = rospy.Publisher('motor_z/pos', Float32, queue_size=5)
        self.l_pos_pub = rospy.Publisher('motor_l/pos', Float32, queue_size=5)
        self.r_pos_pub = rospy.Publisher('motor_r/pos', Float32, queue_size=5)
        self.dest_sub = rospy.Subscriber('arm_dest', Point, self.dest_sub_callback)
        rospy.loginfo('connected')
        self.is_init = False
    
    def init_callback(self, req):
        self.enable_z()
        self.enable_l()
        self.enable_r()
        get_motorz_status = rospy.ServiceProxy('motor_z/get_motor_status', GetMotorStatus)
        get_motorl_status = rospy.ServiceProxy('motor_l/get_motor_status', GetMotorStatus)
        get_motorr_status = rospy.ServiceProxy('motor_r/get_motor_status', GetMotorStatus)
        z_status = get_motorz_status(timeout=0)
        l_status = get_motorl_status(timeout=0)
        r_status = get_motorr_status(timeout=0)
        self.z_init = z_status.position
        self.l_init = l_status.position
        self.r_init = r_status.position
        self.is_init = True
        return TriggerResponse(success=True)

    def dest_sub_callback(self, data):
        if not self.is_init:
            rospy.logwarn('should init first')
            return
        if data.y < 270:
            rospy.logwarn('dest point out of range')
            return
        theta0 = self.inverse_kinematics(ARM_D / 2 - data.x, data.y)
        theta1 = self.inverse_kinematics(ARM_D / 2 + data.x, data.y)
        if theta0 < 0 or theta1 < 0:
            rospy.logwarn('dest point out of range')
            return
        self.l_pos_pub.publish(data = self.l_init + theta1)
        self.r_pos_pub.publish(data = self.r_init - theta0)
        self.z_pos_pub.publish(data = self.z_init + data.z)
        
    def inverse_kinematics(self, x, y):
        l = sqrt(x * x + y * y)
        alpha = atan2(y, x)
        beta = acos((l*l + ARM_A*ARM_A - ARM_B*ARM_B) / (2*l*ARM_A))
        return alpha + beta - pi/2

def main(args):
    rospy.init_node('arm_controller', anonymous=False)
    controller = arm_controller()
    try:
        rospy.spin()
    except KeyboardInterrupt:
        print("Shutting down")

if __name__ == '__main__':
    main(sys.argv)
