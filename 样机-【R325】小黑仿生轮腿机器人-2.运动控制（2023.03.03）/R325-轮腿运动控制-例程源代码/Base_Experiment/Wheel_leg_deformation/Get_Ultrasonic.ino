
const int Ultrasonic_TrigPin[8] = {39,40,46,45,23,24,30,29};  //water edit
const int Ultrasonic_EchoPin[8] = {41,38,44,47,25,22,28,31}; 


const int Ultrasonic_Pin_Numbers = sizeof(Ultrasonic_TrigPin)/sizeof(Ultrasonic_TrigPin[0]);//8

int ReturnCM(int trigPin, int echoPin)
{
  long duration;
  digitalWrite(trigPin, LOW);
//  delayMicroseconds(2);
  Set_Myself_Delay_us(2);
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(20);
  Set_Myself_Delay_us(20);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  duration = duration / 59;
  if ((duration < 2) || (duration > 300)) return false;
  return duration;
}

void Get_ultrasonic_sensor_data() //串口事件,接收串口命令;
{
//  for(int i=0;i<Ultrasonic_Pin_Numbers;i++)
  for(int i=0;i<8;i++)
  {
    GetUltrasonicDatas[i] = ReturnCM ( Ultrasonic_TrigPin[i], Ultrasonic_EchoPin[i]);
    Ultrasonic_flags[i] =  ( (GetUltrasonicDatas[i]<10) && (GetUltrasonicDatas[i]>0) ) ? true : false;
    Serial.print("Sensor");Serial.print(Ultrasonic_TrigPin[i]);Serial.print(": ");Serial.print(GetUltrasonicDatas[i]);Serial.print(" | ");
    Serial.print(Ultrasonic_flags[i]);Serial.print(" | ");
//    delay(10);
  }
  Serial.println();
}

void init_Ultrasonic()
{
  for(int j=0;j<Ultrasonic_Pin_Numbers;j++){
    pinMode(Ultrasonic_TrigPin[j],OUTPUT);
    pinMode(Ultrasonic_EchoPin[j],INPUT);
    Set_Myself_Delay_ms(BriefDelayTimes);//Set Ultrasonic Pin
  }
  
  for(int i=0;i<Ultrasonic_Pin_Numbers;i++){
    digitalWrite(Ultrasonic_TrigPin[i],LOW);
    Set_Myself_Delay_ms(BriefDelayTimes);//init Ultrasonic
  }  
}

void Set_Myself_Delay_ms(unsigned long _ms)
{
  unsigned long now_time = millis();
  while(millis() - now_time < _ms)
  { }
}

void Set_Myself_Delay_us(unsigned long _us)
{
  unsigned long now_time = micros();
  while(micros() - now_time < _us)
  { }  
}
