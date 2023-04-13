#include <MsTimer2.h>                  //使用定时器，查在1000ms中的电平变化次数，即上升沿和下降沿的总数；
int encoder_count=0;                   //计数；
int nowaday_Value=0;                   //当前编码器电平；
int last_Value=0;                      //上一次编码器电平；
int sensor;                            //摇杆模块中值；

/*通过编码器计算电机的转速*/
void EncoderDeal()
{
  int speedd;
  speedd = encoder_count * 2;          //编码器一圈为15个孔，30个边沿，1min=60s,60/30=2；
  Serial.println(speedd);
  encoder_count = 0;
  
}

void setup()
{
  Serial.begin(9600);                 //打开串口
  encoder_count = 0;                   //计数清零
  nowaday_Value = analogRead(A3);      //先读取一次编码器的初始电平状态；
  nowaday_Value = compare(nowaday_Value);//判断其电平高低；
  last_Value = nowaday_Value;          //记录；
  sensor = analogRead(A0);             //读取摇杆传感器中值；
  delay(100);
  MsTimer2::set(1000, EncoderDeal);    // 1000ms 定时器；
  MsTimer2::start();
}

void loop()
{
 nowaday_Value = analogRead(A3);               //读取编码器当前电平；
 nowaday_Value = compare(nowaday_Value);       //判断其电平高低；
 if(last_Value!=nowaday_Value)                 //如果电平变化，即遇到上升沿或者下降沿；
    { 
      encoder_count++;                         //计数一次；
      last_Value=nowaday_Value;                //更新上一次电平状态；
    }
 int Output=analogRead(A0);                    //读取摇杆模块电平，并映射输出给电机；
 analogWrite(9,map(Output,sensor,1023,0,255));

}


int compare(int value)                         //防止因电路问题导致的高低电平噪声，比较电平高低；
{
  if( value>=300 )
     value=1;
  else
     value=0;
  return(value);
}

