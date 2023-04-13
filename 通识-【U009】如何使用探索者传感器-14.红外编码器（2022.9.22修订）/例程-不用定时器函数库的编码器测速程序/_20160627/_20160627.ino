int encoder_count=0;                    //计数；
int nowaday_Value=0;                    //当前编码器电平；
int last_Value=0;                       //上一次编码器电平；
unsigned long begin_time=0;
unsigned long Now_time=0;
void setup() 
{
  analogWrite(5,150);                  //5号口接电机;
  Serial.begin(9600);                 //打开串口
  nowaday_Value = analogRead(A0);      //先读取一次编码器的初始电平状态；
  nowaday_Value = compare(nowaday_Value);//判断其电平高低；
  last_Value = nowaday_Value;          //记录；
  begin_time = millis();
}

void loop() 
{
   Now_time = millis();
   nowaday_Value = analogRead(A0);             //读取编码器当前电平；    //编码器接A0口;
   nowaday_Value = compare(nowaday_Value);     //判断其电平高低；
   if(last_Value!=nowaday_Value)               //如果电平变化，即遇到上升沿或者下降沿；
    { 
      encoder_count++;                        //计数一次；
      last_Value=nowaday_Value;               //更新上一次电平状态；
     }
   if(Now_time-begin_time>=1000)              //1000ms更新一次速度;
     {
       int speedd = encoder_count*2;          //编码器一圈为15个孔，30个边沿;
       Serial.print(speedd);
       Serial.println("r/min");
       encoder_count = 0;
       begin_time = Now_time;
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

