//此程序用于一对一式蓝牙通信,从模式程序,maple韩枫编写;参考资料bluetooth40.pdf,HMDongle40.pdf;此程序与一对多式蓝牙通信被传染对象程序一模一样;
#include"LedControl.h"
LedControl lc=LedControl(12,11,13,1); 
                                   
void setup()
{
  delay(1000);
  Serial.begin(9600);              //以下注释掉的6行为参数配置行,但因为硬件响应原因容易导致设置失败,从而影响程序的执行,我采用在端口软件提前设置好.
//  Serial.print("AT+ROLE0");       //设置自身为从模块;
//  delay(1000);
//  Serial.print("AT+IMME0");       //设置自身上点即工作;
//  delay(1000);
//  Serial.print("AT+MODE2");       //设置自身为远控加透传模式;
//  delay(1000);
  lc.shutdown(0, false);     
  lc.clearDisplay (0);  
  while (Serial.available())      //消除串口缓冲区多余数据,以便执行loop;   
  Serial.read();             

}

void loop() 
{
  while (Serial.available())      //收到数据工作;
  {
    int i=Serial.read();         //存储;
    delay(100);
    lc.clearDisplay (0);
    switch(i)                     //判断收到的数据;
     {
      case 48:{lc.setLed(0, 0, 0, true); Serial.print("ok");}break;//点亮相应的灯并回应主模块;
      case 49:{lc.setLed(0, 0, 1, true); Serial.print("ok");}break;
      case 50:{lc.setLed(0, 0, 2, true); Serial.print("ok");}break;
      case 51:{lc.setLed(0, 0, 3, true); Serial.print("ok");}break;
      case 52:{lc.setLed(0, 0, 4, true); Serial.print("ok");}break;
      case 53:{lc.setLed(0, 0, 5, true); Serial.print("ok");}break;
      case 54:{lc.setLed(0, 0, 6, true); Serial.print("ok");}break;
      case 55:{lc.setLed(0, 0, 7, true); Serial.print("ok");}break;
      default:;break;
   }
  }
}
