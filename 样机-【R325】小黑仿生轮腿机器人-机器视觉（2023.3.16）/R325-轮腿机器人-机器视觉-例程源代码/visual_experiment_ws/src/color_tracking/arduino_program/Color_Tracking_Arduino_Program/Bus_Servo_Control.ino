#define Servo_Num 4
#define D_WHEEL 0.06   //m
#define DIAGONAL_L 0.446 //m
#define BODY_WIDTH  0.337 //m
#define kMaxSpeed 0.6*M_PI*D_WHEEL // m/s    0.1130973m/s

const double kTurningAdjustRate = 1.14;
const double kEquivalentTread = (DIAGONAL_L*DIAGONAL_L/BODY_WIDTH)*kTurningAdjustRate;  //m
const double WRatio = kEquivalentTread*M_PI/(2*M_PI);  //  m/弧度

int forward_flags = 0;
int back_flags = 0;
int left_flags = 0;
int right_flags = 0;
int steppers = 0;
float wheel_Speed[4]={0,0,0,0};

void XYSetVel(double vx, double vy, double w)
{
  double v0 =  (vx+vy);    // m/s
  double v1 =  (vx-vy);    // m/s
  double w_t = WRatio * (-w); // m/s
  if( (fabs(v1 - w_t)>kMaxSpeed)||(fabs(v0 + w_t)>kMaxSpeed)||(fabs(v0 - w_t)>kMaxSpeed)||(fabs(v1 + w_t)>kMaxSpeed) )
    return;
  
  wheel_Speed[0] = v1 - w_t;
  wheel_Speed[1] = v0 + w_t;
  wheel_Speed[2] = v0 - w_t;
  wheel_Speed[3] = v1 + w_t;
  if( (vx >0) && (vy ==0) && (w ==0)) {forward_flags = 1;steppers = 70;}
  else if( (vx <0) && (vy ==0) && (w ==0)) {forward_flags = -1;steppers = 100;}
  else if( (vx ==0 ) && ( vy==0 ) && ( w>0 ) ){forward_flags = 1;steppers = 100;}
  else if( (vx ==0 ) && ( vy==0 ) && ( w<0 ) ){forward_flags = -1;steppers = 100;}
  else {forward_flags = 0;steppers = 0;}
  
  
  set_servo_Vel(wheel_Speed[0], wheel_Speed[1],wheel_Speed[2], wheel_Speed[3]); 
}

void set_servo_Vel(float s1, float s2, float s3, float s4)
{
  int get_Pwm[4] = {0,0,0,0};
  get_Pwm[0] = return_pwm(s1);
  get_Pwm[1] = return_pwm(s2);
  get_Pwm[2] = return_pwm(s3);
  get_Pwm[3] = return_pwm(s4);
  char cmd_returns[200];
  //sprintf(cmd_returns, "{#%03dP%04dT%04d!#%03dP%04dT%04d!#%03dP%04dT%04d!#%03dP%04dT%04d!}",0,get_Pwm[0]+(forward_flags*steppers),9999, 1,get_Pwm[1],9999,  2,get_Pwm[2]+(forward_flags*steppers),9999,  3,get_Pwm[3],9999);
  sprintf(cmd_returns, "{#%03dP%04dT%04d!#%03dP%04dT%04d!#%03dP%04dT%04d!#%03dP%04dT%04d!}",0,get_Pwm[0],9999, 1,get_Pwm[1],9999,  2,get_Pwm[2],9999,  3,get_Pwm[3],9999);
  
  mySerial.print(cmd_returns);
}

void set_Single_servo_Vel(int sss)
{
  char cmd_returns[20];  
  sprintf(cmd_returns, "{#%03dP%04dT%04d!}",0,sss,9999);
  mySerial.print(cmd_returns);   
}

int return_pwm(float mps)
{
  double rps = ( mps / (M_PI*D_WHEEL) )*10000 ;
//  double K = 251090*mps*mps - 40195*fabs(mps) + 3175.5;
  double  k = -0.1426*rps + 1504.7;
//  return 1500 - K*rps;
  return k;
//  if(rps ==0 ){return 1500;}
//  else {
//  return ( (2000*rps-1800)/(-1.2) );
//  }
}

void Car_Move(int Mode)
{
  switch(Mode)
  {
    case FORWARD: {XYSetVel(wheel_speed_forward, 0, 0);}break;
    case BACK: {XYSetVel(wheel_speed_back, 0, 0);}break;
    case LEFT: {XYSetVel(0, 0, wheel_speed_left);}break;
    case RIGHT: {XYSetVel(0, 0, wheel_speed_right);}break;
    case LEFT_TRANSLATION: {XYSetVel(0, wheel_speed_left_translation, 0);}break;
    case RIGHT_TRANSLATION: {XYSetVel(0, wheel_speed_right_translation, 0);}break;
    case STOP: {XYSetVel(0, 0, 0);}break;
    default: break;
  }
}

void car_stop(){Car_Move(STOP);delay(1000);}
