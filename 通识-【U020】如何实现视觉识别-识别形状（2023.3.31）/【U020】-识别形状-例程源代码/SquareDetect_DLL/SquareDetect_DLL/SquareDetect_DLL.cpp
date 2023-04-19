// ShapeDetect_DLL.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "SquareDetect_DLL.h"
#include <opencv2/core/core.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <math.h>
#include <string.h>

using namespace cv;
using namespace std;

Mat imageSource;
VideoCapture cap;
int object_detect = 0;
const char* wndname = "ShapeDetect";

int thresh = 50, N = 11;

//判断图片及视频输入
static void ModeSet(char * address, int DETECT_MODE)
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
			namedWindow(wndname, 0);
			if (!cap.isOpened())
			{
				return;
			}
		}
		cap >> imageSource;
	}
}

//求两条直线夹角
static double angle(Point pt1, Point pt2, Point pt0)
{
	double dx1 = pt1.x - pt0.x;
	double dy1 = pt1.y - pt0.y;
	double dx2 = pt2.x - pt0.x;
	double dy2 = pt2.y - pt0.y;
	return (dx1*dx2 + dy1*dy2) / sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

//多边形检测，通过约束条件寻找矩形
static void findSquares(const Mat& image, vector<vector<Point> >& squares)
{
	squares.clear();

	Mat pyr, timg, gray0(image.size(), CV_8U), gray;

	// down-scale and upscale the image to filter out the noise
	pyrDown(image, pyr, Size(image.cols / 2, image.rows / 2));
	pyrUp(pyr, timg, image.size());
	vector<vector<Point> > contours;

	// find squares in every color plane of the image
	for (int c = 0; c < 3; c++)
	{
		int ch[] = { c, 0 };
		mixChannels(&timg, 1, &gray0, 1, ch, 1);

		// try several threshold levels
		for (int l = 0; l < N; l++)
		{
			// hack: use Canny instead of zero threshold level.
			// Canny helps to catch squares with gradient shading
			if (l == 0)
			{
				// apply Canny. Take the upper threshold from slider
				// and set the lower to 0 (which forces edges merging)
				Canny(gray0, gray, 0, thresh, 5);
				// dilate canny output to remove potential
				// holes between edge segments
				dilate(gray, gray, Mat(), Point(-1, -1));
			}
			else
			{
				// apply threshold if l!=0:
				//     tgray(x,y) = gray(x,y) < (l+1)*255/N ? 255 : 0
				gray = gray0 >= (l + 1) * 255 / N;
			}

			// find contours and store them all as a list
			findContours(gray, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

			vector<Point> approx;

			// test each contour
			for (size_t i = 0; i < contours.size(); i++)
			{
				// approximate contour with accuracy proportional
				// to the contour perimeter
				approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);

				// square contours should have 4 vertices after approximation
				// relatively large area (to filter out noisy contours)
				// and be convex.
				// Note: absolute value of an area is used because
				// area may be positive or negative - in accordance with the
				// contour orientation
				if (approx.size() == 4 &&
					fabs(contourArea(Mat(approx))) > 1000 &&
					isContourConvex(Mat(approx)))
				{
					double maxCosine = 0;

					for (int j = 2; j < 5; j++)
					{
						// find the maximum cosine of the angle between joint edges
						double cosine = fabs(angle(approx[j % 4], approx[j - 2], approx[j - 1]));
						maxCosine = MAX(maxCosine, cosine);
					}

					// if cosines of all angles are small
					// (all angles are ~90 degree) then write quandrange
					// vertices to resultant sequence
					if (maxCosine < 0.3)
						squares.push_back(approx);
				}
			}
		}
	}
}

//画出所有矩形
static void drawSquares(Mat& image, const vector<vector<Point> >& squares)
{
	cout << squares.size();
	for (size_t i = 0; i < squares.size(); i++)
	{
		const Point* p = &squares[i][0];
		int n = (int)squares[i].size();
		polylines(image, &p, &n, 1, true, Scalar(0, 255, 0), 1, LINE_AA);
	}

	imshow(wndname, image);
}

//检测矩形，无返回值
void SquareDetector(char * address, int DETECT_MODE)
{
	cvResizeWindow(wndname, 320, 240);

	ModeSet(address, DETECT_MODE);
	vector<vector<Point> > squares;

	if (imageSource.empty())
	{
		return;
	}

	findSquares(imageSource, squares);
	drawSquares(imageSource, squares);

	char c = (char)waitKey(1);
	if (c == 27)
	{
		object_detect = 0;
		cv::destroyWindow(wndname);
	}
}

