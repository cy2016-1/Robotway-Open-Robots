/*
 * 接线 tower1: x；tower2: y；tower3: z 从上至下：黑绿红蓝
 * 
 * SENSOR_TOWER1: A0, SENSOR_TOWER2: A3, SENSOR_TOWER3: A4
 * 
 *             tower3
 *           *        *
 *         *            *
 *      tower1  *   *  tower2        
 * 
 * dir: x: 5, y: 6, z: 7, a: 13
 * stp: x: 2, y: 3, z: 4, a: 12
 */

#define EN 8                              //步进电机使能引脚，控制步进电机的开关
#define NUM_STEPPER 3                     //步进电机数量
#define NUM_AXIS 3                        //坐标 x, y, z
#define XYZ_FULL_STEPS_PER_ROTATION 200   //步进电机每周步数
#define XYZ_MICROSTEPS 4                  //步进驱动细分，no
#define LEAD 8                            // mm /丝杠导程


#define DELTA_RADIUS  (DELTA_SMOOTH_ROD_OFFSET - DELTA_EFFECTOR_OFFSET - DELTA_CARRIAGE_OFFSET)          
#define DELTA_DIAGONAL_ROD       115.49        // mm //推杆长度                           //修改 观察托盘运动是否水平，进行数据调整 0.1
#define DELTA_SMOOTH_ROD_OFFSET  112.10        // mm //电机轴圆半径                       //修改 观察托盘运动是否水平，进行数据调整 0.01
#define DELTA_EFFECTOR_OFFSET    42.00          // mm //平台中心到推杆连接处的距离
#define DELTA_CARRIAGE_OFFSET    41.80          // mm //电机轴滑块的距离

#define SENSOR_TOWER1 A0                  //tower1 限位传感器 A0
#define SENSOR_TOWER2 A3                  //tower2 限位传感器 A3
#define SENSOR_TOWER3 A4                  //tower3 限位传感器 A4

#define SIN_60 0.866025                       //sin( 60°)
#define COS_60 0.50                       //cos( 60°)

#define TOWER_1 0
#define TOWER_2 1
#define TOWER_3 2

#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

int stepsPerRevolution = XYZ_FULL_STEPS_PER_ROTATION * XYZ_MICROSTEPS / 2.0;

float delta_radius = DELTA_RADIUS;
float delta_diagonal_rod = DELTA_DIAGONAL_ROD;
float delta_tower1_x = -SIN_60 * delta_radius;     // front right tower
float delta_tower1_y = -COS_60 * delta_radius;     
float delta_tower2_x =  SIN_60 * delta_radius;     // front left tower
float delta_tower2_y = -COS_60 * delta_radius;     
float delta_tower3_x = 0.0;                        // back middle tower
float delta_tower3_y = delta_radius;
float delta_diagonal_rod_2= sq(delta_diagonal_rod); 

boolean serial_notes = false;              //串口打印运行过程结果





