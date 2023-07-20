/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-06-14 https://www.robotway.com/
  ------------------------------*/
#include <Servo.h>

int i,j,k,l;  //定义几个变量
Servo servo1; //命名一个舵机

void setup() {
  
  servo1.attach(3); //启动舵机3号口
  
  pinMode( 14, INPUT);  //定义引脚
  pinMode( 18, INPUT);
  pinMode( 5, OUTPUT);
  pinMode( 6, OUTPUT);
  pinMode( 9, OUTPUT);
  pinMode( 10, OUTPUT);
  pinMode( 4, OUTPUT);


}

void loop() {
  i=digitalRead(14);   //设置i为A0读取数据
  j=digitalRead(18);   //设置j为A4读取数据
	//第一步	
  servo1.write( 130 );       //舵机置位
  zero();
	/****************************
	第二步	
	*****************************/
      if(i==0&&j==0)      //如果X轴Y轴已归位
      {
           //delay(2000);
           
           digitalWrite( 9 , LOW );   //X轴至中部
           digitalWrite( 10 , HIGH );
           delay(6000);
           digitalWrite( 10 , LOW );
		   
           servo1.write( 87 );        //舵机伸出
           digitalWrite( 4 , HIGH );  //电机旋转
           delay(1000);
	/****************************
	第三步	
	*****************************/
           digitalWrite( 5 , LOW ); 	 //Z轴移至中间
           digitalWrite( 6 , HIGH );
           delay(5000);
           digitalWrite( 6 , LOW );
           
           digitalWrite( 9 , LOW ); 	 //X轴左移一秒
           digitalWrite( 10 , HIGH );
           delay(1000);
           digitalWrite( 10 , LOW );  	//稍停
           delay(300);
           digitalWrite( 9 , HIGH ); 	//X轴右移一秒
           digitalWrite( 10 , LOW );
           delay(1000);
		   digitalWrite( 9 , LOW ); 
                                  
           servo1.write( 130 );     //舵机伸缩移动
		   delay(300);
		   servo1.write( 87 );
		   delay(300);
	/****************************
	第四步	
	*****************************/
		//   digitalWrite( 5 , LOW ); 	 //Z轴下移一秒
         //  digitalWrite( 6 , HIGH );
         //  delay(1000);
//           digitalWrite( 6 , LOW );		//稍停
//           delay(300);
           digitalWrite( 5 , HIGH );    //Z轴上移一秒
           digitalWrite( 6 , LOW );
           delay(1000);
          digitalWrite( 5 , LOW ); 
		   
	/****************************
	重复第三步	
	*****************************/
		   digitalWrite( 5 , LOW ); 	 //Z轴移至中间
           digitalWrite( 6 , HIGH );
           delay(1000);
           digitalWrite( 6 , LOW );
          
           digitalWrite( 9 , LOW );  //X轴左右移一秒
           digitalWrite( 10 , HIGH );
           delay(1000);
           digitalWrite( 10 , LOW );
           delay(300);
           digitalWrite( 9 , HIGH ); 
           digitalWrite( 10 , LOW );
           delay(1000);
           digitalWrite( 9 , LOW ); 
                                  
           servo1.write( 130 );     //舵机伸缩移动
           delay(300);
           servo1.write( 87 );
           delay(300);
           digitalWrite( 4 , LOW );
           while(1)
           {
             i=digitalRead(14);   //设置i为A0读取数据
            j=digitalRead(18);   //设置j为A4读取数据
            zero();
            }
          
      }
      
  //}
  
}



void zero()
{
   if(i==0)                   //如果触发限位A0
      {
         digitalWrite( 9 , LOW );  //X轴停止运动
         digitalWrite( 10 , LOW );
      }
      else
      {
         digitalWrite( 9 , HIGH );  //X轴电机置位
        digitalWrite( 10 , LOW );
      }
      
      if(j==0)					//如果触发限位A4
      {
         digitalWrite( 5 , LOW );	//Z轴停止运动
         digitalWrite( 6 , LOW );
      }
      else
      {
          digitalWrite( 5 , HIGH );	 //Z轴电机置位
          digitalWrite( 6 , LOW );
      }
}
