
#define Motor_Count 4 //定义直流电机数量
int motor_pin[4] = {5,6,9,10}; //定义直流电机引脚

void Motor_pin_init() //初始化直流电机引脚
{
  for(int i=0;i<Motor_Count;i++)
  {
    pinMode(motor_pin[i],OUTPUT);
    digitalWrite(motor_pin[i],LOW);
  }
}

void Motor_Go(int mode, int speeds) //定义小车状态。mode表示小车模式，speeds表示小车速度
{
  switch(mode)
  {
    case Forward: {
      analogWrite(motor_pin[0],speeds);
      analogWrite(motor_pin[1],0);
      analogWrite(motor_pin[2],speeds);
      analogWrite(motor_pin[3],0);
    }break;
    case Back: {
      analogWrite(motor_pin[0],0);
      analogWrite(motor_pin[1],speeds);
      analogWrite(motor_pin[2],0);
      analogWrite(motor_pin[3],speeds);
    }break;
    case Left: {
      analogWrite(motor_pin[0],speeds);
      analogWrite(motor_pin[1],0);
      analogWrite(motor_pin[2],0);
      analogWrite(motor_pin[3],speeds);
    }break;
    case Right: {
      analogWrite(motor_pin[0],0);
      analogWrite(motor_pin[1],speeds);
      analogWrite(motor_pin[2],speeds);
      analogWrite(motor_pin[3],0);
    }break;
    case Stop: {
      analogWrite(motor_pin[0],speeds);
      analogWrite(motor_pin[1],speeds);
      analogWrite(motor_pin[2],speeds);
      analogWrite(motor_pin[3],speeds);
    }break;
    default: break;   
  }
}
