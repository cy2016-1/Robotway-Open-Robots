#define f 40
#define Servo_Num 4
#define servo_num 4
//ServoTimer2 myServo[4];//statement servo
Servo myServo[4];
int servo_port[4] =   {42, 43, 27, 26};//x,y,z,a
float value_init[4] = {95, 95, 100, 88};//x,y,z,a     2020.12.2 18:32
float value_init_reset[4] = {95, 95, 100, 88};

void Dog_Dance()
{
  Servo_Action_Change_inside(4,12);
  XYSetVel(0.05, 0.0, 0.0);delay(2000); //forward           前进
  XYSetVel(0.0,0.0, 0.0);delay(50);//停止
  Servo_Action_Change_inside(9,20);
  
  Servo_Action_Change_inside(2,12);
  XYSetVel(-0.05,0.0,0.0);delay(2000);  //back              后退
  XYSetVel(0.0,0.0, 0.0);delay(50); 
 
  Servo_Action_Change_inside(9,12);
  XYSetVel(0.0,0.0,-0.20);delay(2000);  //left              左转
  XYSetVel(0.0,0.0, 0.0);delay(30);
  
  XYSetVel(0.0 ,0.0,0.20 );delay(2000);
  XYSetVel(0.0,0.0, 0.0);delay(30);
  
  XYSetVel( 0.0, -0.05, 0.0);delay(2000);
  XYSetVel(0.0,0.0, 0.0);delay(30);
  XYSetVel( 0.0, 0.05, 0.0);delay(2000);
  XYSetVel(0.0,0.0, 0.0);delay(30);
  Servo_Action_Init();delay(1000);
//  
  Servo_Action_Change_inside(3,20);
  moveTest();
  Servo_Action_Init();delay(1000);
  
  Servo_Action_Change_inside(1,20);
  moveTest();
  Servo_Action_Init();delay(1000);
  
  Servo_Action_Change_inside(9,12);   
  XYSetVel(0.0,0.0, 0.0);delay(1050);//停止 
  Servo_Action_Init();delay(1000);
}

void Servo_Action_Change_inside(int Mode,int delay_time)
{
  switch(Mode)
  {
    case 1://向外
         {
             int delta_servo =14 ;
             servo_move(value_init_reset[0]+delta_servo, value_init_reset[1]-delta_servo, value_init_reset[2]-delta_servo, value_init_reset[3]+delta_servo,delay_time);
         }break;
         
    case 2://狗申懒腰_forward
        {
             int delta_servo =35 ;
             servo_move(value_init_reset[0]-delta_servo, value_init_reset[1]+delta_servo, value_init_reset[2]-delta_servo, value_init_reset[3]+delta_servo,delay_time);
         }break; 
         
    case 3://向内
        {
              int delta_servo =-30 ;
              servo_move(value_init_reset[0]+delta_servo, value_init_reset[1]-delta_servo, value_init_reset[2]-delta_servo, value_init_reset[3]+delta_servo,delay_time);          
        }break;
    case 4://狗申懒腰_back
        {
             int delta_servo =35 ;
             servo_move(value_init_reset[0]+delta_servo, value_init_reset[1]-delta_servo, value_init_reset[2]+delta_servo, value_init_reset[3]-delta_servo,delay_time);        
        }break;
        case 5://
        {
             int delta_servo =35 ;
             servo_move(value_init_reset[0]-delta_servo, value_init_reset[1]-delta_servo, value_init_reset[2]+delta_servo, value_init_reset[3]+delta_servo,delay_time);        
        }break;
        case 6://
        {
             int delta_servo =35 ;
             servo_move(value_init_reset[0]-delta_servo, value_init_reset[1]+delta_servo, value_init_reset[2]-delta_servo, value_init_reset[3]+delta_servo,delay_time);        
        }break;
        
          case 7://摇摆
        {
             int delta_servo =35 ;
             servo_move(value_init_reset[0]+delta_servo, value_init_reset[1]+delta_servo, value_init_reset[2]-delta_servo, value_init_reset[3]-delta_servo,delay_time);        
        }break;
          case 8://
        {
             int delta_servo =35 ;
             servo_move(value_init_reset[0]-delta_servo, value_init_reset[1]-delta_servo, value_init_reset[2]+delta_servo, value_init_reset[3]+delta_servo,delay_time);        
        }break;
          case 9://
        {
             servo_move(value_init_reset[0], value_init_reset[1], value_init_reset[2], 86,delay_time);        
        }break;     
    case 10://狗申懒腰_forward
        {
             int delta_servo =35 ;
             servo_move(value_init_reset[0]+delta_servo, value_init_reset[1]+delta_servo, value_init_reset[2]+delta_servo, value_init_reset[3]+delta_servo,delay_time);
         }break;    
    
    case 11://狗申懒腰_forward
        {
             int delta_servo =35 ;
             servo_move(value_init_reset[0]-delta_servo, value_init_reset[1]-delta_servo, value_init_reset[2]-delta_servo, value_init_reset[3]-delta_servo,delay_time);
         }break;     
    case 12://狗申懒腰_forward
        {
             int delta_servo =35 ;
             servo_move(value_init_reset[0]-delta_servo, value_init_reset[1]+delta_servo, value_init_reset[2]-delta_servo, value_init_reset[3]+delta_servo,delay_time);
         }break;          
        default: break;
  }
}

void Servo_Action_Init()
{
  for(int i=0;i<Servo_Num;i++)
  {
    myServo[i].write( value_init_reset[i] );
  }delay(1500);  
}


void init_Servo()
{
  for(int i=0;i<Servo_Num;i++)
  {
    myServo[i].attach(servo_port[i]);delay(50);
//    myServo[i].write( map( value_init[i],0,180,500,2500) );
    myServo[i].write( value_init[i] );
//    myServo[i].write( map( value_init[i],0,180,500,2500) );
  }delay(1500);
} 

void ServoStart(int which)//使能舵机
{
  if(!myServo[which].attached())myServo[which].attach(servo_port[which]);
  pinMode(servo_port[which], OUTPUT);
}

void ServoStop(int which)//释放舵机
{
  myServo[which].detach();
  digitalWrite(servo_port[which],LOW);
}

void ServoGo(int which , int where)//打开并给舵机写入相关角度
{
  if(where!=200)
  {
    if(where==201) ServoStop(which);
    else
    {
      ServoStart(which);
//      myServo[which].write(map(where,0,180,500,2500));
      myServo[which].write( where );
    }
  }
}

void servo_move(float value0, float value1, float value2, float value3,float t)
//value0, value1, value2, value3这四个参数时要写的舵机角度，float t这个参数是代表舵机运动的时间
{  
  float value_arguments[] = {value0, value1, value2, value3};
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
      ServoGo(j,value_init[j]);
    }
    delay(t);
  }
}
