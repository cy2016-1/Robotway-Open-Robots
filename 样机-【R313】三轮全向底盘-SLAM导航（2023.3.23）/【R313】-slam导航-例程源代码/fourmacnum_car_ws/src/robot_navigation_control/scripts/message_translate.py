#!/usr/bin/env python
import numpy
import rospy
import tf
from geometry_msgs.msg import Twist, Point,Pose,PoseWithCovariance, Quaternion, Vector3
from nav_msgs.msg import Odometry

odom_frame = '/odom'
base_frame = '/base_link'
current_vx = 0
current_vy = 0
current_va = 0
current_x = 0
current_y = 0
current_a = 0
last_x = 0
last_y = 0
last_a = 0
delta_x = 0
delta_y = 0
delta_a = 0
pub_count = 0
quat = tf.transformations.quaternion_from_euler(0, -1, 0)

def callBack1(value):
 message = Vector3(value.linear.x,value.linear.y,value.angular.z)
 print("message:%f  %f  %f"%(value.linear.x,value.linear.y,value.angular.z))
 vel_cmd_pub.publish(message)
 
def callBack2(value):
	global current_x, current_y, current_a,delta_x,delta_y,delta_a,pub_count
	current_x = value.x
	current_y = value.y
	current_a = value.z
	delta_x = current_x - last_x
	delta_y = current_y - last_y
	delta_a = current_a - last_a
	pub_count = 0

def callBack3(value):
	global current_vx, current_vy, current_va
	current_vx = value.x
	current_vy = value.y
	current_va = value.z

def shutdown():
	rospy.loginfo("Stopping the robot...")
	vel_cmd_pub.publish(Vector3())

if __name__ == '__main__':
	rospy.init_node("message_translate")
	rospy.Subscriber('/cmd_vel', Twist, callBack1)
	rospy.Subscriber('/pose_feedback', Vector3, callBack2)
	rospy.Subscriber('/vel_feedback', Vector3, callBack3)

	vel_cmd_pub = rospy.Publisher('/vel_cmd', Vector3, queue_size=5)
	tf_broadcaster = tf.TransformBroadcaster()
	odom_pub = rospy.Publisher("/odom", Odometry, queue_size=50)
	receive_delta_time = 0.2    #s
	rate_fre = 30
	rate = rospy.Rate(rate_fre)
	try:
		while not rospy.is_shutdown():
			if pub_count<(rate_fre*receive_delta_time):
				last_x = last_x+(delta_x/(rate_fre*receive_delta_time))
				last_y = last_y+(delta_y/(rate_fre*receive_delta_time))
				last_a = last_a+(delta_a/(rate_fre*receive_delta_time))
				pub_count = pub_count + 1
			quat = tf.transformations.quaternion_from_euler(0, 0, last_a)
			tf_broadcaster.sendTransform((last_x, last_y, 0.),quat,rospy.Time.now(),base_frame,odom_frame)
			odom = Odometry()
			odom.header.stamp = rospy.Time.now()
			odom.header.frame_id = odom_frame
			odom.child_frame_id = base_frame
			odom.pose.pose = Pose(Point(last_x, last_y, 0.), Quaternion(*quat))
			odom.twist.twist = Twist(Vector3(current_vx, current_vy,0), Vector3(0, 0, current_va))
			odom_pub.publish(odom)
			rate.sleep()
		#shutdown()
		rospy.spin()
	except:
		pass



