#!/usr/bin/env python
#!-*-coding=utf-8 -*-

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

img_pub = rospy.Publisher('webcam/image_raw', Image, queue_size=2)
lower_blue=np.array([100,43,46])
upper_blue=np.array([124,255,255])

lower_red=np.array([0,43,46])
upper_red=np.array([10,255,255])

lower_green=np.array([40,43,46])
upper_green=np.array([77,255,255])
font = cv2.FONT_HERSHEY_SIMPLEX
kernel = np.ones((5, 5), np.uint8)

def areaCal(contour):
    area = 0
    for i in range(len(contour)):
        area += cv2.contourArea(contour[i])
    return area
    
    
def image_callback(msg):
  bridge = CvBridge()
  img = bridge.imgmsg_to_cv2(msg, "bgr8")
  #cv2.imshow("source", img)
  hsv = cv2.cvtColor(img,cv2.COLOR_BGR2HSV)
  mask_red = cv2.inRange(hsv,lower_red,upper_red)
  res = cv2.bitwise_and(img,img,mask=mask_red)
  scaling_factor = 0.5
#  cv2.imshow("res",res)
  image,contours,hierarchv = cv2.findContours(mask_red,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
#  print  "red=",areaCal(contours)
  if (areaCal(contours)>5000):
#    print "red color"
    text_red = 'the color is red'
    cv2.putText(img, text_red, (10, 30), font, 1, (0, 0, 255), 2, cv2.LINE_AA, 0)
  mask_blue= cv2.inRange(hsv, lower_blue, upper_blue)
  res_yellow = cv2.bitwise_and(img,img,mask=mask_blue)
  image,contours,hierarchv = cv2.findContours(mask_blue,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
  if(areaCal(contours)>8000):
    text_blue = 'the color is blue'
#    print "blue color"
    cv2.putText(img, text_blue, (10, 60), font, 1, (255, 0, 0), 2, cv2.LINE_AA, 0)
  mask_green=cv2.inRange(hsv, lower_green,upper_green)
  res_green = cv2.bitwise_and(img,img,mask=mask_blue)
  image,contours,hierarchv = cv2.findContours(mask_green,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
  if (areaCal(contours)>5000):
    text_green = 'the color is green'
    cv2.putText(img, text_green, (10, 90), font, 1, (0, 255, 0), 2, cv2.LINE_AA, 0)
#    print ("green color")
#  else:
#     print( "NONE COLOR" )
  frame = cv2.resize(img,None,fx=scaling_factor,fy=scaling_factor,interpolation=cv2.INTER_AREA)
  msg = bridge.cv2_to_imgmsg(frame, encoding="bgr8")
  img_pub.publish(msg)
  cv2.waitKey(3)
#  cv2.waitKey(1)


def main():
    rospy.init_node('image_listener',anonymous=True)
    #image_topic = "/camera/color/image_raw"
    #rospy.Subscriber("/camera/color/image_raw", Image, image_callback)
    rospy.Subscriber("/image_raw", Image, image_callback)
    rospy.spin()

if __name__ == '__main__':
    main()
