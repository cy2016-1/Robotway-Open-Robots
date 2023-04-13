/*******************************************************************************************
实验需求:
         用颜色传感器实现颜色识别。

实现思路：
         程序的整体思路为：在机械臂前方安装颜色传感器，如果检测的物料的颜色为红色，机械臂将
         物体放在机械臂的左侧，如果检测的物料的颜色为蓝色，机械臂将物体放在机械臂的右侧，
         否则，机械臂不动作。
实验接线:
         最上端的机械爪舵机接D4;
         中间的机械身躯舵机接D7；
         最下端的机械底座舵机接D11；
         颜色传感器的接线为         
         S1  S2  5V  GND        S3   S2   5V   GND        OUT   LED   5V   GND
         |   |   |    |         |    |    |     |          |     |    |     |
         A0  A1  5V  GND        A5   A4   5V   GND         D2    A3   5V   GND
********************************************************************************************/



//颜色传感器原理
/*首先进行白平衡，把一个白色物体放置在TCS3200颜色传感器之下，两者相距10mm左右，点亮传感器上的
4个白光LED灯，用Arduino控制器的定时器设置一固定时间1s，然后选通三种颜色的滤波器，让被测物体反
射光中红、绿、蓝三色光分别通过滤波器，计算1s时间内三色光分别对应的TCS3200的输出脉冲数，再通过
算式得到白色物体RGB值255与三色光脉冲数的比例因子。有了白平衡后，得到的RGB比例因子，则其他颜色
物体反射光中红、绿、蓝三色光对应的1s内TCS3200输出信号脉冲数乘以R、G、B比例因子，就可换算出被测
物体的RGB标准值。*/

#include "TimerOne.h"    //颜色传感器需要用到的定时函数库
#include<ServoTimer2.h>  //舵机驱动需要的函数库
ServoTimer2 myservo[3];  //舵机声明
#define servo_num 3      //舵机数量
#define Servo_Speed  20  //舵机速度

#define Upward_servo_close 66   //机械爪闭合的角度值
#define Upward_servo_open 115   //机械爪张开的角度值

#define Middle_servo_down 105   //机械臂的初始角
#define Middle_servo_init 85    //机械臂的初始角
#define Middle_servo_left 10    //机械臂向左偏的角度
#define Middle_servo_left1 50   //机械臂向左偏的角度

#define Down_servo_middle 75   //机械底座初始角度值
#define Down_servo_left 5      //机械底座向左偏的角度值
#define Down_servo_right 145   //机械底座向右偏的角度值


int servo_pin[3]={4,7,11}; //定义舵机引脚号
float value_init[3]={Upward_servo_open, Middle_servo_left, Down_servo_middle};//舵机初始角度
int f=20;   //舵机从角度A转到角度B分的分数

//把TCS3200颜色传感器各控制引脚连到Arduino数字端口 
#define S0     A0   //物体表面的反射光越强，TCS3002D的内置振荡器产生的方波频率越高，
#define S1     A1   //S0和S1的组合决定输出信号频率比率因子，比例因子为2%
                    //比率因子为TCS3200传感器OUT引脚输出信号频率与其内置振荡器频率之比
#define S2     A4   //S2和S3的组合决定让红、绿、蓝，哪种光线通过滤波器
#define S3     A5
#define OUT    2  	//TCS3200颜色传感器输出信号输入到Arduino中断0引脚，并引发脉冲信号中断
                  	//在中断函数中记录TCS3200输出信号的脉冲个数
#define LED    A3   //控制TCS3200颜色传感器是否点亮
int   g_count = 0;    // 计算与反射光强相对应TCS3200颜色传感器输出信号的脉冲数
// 数组存储在1s内TCS3200输出信号的脉冲数，它乘以RGB比例因子就是RGB标准值
int   g_array[3];   
int   g_flag = 0;     //滤波器模式选择顺序标志
float g_SF[3];       // 存储从TCS3200输出信号的脉冲数转换为RGB标准值的RGB比例因子

