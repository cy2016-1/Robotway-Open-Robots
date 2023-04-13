/*********************接线方式 
TCS3473x  Arduino_Uno 
  SDA         A4
  SCL         A5
  VIN         5V
  GND         GND
*************************/
#include <Wire.h>        //调用IIC库函数
#include "MH_TCS34725.h" //调用颜色识别传感器库函数
#include <Adafruit_GFX.h>    
#include <Adafruit_SSD1306.h>//调用oled屏幕库函数
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define OLED_RESET 4
SSD1306 display(OLED_RESET);
//颜色传感器不同通道值设置
MH_TCS34725 tcs = MH_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X); //设置颜色传感器采样周期50毫秒
//MH_TCS34725 tcs = MH_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);//设置颜色传感器采样周期700毫秒
//MH_TCS34725 tcs = MH_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_60X);//设置颜色传感器采样周期50毫秒（不推荐）
//MH_TCS34725 tcs = MH_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_16X);//设置颜色传感器采样周期50毫秒（不推荐）
enum{Forward=1,Back,Left,Right,Stop};//定义小车状态


void setup() {
  Serial.begin(115200);  //开启串口，并设置串口波特率位115200
  Serial.println("Color View Test!"); //串口打印：Color View Test!
  //检测是否有颜色传感器模块
  if (tcs.begin()) {                 //如果检测到颜色传感器模块
    Serial.println("Found sensor");  //串口打印 Found sensor
  } else {                           //如果没有检测到颜色传感器模块
    Serial.println("No TCS34725 found ... check your connections");//串口打印：没有找到颜色识别传感器模块
    while (1); // halt! //程序陷入死循环
  }
  Motor_pin_init();//直流电机引脚初始化
  delay(500);
  Oled_Init();  //oled屏幕初始化
  delay(500);
}

//oled屏幕显示颜色传感器读取的物体颜色
void loop() {
  Get_Color_Data();
}
