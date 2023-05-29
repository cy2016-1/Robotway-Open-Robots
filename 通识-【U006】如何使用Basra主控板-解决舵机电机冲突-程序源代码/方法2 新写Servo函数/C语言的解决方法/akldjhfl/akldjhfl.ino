/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-05-25 https://www.robotway.com/
  ------------------------------*/
int servoPin = 3;    //定义舵机接口数字接口7 也就是舵机的橙色信号线。  
 int speedd=200; 
  void setup() {  
  pinMode(servoPin, OUTPUT); //设定舵机接口为输出接口 
  pinMode( 5 , OUTPUT);
  pinMode( 6 , OUTPUT);                                          //直流电机输出端
  pinMode( 9 , OUTPUT);
  pinMode( 10 , OUTPUT);  
}  
  
void loop() {  
  servo(30);
        analogWrite( 5 , 0 );           
        analogWrite( 6 , speedd ) ;                           //左轮速度（正转）
        analogWrite( 9 , speedd );
       analogWrite( 10 , 0);                                 // 
  delay(600); 
  servo(60);  
  delay(600);
   analogWrite( 5 , speedd );           
      analogWrite( 6 , 0 ) ;                                    //左轮速度（正转）
        analogWrite( 9 , 0 );
       analogWrite( 10 , speedd);         
   servo(90);  
  delay(600);                                              
}  
  
void servo(int angle) { //定义一个脉冲函数  
  //发送50个脉冲  
  for(int i=0;i<50;i++){  
    int pulsewidth = (angle * 11) + 500; //将角度转化为500-2480的脉宽值  
    digitalWrite(servoPin, HIGH);   //将舵机接口电平至高  
    delayMicroseconds(pulsewidth);  //延时脉宽值的微秒数  
    digitalWrite(servoPin, LOW);    //将舵机接口电平至低  
    delayMicroseconds(20000 - pulsewidth);  
  }  
  delay(100);  
} 