// 初始化TSC3200各控制引脚的输入输出模式
//设置TCS3002D的内置振荡器方波频率与其输出信号频率的比例因子为2%
void TSC_Init()
{
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);
  pinMode(LED, OUTPUT); 
  digitalWrite(S0, LOW);  
  digitalWrite(S1, HIGH); 
}
 
//选择滤波器模式，决定让红、绿、蓝，哪种光线通过滤波器 
void TSC_FilterColor(int Level01, int Level02)
{
  if(Level01 != LOW)
    Level01 = HIGH; 
  if(Level02 != LOW)
    Level02 = HIGH; 
  digitalWrite(S2, Level01); 
  digitalWrite(S3, Level02); 
}
//中断函数，计算TCS3200输出信号的脉冲数 
void TSC_Count()
{
  g_count ++ ;
}
//定时器中断函数，每1s中断后，把该时间内的红、绿、蓝三种光线通过滤波器时，
//TCS3200输出信号脉冲个数分别存储到数组g_array[3]的相应元素变量中
void TSC_Callback()
{
  switch(g_flag)
  {
    case 0: 
         TSC_WB(LOW, LOW);              //选择让红色光线通过滤波器的模式
         break;
    case 1:
         g_array[0] = g_count;       //存储1s内的红光通过滤波器时，TCS3200输出的脉冲个数
         TSC_WB(HIGH, HIGH);         //选择让绿色光线通过滤波器的模式
         break;
    case 2:
         g_array[1] = g_count;       //存储1s内的绿光通过滤波器时，TCS3200输出的脉冲个数
         TSC_WB(LOW, HIGH);          //选择让蓝色光线通过滤波器的模式
         break;
 
    case 3:
         g_array[2] = g_count;       //存储1s内的蓝光通过滤波器时，TCS3200输出的脉冲个数
         TSC_WB(HIGH, LOW);             //选择无滤波器的模式   
         break;
   default:
         g_count = 0;    //计数值清零
         break;
  }
}
//设置反射光中红、绿、蓝三色光分别通过滤波器时如何处理数据的标志
//该函数被TSC_Callback( )调用
void TSC_WB(int Level0, int Level1)     
{
  g_count = 0;   //计数值清零
  g_flag ++;     //输出信号计数标志
  TSC_FilterColor(Level0, Level1); //滤波器模式
  Timer1.setPeriod(100000);      //设置输出信号脉冲计数时长1s
}
//初始化
void setup()
{
  TSC_Init();
  Serial.begin(9600); //启动串行通信
  Timer1.initialize(100000);   // defaulte is 1s
  Timer1.attachInterrupt(TSC_Callback); //设置定时器1的中断，中断调用函数为TSC_Callback() 
  //设置TCS3200输出信号的上跳沿触发中断，中断调用函数为TSC_Count()
  attachInterrupt(0, TSC_Count, RISING);  
  digitalWrite(LED, HIGH);//点亮LED灯
//  delay(1500); //延时4s，以等待被测物体红、绿、蓝三色在1s内的TCS3200输出信号脉冲计数
  //通过白平衡测试，计算得到白色物体RGB值255与1s内三色光脉冲数的RGB比例因子


  g_SF[0] = 0.53;     //红色光比例因子
  g_SF[1] = 0.65;    //绿色光比例因子
  g_SF[2] = 0.54;    //蓝色光比例因子
  //红、绿、蓝三色光对应的1s内TCS3200输出脉冲数乘以相应的比例因子就是RGB标准值
    reset();
}
//主程序 
int Now_Color = 0;   //存储上一次颜色传感器检测的数值
int Last_Color = 0;  //存储当前颜色传感器检测的数值

