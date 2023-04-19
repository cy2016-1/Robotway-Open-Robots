// HoughCircles_DLL.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "HoughCircles_DLL.h"
#include <opencv2/core/core.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>

using namespace cv;
using namespace std;

Mat imageSource;
VideoCapture cap;
int object_detect = 0;

size_t HoughCircles(char * address, int DETECT_MODE)
{

	if (DETECT_MODE == 1)
	{
		imageSource = imread(address);
	}
	else if (DETECT_MODE == 2)
	{
		if (!object_detect)
		{
			cap.open(address);
			object_detect = 1;
			namedWindow("ShapeDetect", 0);
			if (!cap.isOpened())
			{
				return 0;
			}
		}
		cap >> imageSource;
	}
	if (imageSource.empty())
	{
		return 0;
	}

	Mat image;
	//转换为灰度图
	cvtColor(imageSource, image, CV_BGR2GRAY);
	//重新设定窗口大小
	cvResizeWindow("ShapeDetect", 320, 240);
	//中值滤波
	medianBlur(image, image, 5);
	//霍夫变换
	vector<Vec3f> circles;
	HoughCircles(image, circles, HOUGH_GRADIENT, 2.0,
		image.rows/8, // change this value to detect circles with different distances to each other
		200, 85, 0, 0 // change the last two parameters
					  // (min_radius & max_radius) to detect larger circles
	);
	//画圆
	for (size_t i = 0; i < circles.size(); i++)
	{
		Vec3i c = circles[i];
		circle(imageSource, Point(c[0], c[1]), c[2], Scalar(0, 0, 255), 3, LINE_AA);
		//circle(imageSource, Point(c[0], c[1]), 2, Scalar(0, 255, 0), 3, LINE_AA);
	}

	imshow("ShapeDetect", imageSource);

	char c = (char)waitKey(1);
	if (c == 27)
	{
		object_detect = 0;
		cv::destroyWindow("ShapeDetect");
	}

	return circles.size();
}

