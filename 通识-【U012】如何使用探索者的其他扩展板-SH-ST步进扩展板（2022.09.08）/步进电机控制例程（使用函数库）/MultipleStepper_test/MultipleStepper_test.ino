/* 多步进电机控制例程
 * 程序使用 Arduino1.8.2 编写，编译错误请使用较新版本
 * 步进电机方向引脚：
 * dir: x: 5, y: 6, z: 7, a: 13
 * 步进电机步进引脚：
 * stp: x: 2, y: 3, z: 4, a: 12
 * 步进电机使能引脚(低电平有效)：
 * en: 8
 * 步进电机细分设置：0, 2, 4, 8, 16
 * 各细分对应步进电机每周步数：
 * 0 --> 200
 * 2 --> 400
 * 4 --> 800
 * 8 --> 1600
 * 16 --> 3200
 */

#include <AccelStepper.h>
#include <MultiStepper.h>
//注意AccelStepper和MultiStepper的库文件需要安装，放到arduino软件目录下libraries文件夹内
#define EN 8     

//步进电机速度,值越大速度越快
#define SPEED_X 1000
#define SPEED_Y 1000
#define SPEED_Z 1000
#define SPEED_A 1000

//步进电机转动步数,每周步数根据细分调整,现在设置的是X全步进（无细分），Y轴8细分，Z轴8细分，A轴16细分
#define STEPS_X 200  
#define STEPS_Y 1600
#define STEPS_Z 1600
#define STEPS_A 3200

void stepperSet();    //步进电机速度设置函数
void stepperMove();   //步进电机步进函数

AccelStepper stepper_x(1, 2, 5);    // X
AccelStepper stepper_y(1, 3, 6);    // Y
AccelStepper stepper_z(1, 4, 7);    // Z
AccelStepper stepper_a(1, 12, 13);  // A

MultiStepper steppers;

void setup() {
  Serial.begin(9600);
  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);

  stepperSet(SPEED_X, SPEED_Y, SPEED_Z, SPEED_A);
  delay(1000);
}

void loop() {
  stepperMove(-STEPS_X, -STEPS_Y, -STEPS_Z, -STEPS_A);          
  delay(200);
  stepperMove(STEPS_X, STEPS_Y, STEPS_Z, STEPS_A);           
  delay(200);
}

void stepperSet(long v_x, long v_y, long v_z, long v_a){
  stepper_x.setMaxSpeed(v_x);          
  stepper_x.setAcceleration(400.0);  
  stepper_y.setMaxSpeed(v_y);
  stepper_y.setAcceleration(400.0);
  stepper_z.setMaxSpeed(v_z);
  stepper_z.setAcceleration(400.0);
  stepper_a.setMaxSpeed(v_a);
  stepper_a.setAcceleration(400.0);

  steppers.addStepper(stepper_x);
  steppers.addStepper(stepper_y);
  steppers.addStepper(stepper_z);
  steppers.addStepper(stepper_a);
}

void stepperMove(long _x, long _y, long _z, long _a){
    long positions[4];
    positions[0] = _x;
    positions[1] = _y;
    positions[2] = _z;
    positions[3] = _a;

    steppers.moveTo(positions);
    steppers.runSpeedToPosition();
    
    stepper_x.setCurrentPosition(0);
    stepper_y.setCurrentPosition(0);
    stepper_z.setCurrentPosition(0);
    stepper_a.setCurrentPosition(0);
}
