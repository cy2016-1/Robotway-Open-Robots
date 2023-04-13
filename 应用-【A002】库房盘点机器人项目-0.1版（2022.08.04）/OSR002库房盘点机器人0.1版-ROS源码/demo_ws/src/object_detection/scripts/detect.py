#!/usr/bin/env python
from __future__ import print_function

import sys
import rospy
import cv2
from sensor_msgs.msg import Image
from geometry_msgs.msg import Point
from cv_bridge import CvBridge, CvBridgeError
import numpy as np

lower_green = np.array([35, 43, 46])
upper_green = np.array([77,255,255])

class image_converter:

  def __init__(self):
    self.image_pub = rospy.Publisher("image_topic_2",Image, queue_size=5)

    self.bridge = CvBridge()
    self.image_sub = rospy.Subscriber("usb_cam/image_raw",Image,self.callback)
    self.center_pub = rospy.Publisher("~object_center", Point, queue_size=10)

  def callback(self,data):
    try:
      cv_image = self.bridge.imgmsg_to_cv2(data, "bgr8")
    except CvBridgeError as e:
      print(e)

    img = cv2.rotate(cv_image,cv2.ROTATE_90_CLOCKWISE)
    hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
    mask = cv2.inRange(hsv, lower_green, upper_green)

    sharpen_kernel = np.array([[-1,-1,-1], [-1,9,-1], [-1,-1,-1]])
    sharpen = cv2.filter2D(mask, -1, sharpen_kernel)

    kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (3,3))
    close = cv2.morphologyEx(sharpen, cv2.MORPH_CLOSE, kernel, iterations=2)

    cnts = cv2.findContours(close, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    cnts = cnts[0] if len(cnts) == 2 else cnts[1]

    min_area = 2000
    max_area = 50000
    for c in cnts:
        area = cv2.contourArea(c)
        if area > min_area and area < max_area:
            #print(area)
            x,y,w,h = cv2.boundingRect(c)
            #print("center: ({}, {})".format(x+w/2, y+h/2))
            cv2.putText(img, "center: ({}, {})".format(x+w/2, y+h/2), (x, y-20), cv2.FONT_HERSHEY_COMPLEX, 0.5, (36, 255, 12), 1)
            cv2.rectangle(img, (x, y), (x + w, y + h), (36,255,12), 2)
            point = Point(x = y+h/2 - 240, y = h, z = x+w/2)
            self.center_pub.publish(point)
            break

    try:
      self.image_pub.publish(self.bridge.cv2_to_imgmsg(img, "bgr8"))
    except CvBridgeError as e:
      print(e)

def main(args):
  rospy.init_node('detect', anonymous=True)
  ic = image_converter()
  try:
    rospy.spin()
  except KeyboardInterrupt:
    print("Shutting down")
  cv2.destroyAllWindows()

if __name__ == '__main__':
    main(sys.argv)
