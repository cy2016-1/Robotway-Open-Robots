/*------------------------------------------------------------------------------------
  版权说明：Copyright 2022 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2022-5-30 https://www.robotway.com/
  -------------------------------------------------------------------------------------*/
//救援指挥中心例程
//配置模块：(模块在配置时与正常工作时TX、RX线序不同，请注意)
//第一步：使用AT指令将所使用的两个模块设置为主模式；所有模块波特率全部为默认的9600，并记录待救援设备从模块的地址(AT+ADDR?);
//第二步：将主模块在未连接时清除之前的配对信息(AT+CLEAR),再设置其工作类型为类型1(AT+IMME即上后处于等待状态，收到AT+START,AT+DISC,AT+CONNL等指令后开始工作）；
//开始工作：
//第三步：将所有模块上电(主模块参考控制中心的连接进行接线，待救援设备从模块参考相应的连接); 
//第四步：将本程序下载进MEGA2560中，将从模块分别摆开，观察显示屏数据；

#include <Arduino.h>
#include <Wire.h>
#include <MultiLCD.h>

#define DATA_SERIAL Serial  //信息打印串口
#define HUMAN_SERIAL Serial1 //待救援数据
#define ROBOT_SERIAL Serial2 //救援机器人数据

#define CMD_CON "AT+CON"
#define CMD_DIS_CON "AT"
#define CMD_START "AT+START"

LCD_SSD1306 lcd;

String human_address = "F83002253650";  //待救援设备地址
String robot_address = "F83002253178";  //救援机器人设备地址

String human_point = "[ax: 0 , ay: 0]";
String robot_point = "[bx: 0 , by: 0]";

void setup() {
  DATA_SERIAL.begin(9600);
  HUMAN_SERIAL.begin(9600);
  ROBOT_SERIAL.begin(9600);
  lcd.begin();
  master_init();
}

void loop() {
  read_human_point();
  read_robot_point();
  point_display();
}

void connect_ble(){
  
  //连接待救援设备地址
//  HUMAN_SERIAL.print(CMD_START);delay(1000);
  HUMAN_SERIAL.print(CMD_DIS_CON);delay(200);
  HUMAN_SERIAL.print(CMD_CON + human_address);
  //连接救援机器人设备地址
  ROBOT_SERIAL.print(CMD_DIS_CON);delay(200);
  ROBOT_SERIAL.print(CMD_CON + robot_address);
  
}

//读取待救援位置
void read_human_point(){
  while(1){
    String str;
    while(HUMAN_SERIAL.available() > 0){
      str = HUMAN_SERIAL.readStringUntil('\n');
      str.trim();  
    }
    if(!str.equals("")){
      Serial.println(str);
      human_point = str;
      break;
    }
  }
}

//读取救援机器人位置
void read_robot_point(){
  while(1){
    String str;
    while(ROBOT_SERIAL.available() > 0){
      str = ROBOT_SERIAL.readStringUntil('\n');
      str.trim();  
    }
    if(!str.equals("")){
      Serial.println(str);
      robot_point = str;
      break;
    }
  }
}

void point_display(){
  lcd.clear();
  lcd.setCursor(10, 1);
  lcd.print("a: human  b: robot");
  lcd.setCursor(20, 3);
  lcd.print(human_point);
  lcd.setCursor(20, 5);
  lcd.print(robot_point);
  
}

void master_init(){
  lcd.clear();
  lcd.setCursor(25, 3);
  lcd.print("Hello World!");
  delay(1000);
  point_display();
  connect_ble();
  while(true){
    if(HUMAN_SERIAL.available() > 0 || ROBOT_SERIAL.available() > 0)
      break;
  }
}
