#!/usr/bin/env python
#!-*-coding=utf-8 -*-
 
 
import rospy
from sensor_msgs.msg import Image
import cv2
import numpy as np
from cv_bridge import CvBridge, CvBridgeError
import sys
import time

lower_blue=np.array([100,43,46])
upper_blue=np.array([124,255,255])
#lower_blue=np.array([14,143,80])
#upper_blue=np.array([23,255,200])

#lower_red=np.array([0,200,55])
#upper_red=np.array([10,255,130])
#lower_red=np.array([0,150,55])
#upper_red=np.array([10,255,130])
lower_red=np.array([0,43,46])
upper_red=np.array([10,255,255])

lower_green=np.array([40,43,46])
upper_green=np.array([77,255,255])
font = cv2.FONT_HERSHEY_SIMPLEX  # 设置字体样式
kernel = np.ones((5, 5), np.uint8)  # 卷积核
img_pub = rospy.Publisher('webcam/image_raw', Image, queue_size=2)

#cap = cv2.VideoCapture(0)

def areaCal(contour):

    area = 0
    for i in range(len(contour)):
        area += cv2.contourArea(contour[i])
    return area

def image_callback(msg): 
           bridge = CvBridge()
           frame = bridge.imgmsg_to_cv2(msg, "bgr8")
           #cv2.imshow("source", frame)
           #ret, frame = Video.read()
           gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)  # 转换为灰色通道
           hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)  # 转换为HSV空间
           mask = cv2.inRange(hsv, lower_red, upper_red)  # 设定掩膜取值范围  [消除噪声]
           #mask = cv2.inRange(hsv, lower_green, upper_green)  # 设定掩膜取值范围 [消除噪声]
           opening = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel)  # 形态学开运算 [消除噪声]
           bila = cv2.bilateralFilter(mask, 10, 200, 200)  # 双边滤波消除噪声 [消除噪声]
           edges = cv2.Canny(opening, 50, 100)  # 边缘识别 [消除噪声]
           mask_green = cv2.inRange(hsv,lower_green,upper_green)
           opening_green = cv2.morphologyEx(mask_green, cv2.MORPH_OPEN, kernel)
           bila_green = cv2.bilateralFilter(mask_green, 10, 200, 200)
           edges_green = cv2.Canny(opening_green, 50, 100)
           images,contourss,hierarchvs = cv2.findContours(edges_green,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
           image,contours,hierarchv = cv2.findContours(edges,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
           scaling_factor = 0.5
           print "area_red=",areaCal(contours),"area_green=",areaCal(contourss)
           if(areaCal(contours)>50):
             #circles = cv2.HoughCircles(edges, cv2.HOUGH_GRADIENT, 1, 100, param1=100, param2=20, minRadius=20, maxRadius=500)
             circles = cv2.HoughCircles(edges, cv2.HOUGH_GRADIENT, 1, 100, param1=100, param2=20, minRadius=0, maxRadius=0)
             if circles is not None:  # 如果识别出圆
               #print "I found the red circle"
               for circle in circles[0]:
                 x_red=int(circle[0])
                 y_red=int(circle[1])
                 r_red=int(circle[2])
                 cv2.circle(frame, (x_red, y_red), r_red, (0, 0, 255), 3)  # 标记圆
                 cv2.circle(frame, (x_red, y_red), 3, (255, 255, 0), -1)  # 标记圆心
                 text = 'circle' + 'x:  '+str(x_red)+' y:  '+str(y_red)
                 cv2.putText(frame, text, (10, 30), font, 1, (0, 255, 0), 2, cv2.LINE_AA, 0)  # 显示圆心位置

           if(areaCal(contourss)>1000):
             #circles = cv2.HoughCircles(edges, cv2.HOUGH_GRADIENT, 1, 100, param1=100, param2=20, minRadius=20, maxRadius=500)
             circles = cv2.HoughCircles(edges_green, cv2.HOUGH_GRADIENT, 1, 100, param1=100, param2=20, minRadius=0, maxRadius=0)
             if circles is not None:  # 如果识别出圆
               #print "I found the green circle"
               for circle in circles[0]:
                 x_red=int(circle[0])
                 y_red=int(circle[1])
                 r_red=int(circle[2])
                 cv2.circle(frame, (x_red, y_red), r_red, (0, 0, 255), 3)  # 标记圆
                 cv2.circle(frame, (x_red, y_red), 3, (255, 255, 0), -1)  # 标记圆心
                 text = 'circle' + 'x:  '+str(x_red)+' y:  '+str(y_red)
                 cv2.putText(frame, text, (10, 60), font, 1, (0, 255, 0), 2, cv2.LINE_AA, 0)  # 显示圆心位置
           frame = cv2.resize(frame,None,fx=scaling_factor,fy=scaling_factor,interpolation=cv2.INTER_AREA)
           msg = bridge.cv2_to_imgmsg(frame, encoding="bgr8")
           img_pub.publish(msg)
           cv2.waitKey(3)
           '''
           rate = rospy.Rate(20) # 5hz
           scaling_factor = 0.5
           bridge = CvBridge() 
           count = 0
           while not rospy.is_shutdown():
             if (True):
               count = count + 1
             else:
               rospy.loginfo("Capturing image failed.")
             if count == 2:
               count = 0
               frame = cv2.resize(frame,None,fx=scaling_factor,fy=scaling_factor,interpolation=cv2.INTER_AREA)
               msg = bridge.cv2_to_imgmsg(frame, encoding="bgr8")
               img_pub.publish(msg) 
           rate.sleep()          
           '''
def webcamImagePub():
    rospy.init_node('webcam_puber', anonymous=True)
#    img_pub = rospy.Publisher('webcam/image_raw', Image, queue_size=2)
    rospy.Subscriber("/image_raw", Image, image_callback)
    rospy.spin()
 
if __name__ == '__main__':
    try:
        webcamImagePub()
    except rospy.ROSInterruptException:
        pass
    finally:
        webcamImagePub()
