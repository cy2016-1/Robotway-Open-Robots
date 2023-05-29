/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-05-25 https://www.robotway.com/
  ------------------------------*/
#define myservoPin 3
ServoTimer2 myservo;//注意与声明的头文件保持一致
int a;
void setup() 
{
  // put your setup code here, to run once:
  myservo.attach(myservoPin);
  pinMode( 9 , OUTPUT );
  pinMode( 10 , OUTPUT );
    pinMode( 5, OUTPUT );
  pinMode( 6, OUTPUT );
}

void loop() 
{
  // put your main code here, to run repeatedly:
  a=map(60,0,180,750,2250);
  myservo.write(a); 
  analogWrite( 9 , 200 );
    analogWrite(5 , 200 );
  delay(1000);
  
  a=map(120,20,160,750,2250);////这是一个映射函数
  myservo.write(a); //注意a=map（60，20，160，750,2250），其中a=map（转动到的角度，可转动角度最小值，转动角度最大值，最小可转动的角度值对应的脉冲，最大可转动的角度值对应的脉冲）
} 
  analogWrite( 9 ,100 );
  analogWrite( 5 ,100 );
  delay(1000);
}
