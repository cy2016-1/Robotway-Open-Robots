   #include "LedControl.h"
   int pin[3]={A4,A3,A0};
   int state[3]={1};
   LedControl lc=LedControl(12,11,13,1);  //初始化设备，设置DIN（dataPin）、CLK、CS的IO口及连接设备数量（既有多少块屏）并定义一个对象
                                          //本例中：设置DIN口对应Arduino上12口;设置CLK口对应Arduino上11口;设置CS口对应Arduino上13口;设备连接数1
   void setup()
  {
    Serial.begin(9600);  
    lc.shutdown(0,false);     //设置LED0节电模式关闭
    lc.setIntensity(0,15);    //设置LED0可显示的行数，可设置0-7，超过7变为8的余数
    lc.clearDisplay(0);       //设备0清屏
                              //使用0-7表示LED的1-8行，使用0，1表示LED亮灭
    lc.setRow(0,0,10000001);  //设置LED0第一行8个LED状态
    lc.setRow(0,7,10000001);  //设置LED0第八行8个LED状态
    delay(1000);   //LED灯亮1秒
    lc.clearDisplay(0);   //设备0清屏
  }
    void loop()
  {
    lc.clearDisplay(0); 
    for(int i = 0; i < 3;i++)
    {
      state[i]=!(digitalRead(pin[i]));         //state[i]表示第i个传感器触发状态，1表示触发，0表示未触发
      lc.setColumn(0, 6-2*i, byte(255*state[i]));  //设置LED0 6-2i 列8个LED的开关状态，与setRow输出的图形正好旋转90度，byte(255*state[i])表示 传感器触发状态*255 后转二进制来控制LED0列中每个灯的亮灭
    }
  }
