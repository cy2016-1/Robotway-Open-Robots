/* 步进电机下位机控制例程
 * 程序使用 Arduino1.8.2 编写，编译错误请使用较新版本
 * 步进电机方向引脚：dir: x: 44, y: 32, z: 42, a: 30
 * 步进电机步进引脚：stp: x: 45, y: 33, z: 43, a: 31
 * 步进电机使能引脚(低电平有效)：en: 34
 * 步进电机细分设置：0, 2, 4, 8, 16
 * 各细分对应步进电机每周步数：0 --> 200   2 --> 400   4 --> 800   8 --> 1600  16 --> 3200

 * 构建对象，并设置引脚
 * AccelStepper mystepper（1，pinStep，pinDirection）;
 * 步进电机由专用驱动板控制,此例程所用驱动芯片为A4988
 * AccelStepper mystepper（2，pinA，pinB）;
 * 由H桥电路控制的双极性步进电机。
 * AccelStepper mystepper（4，pinA1，pinA2，pinB1，pinB2）;
 * 单极步进电机，由4个晶体管控制。
 * mystepper。setMaxSpeed（stepsPerSecond）;
 * https://www.pjrc.com/teensy/td_libs_AccelStepper.html
 */

#include <AccelStepper.h>
#define EN_PIN 34  //stepper enable pin
#define D_WHEEL 0.058  //Diameter of freighter
#define Variable_Pi 3.14159 //data of π
#define DIAGONAL_L 0.222
#define BODY_WIDTH  0.3139
#define MAIN_STEP 200
#define MICRO_STEP 16  //16 subdivision
#define TOTAL_STEP (MAIN_STEP * MICRO_STEP)   //Step number of one turn of stepper motor
const double Coefficient_of_deviation = 1.285;//小车旋转转动因子
const double kMaxFre = 3200.0;                //n/s
const double CWheel = Variable_Pi * D_WHEEL;  //0.0.1822123739082 m
const double VRatio = TOTAL_STEP/CWheel;      //17561.9247557 step/m
const double V1Ratio = CWheel/TOTAL_STEP;     //m/step
const double kTurningAdjustRate = 1.05;
const double kEquivalentTread = (DIAGONAL_L*DIAGONAL_L/BODY_WIDTH)*kTurningAdjustRate;  //m
const double WRatio = kEquivalentTread*M_PI*VRatio/(2*M_PI);//n step/rad弧度
const double Angle_to_Rad = Variable_Pi/180.0;
AccelStepper stepperx(1, 45, 44);//X轴步进电机引脚及方向引脚定义
AccelStepper steppery(1, 33, 32);//Y轴步进电机引脚及方向引脚定义
AccelStepper stepperz(1, 43, 42);//Z轴步进电机引脚及方向引脚定义
AccelStepper steppera(1, 31, 30);//A轴步进电机引脚及方向引脚定义

