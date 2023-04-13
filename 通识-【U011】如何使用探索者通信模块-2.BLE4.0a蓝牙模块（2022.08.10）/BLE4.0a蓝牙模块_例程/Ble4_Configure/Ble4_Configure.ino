#include "LedControl.h"                    
LedControl lc=LedControl(12,11,13,1);         //调用8*8点阵函数库,并初始化;
   
void setup() 
  {
   Serial.begin(9600);                       //设置串口通信波特率;
   Serial.print("AT");                       //以下六条语句设置蓝牙模块参数;
   delay(100);
   Serial.print("AT+CLEAR");
   delay(100);
   Serial.print("AT+BAUD0");
   delay(100);
   lc.shutdown(0, false);                     //设置点阵参数;
   lc.clearDisplay(0);
  }

void loop() 
  {
     if(!digitalRead(A0))                     //如果按下"从模式"按键,即A0端口键;
      {
        for(int i = 0;i<5;i++)
          {
            Serial.print("AT");                  //测试一下;
            delay(10);
          }
        Serial.print("AT+ROLE0");            //设置从模式;
        delay(100);
        if( Serial.find("Set:0"))            //判断是否设置成功,成功则(0,0)灯亮;
         {
          lc.clearDisplay (0);
          lc.setLed(0, 0, 0, true);
         }
      }
     if(!digitalRead(A4))                   //如果按下"主模式"按键,即A4端口键;
      {
       for(int i = 0;i<5;i++)
          {
            Serial.print("AT");                 //断开连接或测试;
            delay(10);
          }
       Serial.print("AT+ROLE1");           //设置主模式;
 
       if( Serial.find("Set:1"))            //判断是否设置成功,成功则(0,1)灯亮;
        {
         lc.clearDisplay (0);
         lc.setLed(0, 0, 1, true);
        } 
     }  
  }
