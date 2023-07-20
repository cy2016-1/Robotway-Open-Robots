void Servo_reset()//初始化舵机引脚以及舵机角度
{
  int float_to_int[servo_num] = {0,0,0,0,0,0,0,0};
  for(int i=0;i<servo_num;i++)
  {
    myservo[i].attach(servo_pin[i]);
    float_to_int[i] = value_init[i];
    myservo[i].write(float_to_int[i]);
    delay(30);
  }  
}

//8舵机同时动作函数
void servo_move(float value0, float value1, float value2, float value3, float value4, float value5, float value6, float value7) 
{
  int float_to_int[servo_num] = {0,0,0,0,0,0,0,0};
  float value_arguments[servo_num] = {value0, value1, value2, value3,value4,value5, value6, value7};
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
      float_to_int[k] = value_init[k];
    }
    
    for(int j=0;j<servo_num;j++)
    {
      myservo[j].write(float_to_int[j]);
      delay(servo_delay);
    }
  }
}

//单个舵机转动函数
void single_servo_move(int servopin, float value0){
  int float_to_int = 0;
  float value_arguments = value0;
  float value_delta;
  
  value_delta = (value_arguments - value_init[servopin]) / f;
  
  for(int i=0;i<f;i++)
  {
      value_init[servopin] = value_delta == 0 ? value_arguments : value_init[servopin] + value_delta;
      float_to_int = value_init[servopin];
    
      myservo[servopin].write(float_to_int);
      delay(servo_delay);
  }
}
