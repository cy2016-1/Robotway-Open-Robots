#include"RssiPositionComputer.h"

bool RssiPositionComputer::intersection (Point2D o1, Point2D o2, 
						                 double r1, double r2, 
						                 Point2D* p1, Point2D* p2)  
{
	double d = DISTANCE(o1.x, o1.y, o2.x, o2.y);

	if (d == 0) return false;
	if (d > (r1 + r2)) return false;
	if (d < r1 - r2 || d < r2 - r1) return false;
	double a = (r1 * r1 - r2 * r2 + d * d) / 2.0 / d;
	double h = sqrt(r1 * r1 - a * a);
	double tx = o1.x + a * (o2.x - o1.x) / d;
	double ty = o1.y + a * (o2.y - o1.y) / d;
	p1->x = tx + h * (o2.y - o1.y) / d;
	p1->y = ty - h * (o2.x - o1.x) / d;
	p2->x = tx - h * (o2.y - o1.y) / d;
	p2->y = ty + h * (o2.x - o1.x) / d;
	return true;
}

bool RssiPositionComputer::distanceToPoint(float d0,float d1,float d2,Point2D* actual_master_point)
{
	master_slave_distance[0] = d0;
	master_slave_distance[1] = d1;
	master_slave_distance[2] = d2;
	for(int i=0;i<SLAVENUMBER;i++)
	{
		while(master_slave_distance[i] + master_slave_distance[(i+1)%SLAVENUMBER]<triangle_side_length)
		{
			master_slave_distance[i] *= 1.1;
			master_slave_distance[(i+1)%SLAVENUMBER] *= 1.1;
			#ifdef DEBUGSERIAL
				DEBUGSERIAL.println("enlarger"+String(i));
			#endif
		}
		while(abs(master_slave_distance[i] - master_slave_distance[(i+1)%SLAVENUMBER])>triangle_side_length)
		{
			if(master_slave_distance[i]>master_slave_distance[(i+1)%SLAVENUMBER])
				master_slave_distance[i] *= 0.9;
			else if(master_slave_distance[i]<master_slave_distance[(i+1)%SLAVENUMBER])
				master_slave_distance[(i+1)%SLAVENUMBER] *= 0.9;
			#ifdef DEBUGSERIAL
				DEBUGSERIAL.println("shrink"+String(i));
			#endif
		}
	 	if(intersection(slave_point[i],slave_point[(i+1)%SLAVENUMBER],master_slave_distance[i],master_slave_distance[(i+1)%SLAVENUMBER],&possible_intersection[2*i],&possible_intersection[2*i+1])==true)
	 	{
	 		float dis_mp0 = abs(DISTANCE(possible_intersection[2*i].x,possible_intersection[2*i].y,slave_point[(i+2)%SLAVENUMBER].x,slave_point[(i+2)%SLAVENUMBER].y) - master_slave_distance[(i+2)%SLAVENUMBER]);
	 		float dis_mp1 = abs(DISTANCE(possible_intersection[2*i+1].x,possible_intersection[2*i+1].y,slave_point[(i+2)%SLAVENUMBER].x,slave_point[(i+2)%SLAVENUMBER].y) - master_slave_distance[(i+2)%SLAVENUMBER]);
	 		if(dis_mp0<dis_mp1)
	 		{
	         	actual_intersection[i].x = possible_intersection[2*i].x;
	         	actual_intersection[i].y = possible_intersection[2*i].y;
	 		}
	        else
	        {
	         	actual_intersection[i].x = possible_intersection[2*i+1].x;
	         	actual_intersection[i].y = possible_intersection[2*i+1].y;
	        }
		}
		else
			return(false);
	}
	for(int i=0;i<SLAVENUMBER;i++)
	{
		#ifdef DEBUGSERIAL
			DEBUGSERIAL.println(possible_intersection[2*i].x);
			DEBUGSERIAL.println(possible_intersection[2*i].y);
			DEBUGSERIAL.println(possible_intersection[2*i+1].x);
			DEBUGSERIAL.println(possible_intersection[2*i+1].y);
			DEBUGSERIAL.println(actual_intersection[i].x);
			DEBUGSERIAL.println(actual_intersection[i].y);
		#endif
		actual_master_point->x += actual_intersection[i].x;
		actual_master_point->y += actual_intersection[i].y;
	}
	actual_master_point->x = actual_master_point->x/SLAVENUMBER;
	actual_master_point->y = actual_master_point->y/SLAVENUMBER;	
	#ifdef DEBUGSERIAL
	    DEBUGSERIAL.println(actual_master_point->x);
		DEBUGSERIAL.println(actual_master_point->y);	
	#endif
	return(true);
}