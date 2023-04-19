#ifndef DELTA_CONFIG_H
#define DELTA_CONFIG_H

#define DELTA_RADIUS  (DELTA_SMOOTH_ROD_OFFSET - DELTA_EFFECTOR_OFFSET - DELTA_CARRIAGE_OFFSET)          
#define DELTA_DIAGONAL_ROD       150.98        // mm //推杆长度                           //修改 观察托盘运动是否水平，进行数据调整 0.1
#define DELTA_SMOOTH_ROD_OFFSET  117.51        // mm //电机轴圆半径                       //修改 观察托盘运动是否水平，进行数据调整 0.01
#define DELTA_EFFECTOR_OFFSET    25.50          // mm //平台中心到推杆连接处的距离
#define DELTA_CARRIAGE_OFFSET    27.50          // mm //电机轴滑块的距离
#define DELTA_AXIS_NONE 136.504 //mm //坐标为0
#define DELTA_DIALOGNAL_AREA 75 //mm //最大运动范围直径

#define DELTA_LIMIT_X 

#define SIN_60 0.866025                   //sin( 60°)
#define COS_60 0.50                       //cos( 60°)
#define COS_45_2 0.707107                   //cos( 45°)/2

#define TOWER_1 0
#define TOWER_2 1
#define TOWER_3 2

float delta_radius = DELTA_RADIUS;
float delta_diagonal_rod = DELTA_DIAGONAL_ROD;
float delta_limit_xy_2 = DELTA_DIALOGNAL_AREA * COS_45_2 / 2; //25....mm

float delta_tower1_x = -SIN_60 * delta_radius;     // front right tower
float delta_tower1_y = -COS_60 * delta_radius;     
float delta_tower2_x =  SIN_60 * delta_radius;     // front left tower
float delta_tower2_y = -COS_60 * delta_radius;     
float delta_tower3_x = 0.0;                        // back middle tower
float delta_tower3_y = delta_radius;
float delta_diagonal_rod_2= sq(delta_diagonal_rod); 
float delta_axis_none = DELTA_AXIS_NONE;


#endif
