/*为使同学们学习到编码器测速知识,所以此程序是在编码器测速实验基础上修改而成的,路程计算较简单,故误差较大,有兴趣的同学可以利用累加方式精确计算.
#include <MsTimer2.h>                   //使用定时器2，查在1000ms中的电平变化次数，即上升沿和下降沿的总数；
#include <Wire.h>                       //调用IIC函数库;
#include <MultiLCD.h>                   //调用LED屏函数库
LCD_SSD1306 lcd;                        //定义一个LED屏对象;
int encoder_count=0;                    //计数；
int nowaday_Value=0;                    //当前编码器电平；
int last_Value=0;                       //上一次编码器电平；
int speedd=0;                           //实际速度；
int timerNum=0;
bool dis=true;

/*通过编码器计算电机的转速*/
void EncoderDeal()
{
  speedd = encoder_count;          //编码器一圈为15个孔，30个边沿;
  encoder_count = 0;
  timerNum++;
  dis=true;
}


void setup()
{ 
  lcd.begin();                         //LED屏显示;
  analogWrite(5,150);                  //设置电机速度;
  Serial.begin(9600);                 //打开串口
  encoder_count = 0;                   //计数清零
  nowaday_Value = analogRead(A0);      //先读取一次编码器的初始电平状态；
  nowaday_Value = compare(nowaday_Value);//判断其电平高低；
  last_Value = nowaday_Value;          //记录；
  MsTimer2::set(2000, EncoderDeal);    // 2000ms 定时器；
  MsTimer2::start();                   //定时器开始计时;
}


void loop()
{
  if(dis)                                     //如果速度更新,刷新LED屏数据;
    {display();
     dis=false;}
  nowaday_Value = analogRead(A0);             //读取编码器当前电平；
  nowaday_Value = compare(nowaday_Value);     //判断其电平高低；
  if(last_Value!=nowaday_Value)               //如果电平变化，即遇到上升沿或者下降沿；
    { 
      encoder_count++;                        //计数一次；
      last_Value=nowaday_Value;               //更新上一次电平状态；
     }
}


int compare(int value)                        //防止因电路问题导致的高低电平噪声，比较电平高低；
{
  if( value>=300 )
     value=1;
  else
     value=0;
  return(value);
}


void display()                               //LED屏显示函数;
  {
      lcd.clear();                           //清屏;
      Serial.print(speedd);                 //串口显示;
      Serial.print("r/min");
      lcd.setCursor(0, 2);                   //设置LED屏光标位置;
      lcd.printLong(speedd, FONT_SIZE_LARGE);.//设置字体大小;
      lcd.setCursor(50, 3);            
      lcd.print("r/min");
      int distance=timerNum*speedd/60*5*3;  //在整个程序中只设置过一次速度（150),故默认小车匀速行驶,speedd恒定;车轮直径5cm，为了显示方便，π取3；
      Serial.print(distance);
      Serial.println("cm");
      lcd.setCursor(0, 5);       
      lcd.printLong(distance, FONT_SIZE_LARGE);
      lcd.setCursor(50, 6);
      lcd.print("cm");
  }
