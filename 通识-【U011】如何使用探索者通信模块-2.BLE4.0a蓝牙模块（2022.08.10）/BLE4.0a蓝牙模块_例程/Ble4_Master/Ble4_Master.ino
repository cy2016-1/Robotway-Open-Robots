//此程序用于一对一式蓝牙通信,主模块,maple韩枫编写;参考资料bluetooth40.pdf,HMDongle40.pdf;
#include"LedControl.h"
LedControl lc=LedControl(12,11,13,1); 
int i=0;              //要发送的数据;
void setup()
{
  Serial.begin(9600);
  lc.shutdown(0, false);         
  delay(3000);
}

void loop() 
{
    delay(500);
    lc.clearDisplay (0);
    Serial.print(i);      //发送出去;
    lc.setLed(0, 0, i, true);
    delay(50);      
    for(int k=0;k<3;k++)       
    Serial.read();       //消除串口缓冲区的数据"i","ok",以便执行serialEvent事件;   
    delay(100);
}

void serialEvent()        //如果从模块响应了我的发送行为,数据++;
{      
  i++;
  if(i==8)
  i=0;
}
