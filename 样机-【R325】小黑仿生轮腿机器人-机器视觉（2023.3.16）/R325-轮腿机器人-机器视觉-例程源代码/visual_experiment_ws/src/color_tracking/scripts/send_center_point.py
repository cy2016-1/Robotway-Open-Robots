#!/usr/bin/env python
#!coding=utf-8

import rospy
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError
import cv2
import numpy as np
import serial
import time
import sys
from std_msgs.msg import UInt16
from std_msgs.msg import String

#lower_blue=np.array([50,143,146])
#upper_blue=np.array([124,255,255])
#lower_blue=np.array([14,143,80])
#upper_blue=np.array([23,255,200])
lower_blue=np.array([100,43,46])
upper_blue=np.array([124,255,255])

#lower_red=np.array([0,200,55])
#upper_red=np.array([10,255,130])
#lower_red=np.array([0,150,55])
#upper_red=np.array([10,255,130])
lower_red=np.array([0,43,46])
upper_red=np.array([10,255,255])

lower_green=np.array([40,43,46])
upper_green=np.array([77,255,255])

#ser = serial.Serial('/dev/ttyACM0', 57600, timeout=2.0) #2020.8.28 source value=0.5
#img_pub = rospy.Publisher('webcam/image_raw', Image, queue_size=2)
data_pub= rospy.Publisher('hahaha',String,queue_size=20)

red_flag=0
blue_flag=0
image_flags = 1
cx_string=""
cy_string=""
cx_cy_string=""
send_data = ""
count=0
scaling_factor = 0.1  #2020.8.28 source value=0.5


def areaCal(contour):
    area = 0
    for i in range(len(contour)):
        area += cv2.contourArea(contour[i])
    return area
    
    
def image_callback(msg):
  global count,send_data
  bridge = CvBridge()
  frame = bridge.imgmsg_to_cv2(msg, "bgr8")
  cv2.imshow("source", frame)
  hsv = cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)
  mask_red = cv2.inRange(hsv,lower_red,upper_red)
  res = cv2.bitwise_and(frame,frame,mask=mask_red)
  #cv2.imshow("res",res)
  image,contours,hierarchv = cv2.findContours(mask_red,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)  
  print "mianji=",areaCal(contours)
  if (areaCal(contours)>5000):
    if(areaCal(contours)>80000):
      send_data="back"
      #ser.write("back\n")
      #print "back"
    elif( areaCal(contours)<50000 and areaCal(contours)>5000 ):
      send_data="forward"
      #ser.write("forward\n")
      #print "forward"
    else:
      send_data="state"
    if len(contours) > 0:
      c = max(contours, key=cv2.contourArea)
      #print "c=",c
      cnt=contours[0]
      #cv2.drawContours(frame, c, -1, (0, 0, 255), 1)#画轮廓
      #cv2.imshow("drawcontours",frame)
      M = cv2.moments(c)
      if M["m00"] !=0:
        cx = int(M['m10']/M['m00'])
        cy = int(M['m01']/M['m00'])
        center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))
        cv2.circle(frame, (cx,cy), 5, (255, 255, 0), -1)
        print "center=",center,"cx=",cx,"cy=",cy
        cx_string=str(cx)
        cy_string=str(cy)
        #cx_cy_string=(cx_string + "-" + cy_string + "\n").encode('utf-8')
        #cx_cy_string=(cx_string + "-" + cy_string + "-" + send_data + "\n").encode('utf-8')
        cx_cy_string=(cx_string + "-" + cy_string + "+" + send_data ).encode('utf-8')
        #print (cx_cy_string)
        data_pub.publish(cx_cy_string)
      else:
        cx=0
        cy=0
    else:
      print "no red color something"
    cv2.waitKey(1)
      #cv2.imshow("chanle", img)
#      if cv2.waitKey(1) & 0xFF == ord('q'):
#        #break
#        #continue
'''
    if(image_flags==1):
      count = count+1
    else:
      rospy.loginfo("Capturing image failed.")
    if count == 2:
      count = 0
      frame = cv2.resize(frame,None,fx=scaling_factor,fy=scaling_factor,interpolation=cv2.INTER_AREA)
      msg = bridge.cv2_to_imgmsg(frame, encoding="bgr8")
      img_pub.publish(msg)
#  cv2.waitKey(3)
'''

def main():
    rospy.init_node('image_listener',anonymous=True)
#    img_pub = rospy.Publisher('webcam/image_raw', Image, queue_size=2)
    rospy.Subscriber("/image_raw", Image, image_callback)
    rospy.spin()

if __name__ == '__main__':
    main()
