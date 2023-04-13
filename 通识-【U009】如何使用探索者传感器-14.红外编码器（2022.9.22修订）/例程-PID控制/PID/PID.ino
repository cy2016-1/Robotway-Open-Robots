#include <MsTimer2.h>                   //使用定时器，查在1000ms中的电平变化次数，即上升沿和下降沿的总数；
#include <PID_v1.h>                     //使用PID库；
int encoder_count=0;                    //计数；
int nowaday_Value=0;                    //当前编码器电平；
int last_Value=0;                       //上一次编码器电平；
int sensor;                             //摇杆模块中值；
int speedd=0;                           //实际速度；


/*PID设置*/
double Setpoint, Input, Output;
PID myPID(&Input, &Output, &Setpoint,1.6,1,0,DIRECT );       
                                       //设置PID参数，输入输出，目标值，Kp,Ki,Kd,方向DIRECT//REVERSE


/*通过编码器计算电机的转速*/
void EncoderDeal()
{
  speedd = encoder_count * 2;          //编码器一圈为15个孔，30个边沿，1min=60s,60/30=2；
  //Serial.println(Output);
  Serial.print(speedd);
  Serial.println("r");
  encoder_count = 0;
}


void setup()
{
  Serial.begin(9600);                 //打开串口
  encoder_count = 0;                   //计数清零
  nowaday_Value = analogRead(A3);      //先读取一次编码器的初始电平状态；
  nowaday_Value = compare(nowaday_Value);//判断其电平高低；
  last_Value = nowaday_Value;          //记录；
  sensor = analogRead(A4);             //读取摇杆传感器中值；
  myPID.SetMode(AUTOMATIC);            //设置PID自动调节模式；
  MsTimer2::set(1000, EncoderDeal);    // 1000ms 定时器；
  MsTimer2::start();
}


void loop()
{
  nowaday_Value = analogRead(A3);             //读取编码器当前电平；
  nowaday_Value = compare(nowaday_Value);     //判断其电平高低；
  if(last_Value!=nowaday_Value)               //如果电平变化，即遇到上升沿或者下降沿；
    { 
      encoder_count++;                        //计数一次；
      last_Value=nowaday_Value;               //更新上一次电平状态；
     }
  int control=analogRead(A0);                 //读取摇杆电平，以更新PID目标值；
  Setpoint = map(control,sensor,1023,0,150);  //电平映射至速度，并赋给PID目标值；
  Input = speedd;                             //更新”速度“值；
  myPID.Compute();                            //PID计算；
  analogWrite(9,Output);                      //输出PID计算结果至电机；
}


int compare(int value)                        //防止因电路问题导致的高低电平噪声，比较电平高低；
{
  if( value>=300 )
     value=1;
  else
     value=0;
  return(value);
}

