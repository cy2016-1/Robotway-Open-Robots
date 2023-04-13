#ifndef RssiPositionComputer_H
#define RssiPositionComputer_H
#include<Arduino.h>
#define SLAVENUMBER 3
//#define DEBUGSERIAL Serial
#define DISTANCE(x1, y1, x2, y2) sqrt( \
((x1) - (x2)) * ((x1) - (x2)) + \
((y1) - (y2)) * ((y1) - (y2)) )

struct Point2D 
{
	double x;
	double y;
};

class RssiPositionComputer
{
public:
	RssiPositionComputer(){};
	~RssiPositionComputer(){};

	bool distanceToPoint(float d0,float d1,float d2,Point2D* actual_master_point);

private:
	bool intersection (Point2D o1, Point2D o2, double r1, double r2, 
		                 Point2D* p1, Point2D* p2);
public:
private:
	//master_slave_distance[SLAVENUMBER]分别为master--slave0、master--slave1、master--slave2间的距离；
	float master_slave_distance[SLAVENUMBER];
	const float triangle_side_length = 1.0;
	const Point2D slave_point[SLAVENUMBER] = {Point2D({0,0}),Point2D({1,0}),Point2D({0.5,0.866})};
	Point2D possible_intersection[SLAVENUMBER*2];
	Point2D actual_intersection[SLAVENUMBER];
};
#endif