void loop()
{ 
    Last_Color = Color_Detection();
    Now_Color  = Color_Detection();
    if( Last_Color == Now_Color) //如果两次检测的数值相同
                                 //（这里是为了防止颜色传感器检测出错，所以检测了两次）
    {
      switch(Now_Color)
      {
        case 1:
               Serial.print("Red"); //如果检测到的物料为红色，将物料放到机械臂的左侧
               Servo_Left();
               Now_Color = 0; Last_Color = 0;
               break;     
        case 2:
               Serial.print("Blue");//如果检测到的物料为蓝色，将物料放到机械臂的右侧
               Servo_Right();
               Now_Color = 0; Last_Color = 0;
               break;
        case 3:
               Serial.print("NONE");//否则，机械臂不动作；
               Serial.println();
               Now_Color = 0; Last_Color = 0;
               break;
      }
    }
}

int Color_Detection() //颜色检测函数
{
    int color[3];
    g_flag = 0;
    for(int i=0; i<3; i++) {
    color[i] = g_array[i] * g_SF[i];  
   }
    Serial.println((String)(color[0]) + '+' + (String)(color[1]) + '+' + (String)(color[2]) + '+'); 
    delay(500);
   if( (color[0] > color[1]) && (color[0] >color[2]) && ( (color[1]+color[2])<color[0] ) ){
     return 1;         //如果检测到的颜色为红色，返回1；
   }
   else if( (color[2] > color[1]) && (color[2] >color[0]) ){
     return 2;         //如果检测到的颜色为蓝色，返回2；
   }
   else { return 3; }  //否则，机械臂不动作；
}

void reset()            //舵机角度初始化
{
   for(int i=0;i<servo_num;i++)
  {
     myservo[i].attach(servo_pin[i]);
     myservo[i].write(map(value_init[i],0,180,500,2500));
  }  
}

void servo_move(float value0, float value1, float value2)   //舵机转动
   {
  float value_arguments[3] = {value0, value1, value2};
  float value_delta[servo_num];
  
  for(int i=0;i<servo_num;i++)
  {
    value_delta[i] = (value_arguments[i] - value_init[i]) / f;
  }
  
  for(int i=0;i<f;i++)
  {
    for(int k=0;k<servo_num;k++)
    {
      value_init[k] = value_delta[k] == 0 ? value_arguments[k] : value_init[k] + value_delta[k];
    }
    
    for(int j=0;j<servo_num;j++)
    {
      myservo[j].write(map(value_init[j],0,180,500,2500));
      delay(Servo_Speed);
    }
  }
}


void Servo_Left() //将物料放到机械臂的左侧
{
  servo_move(Upward_servo_open, Middle_servo_left, Down_servo_middle);//初始化动作
  servo_move(Upward_servo_open, Middle_servo_init, Down_servo_middle);//机械臂下降
  servo_move(Upward_servo_close, Middle_servo_init, Down_servo_middle);//机械爪闭合（抓取货物）
  servo_move(Upward_servo_close, Middle_servo_left1, Down_servo_middle);//机械臂上抬
  servo_move(Upward_servo_close, Middle_servo_down, Down_servo_left); //机械臂下降，机械底座向左转
  servo_move(Upward_servo_open, Middle_servo_down, Down_servo_left);  //机械爪张开（释放货物）
  servo_move(Upward_servo_open, Middle_servo_left, Down_servo_middle);//机械臂回复到初始角度
}

void Servo_Right() //将物料放到机械臂的右侧
{
  servo_move(Upward_servo_open, Middle_servo_left, Down_servo_middle);//初始化动作
  servo_move(Upward_servo_open, Middle_servo_init, Down_servo_middle);
  servo_move(Upward_servo_close, Middle_servo_init, Down_servo_middle);
  servo_move(Upward_servo_close, Middle_servo_left1, Down_servo_middle);
  servo_move(Upward_servo_close, Middle_servo_down, Down_servo_right);
  servo_move(Upward_servo_open, Middle_servo_down, Down_servo_right);
  servo_move(Upward_servo_open, Middle_servo_left, Down_servo_middle);
}
