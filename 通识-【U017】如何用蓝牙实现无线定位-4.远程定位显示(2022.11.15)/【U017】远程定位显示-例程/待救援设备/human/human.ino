/*------------------------------------------------------------------------------------
  版权说明：Copyright 2022 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2022-5-30 https://www.robotway.com/
  -------------------------------------------------------------------------------------*/
//待救援主控例程
//配置模块：(模块在配置时与正常工作时TX、RX线序不同，请注意)
//第一步：使用AT指令将所使用的两个模块其中一个设置为主模式，另外一个为从模式；所有模块波特率全部为默认的9600，并记录主从模块的地址(AT+ADDR?);
//第二步：将主模块在未连接时清除之前的配对信息(AT+CLEAR),再设置其工作类型为类型1(AT+IMME即上后处于等待状态，收到AT+START,AT+DISC,AT+CONNL等指令后开始工作）；
//开始工作：
//第三步：将所有模块上电(主从模块按照上面介绍的连接方式连接即可); 
//第四步：将本程序下载进MEGA2560中，将从模块分别摆开，观察显示屏数据；


/*********从设备地址********/
//  "D8A98B788750",
//  "D8A98B788732",
//  "380B3CFFC5B0"
/*********从设备地址********/

/**********头文件***************/
#include <Arduino.h>
#include <Wire.h>
#include <MultiLCD.h>
#include <RssiPositionComputer.h>

/***********宏定义**************/
//#define DEBUG_SERIAL Serial  //打印信息串口
#define CON_SERIAL Serial1    //蓝牙通信串口
#define SEND_SERIAL Serial2   //数据发送串口

#define CMD_CON "AT+CON"
#define CMD_DIS_CON "AT"
#define CMD_GET_RSSI "AT+RSSI?"


RssiPositionComputer myPositionComputer;
Point2D master_point;

//基站数量
#define SLAVENUMBER 3
//基站地址
String BLUETOOTHADDRESS[3] = {
  "D8A98B788750",
  "D8A98B788732",
  "380B3CFFC5B0"
};

//位置发送蓝牙地址
// F83002253650

String search_result_string[SLAVENUMBER] = {""};
String rssi[SLAVENUMBER] = {""};
float distance[SLAVENUMBER] = {};


void setup() {
  #if defined(DEBUG_SERIAL)
  DEBUG_SERIAL.begin(9600);
  #endif
  CON_SERIAL.begin(9600);
  SEND_SERIAL.begin(9600);
  delay(1000);
  init_ble();

}

void loop() {
  read_ble(BLUETOOTHADDRESS);
  to_axis(distance, &master_point);

}

//读取串口
String serial_read(int _len){
  String data = "";
  int len = 0;
  unsigned long t = millis() + 500;
  while(1)
  {
    while(CON_SERIAL.available()){
      char c = CON_SERIAL.read();
      data += c;
      len++;
    }  
    if(len == _len){
       break;
    }
    if(millis() > t) 
      break;
  }  

  #if defined(DEBUG_SERIAL)
  //DEBUG_SERIAL.println(data);
  #endif

  return data;
}

//初始化
void init_ble(){
  CON_SERIAL.print(CMD_DIS_CON);delay(100);
  serial_read(2);
}

//获取设备 RSSI
void read_ble(String * address){
  for(int i=0;i<SLAVENUMBER;i++){
    CON_SERIAL.print(CMD_DIS_CON);delay(100);
    serial_read(2);
    CON_SERIAL.print(CMD_CON + address[i]);
    serial_read(8);
    delay(500);
    CON_SERIAL.print(CMD_GET_RSSI);
  
    String rssi_str = serial_read(10);
    String _rssi = rssi_str.substring(7, rssi_str.length());

    //rssi
    rssi[i] = _rssi;
    //distance
    distance[i] = rssiToDistance(rssi[i].toFloat());

    #if defined(DEBUG_SERIAL)
      DEBUG_SERIAL.println("BLE_" + String(i) + ": " + rssi[i]);
      //DEBUG_SERIAL.println("BLE_" + String(i) + ": " + distance[i]);
    #endif

    //delay(800);
  }
  
}

//计算距离
float rssiToDistance(float rssi){
  float dis = 0;
  //dis = pow(10.0,((abs(rssi)-56)/10.0/1.05));
  dis = pow(10.0,((abs(rssi)-56)/5.0/1.65));
  return dis;  
}

//转换为2d坐标x,y
void to_axis(float * dis, Point2D* actual_master_point){
   //myPositionComputer.distanceToPoint(*dis,*(dis+1),*(dis+2),actual_master_point);
   myPositionComputer.distanceToPoint(*dis,*(dis+1),random(0,77),actual_master_point);

   int x = master_point.x*100;
   int y = master_point.y*100;

   char point[100];

   sprintf(point, "[ax:%3d,ay:%3d]\n",abs(x),abs(y));

   #if defined(DEBUG_SERIAL)
      DEBUG_SERIAL.println(point);
   #endif

   SEND_SERIAL.print(point);
}
