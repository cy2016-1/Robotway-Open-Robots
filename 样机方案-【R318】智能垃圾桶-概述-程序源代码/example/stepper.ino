/* 步进电机方向引脚：
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

#include "Arduino.h"         //arduino基本库函数
#include <AccelStepper.h>  //控制单个步进电机的库函数
#include <MultiStepper.h>  //将单个步进电机添加到组中，进而控制多个步进电机的库函数

#define EN 8          //步进电机驱动板（即A4988）的使能引脚
#define MAIN_STEP 200 //步进电机每圈步数
#define MICRO_STEP 16 //驱动细分数
#define TOTAL_STEP (MAIN_STEP * MICRO_STEP) //16细分下步进电机每圈步数为3200步（即16细分下步进电机转一圈需要走3200步）

AccelStepper stepper_x(1, 2, 5);  //设置X轴步进电机引脚和方向（这里可以理解为：步进电机由专用驱动板控制的固定方式,此例程所用驱动芯片为A4988）
MultiStepper steppers;  //设置步进电机组对象

void initMotor(){
  pinMode(EN, OUTPUT);   //将使能引脚设置为输出模式
  digitalWrite(EN, LOW); //拉低步进电机扩展板使能引脚（这里可以理解为：让步进电机扩展板开始工作）
  steppers.addStepper(stepper_x); //将X轴步进电机添加到步进电机组中（这里可以理解为：将单个步进电机添加到步进电机组中）
  stepperSet(V_MAX);  //设置步进电机速度
}

//x
void move(double x){ 
  double step_x;     
  x *= TOTAL_STEP;    //得到x步进电机要转动的总步数
  step_x = -x;        //这里的 -x 前的负号表示方向，如果没有负号，表示正转，如果有负号，表示反转。     
  stepperMove(step_x);//步进电机要转动   step_x/3200   圈
}

void stepperSet(double _v){
  stepper_x.setMaxSpeed(_v);//设置步进电机能达到的最大速度
}


//步进电机转动的函数
void stepperMove(long _x){   
    long positions[2]; //定义数组
    positions[0] = _x; //将步进电机要走的圈数存储到数组中   
    steppers.moveTo(positions);  //步进电机准备要走的步数
    steppers.runSpeedToPosition();//步进电机开始转动到指定的位置（这里的位置即步进电机准备要走的圈数）
    stepper_x.setCurrentPosition(0);
    //将转动一圈后的步进电机位置定为起点位置，如果下次转动2圈或者0.3圈，步进电机将把转动2圈后的位置重新定为步进电机的起点位置）。
}