void initMotor() //Motor initialization
{
  stepperx.setEnablePin(EN_PIN); //Stepper 
  stepperx.setPinsInverted(false,false,true);//Function prototype:  setPinsInverted (bool directionInvert=false, bool stepInvert=false, bool enableInvert=false)
                                             //Reference website :  https://blog.csdn.net/wenguitao/article/details/104864118
  steppery.setPinsInverted(true,false,true); //ditto
  stepperz.setPinsInverted(false,false,true);//ditto
  steppera.setPinsInverted(true,false,true); //ditto
  stepperx.setMaxSpeed(kMaxFre);//Set the maximum speed of stepper motor【X】
  steppery.setMaxSpeed(kMaxFre);//Set the maximum speed of stepper motor【Y】
  stepperz.setMaxSpeed(kMaxFre);//Set the maximum speed of stepper motor【Z】
  steppera.setMaxSpeed(kMaxFre);//Set the maximum speed of stepper motor【A】
  stepperx.enableOutputs();
}
//vx: m/s; vy: m/s; w: rad/s
void XYSetVel(double vx, double vy, double w)//计算车轮速度
{
  static double increment = 0;
  if(vx>= 0.1){vx=0.1;}
  else if(vx<=-0.1){vx=-0.1;}else{}
  if(vy>= 0.2){vy=0.2;}
  else if(vy<=-0.2){vy=-0.2;}else{}  
  current_vx = vx;
  current_vy = vy;
  current_va = w;  
  double v0 = 0.7071  * VRatio * (vx+vy) ;
  double v1 = 0.7071  * VRatio * (vx-vy) ;
  double w_t = WRatio * w;
  if( (fabs(v1 - w_t)>kMaxFre)||(fabs(v0 + w_t)>kMaxFre)||(fabs(v0 - w_t)>kMaxFre)||(fabs(v1 + w_t)>kMaxFre) )
    return;
  if(vx>0){increment = 390;}
  else if(vx<0){increment = -390;}
  else{increment = 0;}
  stepperx.setSpeed(v1 - w_t);
  steppery.setSpeed(v0 + w_t + increment);
  stepperz.setSpeed(v0 - w_t );
  steppera.setSpeed(v1 + w_t );
}

inline void XYStop() {XYSetVel(0,0,0);stepperx.disableOutputs();}
void XYRun() //步进电机转动函数
{
  stepperx.runSpeed();
  steppery.runSpeed();
  stepperz.runSpeed();
  steppera.runSpeed();
}

void XYRun_time(unsigned long delay_times) //步进电机转动delay_time（单位：s）
{
  unsigned long times = millis();
  while( (millis() - times) < delay_times )
  {
    stepperx.runSpeed();
    steppery.runSpeed();
    stepperz.runSpeed();
    steppera.runSpeed();    
  }
}

void Stepper_move_test()  //小车运动状态测试（动作分别是前进、后退、左平移、右平移、左转、右转）
{
   XYSetVel(Set_Speed_Test,      0,    0    );XYRun_time(Action_implement_delay);delay(Action_wait_for_delay); //forward
   XYSetVel(-Set_Speed_Test,     0,    0    );XYRun_time(Action_implement_delay);delay(Action_wait_for_delay); //back
   XYSetVel(0,       Set_Speed_Test,   0    );XYRun_time(Action_implement_delay);delay(Action_wait_for_delay); //left_translation
   XYSetVel(0,      -Set_Speed_Test,   0    );XYRun_time(Action_implement_delay);delay(Action_wait_for_delay); //right_translation
   XYSetVel(0,        0,   Set_Speed_Test   );XYRun_time(Action_implement_delay);delay(Action_wait_for_delay); //left
   XYSetVel(0,        0,   -Set_Speed_Test  );XYRun_time(Action_implement_delay);delay(Action_wait_for_delay); //right 
}

void XYRead()
{
  static long step_count[4] = {0,0,0,0};
  static long d_step[4] = {0,0,0,0};
  static unsigned long last_time = micros();
  static long tt = 0;
  d_step[0] = stepperx.currentPosition()-step_count[0];
  d_step[1] = steppery.currentPosition()-step_count[1];
  d_step[3] = stepperz.currentPosition()-step_count[2];
  d_step[2] = steppera.currentPosition()-step_count[3];
  step_count[0] = stepperx.currentPosition();
  step_count[1] = steppery.currentPosition();
  step_count[2] = stepperz.currentPosition();
  step_count[3] = steppera.currentPosition(); 
  if( (d_step[0]|d_step[1]|d_step[2]|d_step[3])==0 )
  {
    last_time = micros();
    current_vx = 0;
    current_vy = 0;
    current_va = 0;
    return;
  }
  else
  {
    float dt = (micros()-last_time)/1000000.0;
    float dx,dy,da;
    dx = current_vx * dt;
    dy = current_vy * dt;
    da = current_va * dt / Coefficient_of_deviation;
    current_x += dx;
    current_y += dy;
    current_a += da;
    last_time = micros();
  }
}
