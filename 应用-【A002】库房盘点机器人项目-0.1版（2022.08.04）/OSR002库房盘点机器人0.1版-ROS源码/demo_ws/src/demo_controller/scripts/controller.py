#!/usr/bin/env python
from __future__ import print_function

import sys
import rospy
import actionlib
import time
from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal
from std_srvs.srv import Trigger
from geometry_msgs.msg import Point
from protobot_can_ros.msg import CanFrame
from protobot_can_ros.srv import Transmit, TransmitRequest

class demo_controller:
    def __init__(self):
        self.nav_client = actionlib.SimpleActionClient('move_base',MoveBaseAction)
        self.arm_init_proxy = rospy.ServiceProxy('init_arm', Trigger)
        self.arm_dest_pub = rospy.Publisher('arm_dest', Point, queue_size=5)
        self.nozzel_proxy = rospy.ServiceProxy('can/transmit', Transmit)
        self.detect_sub = rospy.Subscriber('detect_node/object_center', Point, self.detect_cb)
        self.following = False
        self.dest_x = 0
        self.dest_y = 270
    
    def move_base(self, x, y, z, w):
        self.nav_client.wait_for_server()
        goal = MoveBaseGoal()
        goal.target_pose.header.frame_id = "map"
        goal.target_pose.header.stamp = rospy.Time.now()
        goal.target_pose.pose.position.x = x
        goal.target_pose.pose.position.y = y
        goal.target_pose.pose.orientation.z = z
        goal.target_pose.pose.orientation.w = w

        self.nav_client.send_goal(goal)
        wait = self.nav_client.wait_for_result()
        if not wait:
            rospy.logerr("Action server not available!")
            rospy.signal_shutdown("Action server not available!")
        else:
            rospy.loginfo("Goal execution done!")
            return self.nav_client.get_result()
    
    def detect_cb(self, point):
        if self.following:
            x = point.z - 250
            y = 640 - 5*(point.y - 70)
            self.dest_x = x
            self.dest_y = y
            self.move_arm(x, y, 20)
    
    def init_arm(self):
        rospy.wait_for_service('init_arm')
        self.arm_init_proxy()

    def move_arm(self, x, y, z):
        self.arm_dest_pub.publish(x = x, y = y, z = z-20)
        
    def nozzel_on(self):
        rospy.wait_for_service('can/transmit')
        req = TransmitRequest()
        frame = CanFrame()
        req.node_id = 33
        frame.command_id = 1
        req.frame = frame
        self.nozzel_proxy(req)
        
    def nozzel_off(self):
        rospy.wait_for_service('can/transmit')
        req = TransmitRequest()
        frame = CanFrame()
        req.node_id = 33
        frame.command_id = 2
        req.frame = frame
        self.nozzel_proxy(req)
    
    

if __name__ == '__main__':
    try:
        rospy.init_node('demo_controller')
        controller = demo_controller()
        time.sleep(0.5)
        #controller.init_arm()
        controller.move_arm(0, 270, 20)
        time.sleep(3)
        
        controller.move_base(3.474, -6.5, -0.72, 0.694)
        time.sleep(1)
        controller.following = True
        #controller.move_arm(0, 640, 20)
        time.sleep(5)
        controller.following = False
        #controller.move_arm(0, 640, -16)
        controller.move_arm(controller.dest_x, controller.dest_y, -16)
        time.sleep(4)
        controller.nozzel_on()
        time.sleep(3)
        controller.move_arm(controller.dest_x, controller.dest_y, 20)
        time.sleep(5)
        controller.move_arm(0, 270, 20)
        
        controller.move_base(0.449, -8.623, -0.72, 0.694)
        time.sleep(1)
        controller.move_arm(0, 600, 20)
        time.sleep(3)
        controller.move_arm(0, 600, -25)
        time.sleep(6)
        controller.nozzel_off()
        time.sleep(3)
        controller.move_arm(0, 600, 20)
        time.sleep(4)
        controller.move_arm(0, 270, 20)
        time.sleep(2)
        controller.move_base(1.82, -0.837, 0.712, 0.703)
        controller.move_base(0, 0, 0, 1)
        
    except rospy.ROSInterruptException:
        rospy.loginfo("Navigation test finished.")
