/***** 舵机-舵机驱动板 连接接口 *****/
#define LEG1_S1 9
#define LEG1_S2 8
#define LEG1_S3 5
#define LEG1_S4 6

#define LEG2_S1 18
#define LEG2_S2 19
#define LEG2_S3 20
#define LEG2_S4 21

#define LEG3_S1 0
#define LEG3_S2 1
#define LEG3_S3 2
#define LEG3_S4 3

#define LEG4_S1 27
#define LEG4_S2 26
#define LEG4_S3 25
#define LEG4_S4 24

/***** 红外传感器-bigfish 连接接口 *****/
#define LEFT_IR_PIN   4
#define RIGHT_IR_PIN  8
#define BACK_IR_PIN   7

/***** 单个动作展示次数 *****/
#define MOTION_TIMES 3

//***** 腿部位置初始高度 *****/
const float Leg_Init_Z_Pos = -125.0;

/***** 肩部舵机初始位置 *****/
const uint Leg1_S4Pos = 165;
const uint Leg2_S4Pos = 20;
const uint Leg3_S4Pos = 10;
const uint Leg4_S4Pos = 165;

/***** 运动周期设置 *****/
const uint Track_Cycle = 200;

/*****
运动轨迹定义
(x1,0,z1) - (x2,0,z2) : 前后行走时腿部方形轨迹端点坐标
(0,y1,z1) - (0,y2,z2) : 左右行走时腿部方形轨迹端点坐标
(x3,y1,z1) - (x4,y2,z2) : 斜向运动时腿部方形轨迹端点坐标
(x4,y1,z1) - (x3,y2,z2) : 斜向运动时腿部方形轨迹端点坐标
*****/
const float track_x1 = -50.0;
const float track_x2 = 50.0;
const float track_x3 = -30.0;
const float track_x4 = 30.0;
const float track_y1 = -30.0;
const float track_y2 = 30.0;
const float track_z1 = -140.0;
const float track_z2 = -90.0;

/***** 矩形轨迹全运动周期中到各顶点时间分配 *****/
const uint track_t1 = Track_Cycle / 24.0;
const uint track_t2 = Track_Cycle / 6.0;
const uint track_t3 = Track_Cycle / 4.0;
const uint track_t4 = Track_Cycle;

/***** 姿态调节相关配置 *****/
#define ADJUST_DELTA_TIME 20 //平衡调节单次时间间隔20ms
const float Leg_Adjust_Delta_Z = 2.0; //原地平衡调节腿部单次运动幅度2mm
const float Track_Adjust_Delta_Z = 0.5; //行进间平衡调节轨迹单次变化幅度0.5mm
const float Balence_Range = 2.0; //平衡灵敏度±2°
const float Leg_Adjust_Min_Z = -160.0; //原地平衡调节腿部最小位置
const float LEG_Adjust_Max_Z = -90.0; //原地平衡调节腿部最大位置
const float Track_Adjust_Min_Z = -15; //行进间平衡调节轨迹最小位置
const float Track_Adjust_Max_Z = 15; //行进间平衡调节轨迹最大位置
