                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  #include <SoftwareSerial.h> //蓝牙
SoftwareSerial BT(10, 11); 
//Pin10为RX，接HC05的TX针脚
//Pin11为TX，接HC05的RX针脚

char val;
int input1 = 30; // 定义uno的pin 5 向 input1 输出 
int input2 = 31; // 定义uno的pin 6 向 input2 输出
int enA = 2; // 定义uno的pin 3 向 输出A使能端输出
int input3 = 32;
int input4 = 33;
int enB = 3;
int input5 = 34;
int input6 = 35;
int enC = 4;
int input7 = 36;
int input8 = 37;
int enD = 5;
int diancifa = 6;



/****************************主卧*****************************/
void bedroom1()
{
  digitalWrite(input1,LOW);  //直行
  digitalWrite(input2,HIGH);
  digitalWrite(input3,LOW);
  digitalWrite(input4,HIGH);
  digitalWrite(input5,HIGH);
  digitalWrite(input6,LOW);
  digitalWrite(input7,HIGH);
  digitalWrite(input8,LOW);
  analogWrite(enA,195);
  analogWrite(enB,185);
  analogWrite(enC,210);
  analogWrite(enD,185);
  delay(1400);

//  digitalWrite(input1,LOW);  //矫正
//  digitalWrite(input2,HIGH);
//  digitalWrite(input3,LOW);
//  digitalWrite(input4,HIGH);
//  digitalWrite(input5,HIGH);
//  digitalWrite(input6,LOW);
//  digitalWrite(input7,LOW);
//  digitalWrite(input8,LOW);
//  analogWrite(enA,195);
//  analogWrite(enB,185);
//  analogWrite(enC,210);
//  delay(450);
//
//  digitalWrite(input1,LOW);  //直行
//  digitalWrite(input2,HIGH);
//  digitalWrite(input3,LOW);
//  digitalWrite(input4,HIGH);
//  digitalWrite(input5,HIGH);
//  digitalWrite(input6,LOW);
//  digitalWrite(input7,HIGH);
//  digitalWrite(input8,LOW);
//  analogWrite(enA,195);
//  analogWrite(enB,185);
//  analogWrite(enC,210);
//  analogWrite(enD,185);
//  delay(1000);
//
//  digitalWrite(input1,LOW);  //停止
//  digitalWrite(input2,LOW);
//  digitalWrite(input3,LOW);
//  digitalWrite(input4,LOW);
//  digitalWrite(input5,LOW);
//  digitalWrite(input6,LOW);
//  digitalWrite(input7,LOW);
//  digitalWrite(input8,LOW);
//  delay(5000);
//
//  digitalWrite(input1,LOW);  //直行
//  digitalWrite(input2,HIGH);
//  digitalWrite(input3,LOW);
//  digitalWrite(input4,HIGH);
//  digitalWrite(input5,HIGH);
//  digitalWrite(input6,LOW);
//  digitalWrite(input7,HIGH);
//  digitalWrite(input8,LOW);
//  analogWrite(enA,195);
//  analogWrite(enB,185);
//  analogWrite(enC,210);
//  analogWrite(enD,185);
//  delay(4200);
//
  digitalWrite(input1,LOW);  //向左转
  digitalWrite(input2,HIGH);
  digitalWrite(input3,LOW);
  digitalWrite(input4,HIGH);
  digitalWrite(input5,LOW);
  digitalWrite(input6,HIGH);
  digitalWrite(input7,HIGH);
  digitalWrite(input8,LOW);
  analogWrite(enA,200);
  analogWrite(enB,200);
  analogWrite(enC,200);
  analogWrite(enD,200);
  delay(2800);
//
//  digitalWrite(input1,LOW);  //直行
//  digitalWrite(input2,HIGH);
//  digitalWrite(input3,LOW);
//  digitalWrite(input4,HIGH);
//  digitalWrite(input5,HIGH);
//  digitalWrite(input6,LOW);
//  digitalWrite(input7,HIGH);
//  digitalWrite(input8,LOW);
//  analogWrite(enA,195);
//  analogWrite(enB,185);
//  analogWrite(enC,210);
//  analogWrite(enD,185);
//  delay(1200);
  
  digitalWrite(input1,LOW);  //停止
  digitalWrite(input2,LOW);
  digitalWrite(input3,LOW);
  digitalWrite(input4,LOW);
  digitalWrite(input5,LOW);
  digitalWrite(input6,LOW);
  digitalWrite(input7,LOW);
  digitalWrite(input8,LOW);

//delay(5000);
//  digitalWrite(diancifa,LOW);
//  delay(3000);
//  digitalWrite(diancifa,HIGH);
  //delay(3000);

  }


/****************************主卧————>阳台*****************************/
void balcony()
{
  digitalWrite(input1,HIGH);  //后退
  digitalWrite(input2,LOW);
  digitalWrite(input3,HIGH);
  digitalWrite(input4,LOW);
  digitalWrite(input5,LOW);
  digitalWrite(input6,HIGH);
  digitalWrite(input7,LOW);
  digitalWrite(input8,HIGH);
  analogWrite(enA,195);
  analogWrite(enB,185);
  analogWrite(enC,210);
  analogWrite(enD,185);
  delay(1500);

  digitalWrite(input1,HIGH);  //向右转
  digitalWrite(input2,LOW);
  digitalWrite(input3,HIGH);
  digitalWrite(input4,LOW);
  digitalWrite(input5,HIGH);
  digitalWrite(input6,LOW);
  digitalWrite(input7,LOW);
  digitalWrite(input8,HIGH);
  analogWrite(enA,200);
  analogWrite(enB,200);
  analogWrite(enC,200);
  analogWrite(enD,200);
  delay(2900);

  digitalWrite(input1,HIGH);  //后退
  digitalWrite(input2,LOW);
  digitalWrite(input3,HIGH);
  digitalWrite(input4,LOW);
  digitalWrite(input5,LOW);
  digitalWrite(input6,HIGH);
  digitalWrite(input7,LOW);
  digitalWrite(input8,HIGH);
  analogWrite(enA,195);
  analogWrite(enB,185);
  analogWrite(enC,210);
  analogWrite(enD,185);
  delay(3000);

  digitalWrite(input1,HIGH);  //矫正
  digitalWrite(input2,LOW);
  digitalWrite(input3,HIGH);
  digitalWrite(input4,LOW);
  digitalWrite(input5,LOW);
  digitalWrite(input6,HIGH);
  digitalWrite(input7,LOW);
  digitalWrite(input8,LOW);
  analogWrite(enA,195);
  analogWrite(enB,185);
  analogWrite(enC,210);
  delay(300);

  digitalWrite(input1,HIGH);  //后退
  digitalWrite(input2,LOW);
  digitalWrite(input3,HIGH);
  digitalWrite(input4,LOW);
  digitalWrite(input5,LOW);
  digitalWrite(input6,HIGH);
  digitalWrite(input7,LOW);
  digitalWrite(input8,HIGH);
  analogWrite(enA,195);
  analogWrite(enB,185);
  analogWrite(enC,210);
  analogWrite(enD,185);
  delay(3000);
  
  digitalWrite(input1,LOW);  //向左转
  digitalWrite(input2,HIGH);
  digitalWrite(input3,LOW);
  digitalWrite(input4,HIGH);
  digitalWrite(input5,LOW);
  digitalWrite(input6,HIGH);
  digitalWrite(input7,HIGH);
  digitalWrite(input8,LOW);
  analogWrite(enA,200);
  analogWrite(enB,200);
  analogWrite(enC,200);
  analogWrite(enD,200);
  delay(3350);

  digitalWrite(input1,LOW);  //直行
  digitalWrite(input2,HIGH);
  digitalWrite(input3,LOW);
  digitalWrite(input4,HIGH);
  digitalWrite(input5,HIGH);
  digitalWrite(input6,LOW);
  digitalWrite(input7,HIGH);
  digitalWrite(input8,LOW);
  analogWrite(enA,195);
  analogWrite(enB,185);
  analogWrite(enC,210);
  analogWrite(enD,185);
  delay(3000);

  digitalWrite(input1,LOW);  //矫正
  digitalWrite(input2,HIGH);
  digitalWrite(input3,LOW);
  digitalWrite(input4,HIGH);
  digitalWrite(input5,HIGH);
  digitalWrite(input6,LOW);
  digitalWrite(input7,LOW);
  digitalWrite(input8,LOW);
  analogWrite(enA,195);
  analogWrite(enB,185);
  analogWrite(enC,210);
  delay(300);

  digitalWrite(input1,LOW);  //直行
  digitalWrite(input2,HIGH);
  digitalWrite(input3,LOW);
  digitalWrite(input4,HIGH);
  digitalWrite(input5,HIGH);
  digitalWrite(input6,LOW);
  digitalWrite(input7,HIGH);
  digitalWrite(input8,LOW);
  analogWrite(enA,195);
  analogWrite(enB,185);
  analogWrite(enC,210);
  analogWrite(enD,185);
  delay(2500);

  digitalWrite(input1,LOW);  //矫正
  digitalWrite(input2,HIGH);
  digitalWrite(input3,LOW);
  digitalWrite(input4,HIGH);
  digitalWrite(input5,HIGH);
  digitalWrite(input6,LOW);
  digitalWrite(input7,LOW);
  digitalWrite(input8,LOW);
  analogWrite(enA,195);
  analogWrite(enB,185);
  analogWrite(enC,210);
  delay(300);

  digitalWrite(input1,LOW);  //停止
  digitalWrite(input2,LOW);
  digitalWrite(input3,LOW);
  digitalWrite(input4,LOW);
  digitalWrite(input5,LOW);
  digitalWrite(input6,LOW);
  digitalWrite(input7,LOW);
  digitalWrite(input8,LOW);
  }



/****************************厨房*****************************/
void kitchen()
{
  digitalWrite(input1,LOW);  //直行
  digitalWrite(input2,HIGH);
  digitalWrite(input3,LOW);
  digitalWrite(input4,HIGH);
  digitalWrite(input5,HIGH);
  digitalWrite(input6,LOW);
  digitalWrite(input7,HIGH);
  digitalWrite(input8,LOW);
  analogWrite(enA,185);
  analogWrite(enB,185);
  analogWrite(enC,202);
  analogWrite(enD,185);
  delay(600);
  
  digitalWrite(input1,LOW);  //向左转
  digitalWrite(input2,HIGH);
  digitalWrite(input3,LOW);
  digitalWrite(input4,HIGH);
  digitalWrite(input5,LOW);
  digitalWrite(input6,HIGH);
  digitalWrite(input7,HIGH);
  digitalWrite(input8,LOW);
  analogWrite(enA,200);
  analogWrite(enB,200);
  analogWrite(enC,200);
  analogWrite(enD,200);
  delay(3300);

  digitalWrite(input1,LOW);  //直行
  digitalWrite(input2,HIGH);
  digitalWrite(input3,LOW);
  digitalWrite(input4,HIGH);
  digitalWrite(input5,HIGH);
  digitalWrite(input6,LOW);
  digitalWrite(input7,HIGH);
  digitalWrite(input8,LOW);
  analogWrite(enA,185);
  analogWrite(enB,185);
  analogWrite(enC,210);
  analogWrite(enD,150);
  delay(5000);
//  digitalWrite(input1,LOW);  //直行
//  digitalWrite(input2,HIGH);
//  digitalWrite(input3,LOW);
//  digitalWrite(input4,HIGH);
//  digitalWrite(input5,HIGH);
//  digitalWrite(input6,LOW);
//  digitalWrite(input7,LOW);
//  digitalWrite(input8,LOW);
//  analogWrite(enA,195);
//  analogWrite(enB,185);
//  analogWrite(enC,220);
//  delay(400);
  digitalWrite(input1,LOW);  //直行
  digitalWrite(input2,HIGH);
  digitalWrite(input3,LOW);
  digitalWrite(input4,HIGH);
  digitalWrite(input5,HIGH);
  digitalWrite(input6,LOW);
  digitalWrite(input7,HIGH);
  digitalWrite(input8,LOW);
  analogWrite(enA,185);
  analogWrite(enB,185);
  analogWrite(enC,210);
  analogWrite(enD,165);
  delay(3400);

  digitalWrite(input1,LOW);  //停止
  digitalWrite(input2,LOW);
  digitalWrite(input3,LOW);
  digitalWrite(input4,LOW);
  digitalWrite(input5,LOW);
  digitalWrite(input6,LOW);
  digitalWrite(input7,LOW);
  digitalWrite(input8,LOW);

  delay(3000);

  digitalWrite(input1,HIGH);  //返回
  digitalWrite(input2,LOW);
  digitalWrite(input3,HIGH);
  digitalWrite(input4,LOW);
  digitalWrite(input5,LOW);
  digitalWrite(input6,HIGH);
  digitalWrite(input7,LOW);
  digitalWrite(input8,HIGH);
  analogWrite(enA,185);
  analogWrite(enB,185);
  analogWrite(enC,210);
  analogWrite(enD,185);
  delay(3500);
//  digitalWrite(input1,LOW);
//  digitalWrite(input2,HIGH);
//  digitalWrite(input3,LOW);
//  digitalWrite(input4,HIGH);
//  digitalWrite(input5,LOW);
//  digitalWrite(input6,HIGH);
//  digitalWrite(input7,LOW);
//  digitalWrite(input8,LOW);
//  analogWrite(enA,195);
//  analogWrite(enB,185);
//  analogWrite(enC,210);
//  delay(400);
  digitalWrite(input1,HIGH);
  digitalWrite(input2,LOW);
  digitalWrite(input3,HIGH);
  digitalWrite(input4,LOW);
  digitalWrite(input5,LOW);
  digitalWrite(input6,HIGH);
  digitalWrite(input7,LOW);
  digitalWrite(input8,HIGH);
  analogWrite(enA,185);
  analogWrite(enB,185);
  analogWrite(enC,210);
  analogWrite(enD,185);
  delay(5400);
  digitalWrite(input1,HIGH);   //转弯
  digitalWrite(input2,LOW);
  digitalWrite(input3,HIGH);
  digitalWrite(input4,LOW);
  digitalWrite(input5,HIGH);
  digitalWrite(input6,LOW);
  digitalWrite(input7,LOW);
  digitalWrite(input8,HIGH);
  analogWrite(enA,200);
  analogWrite(enB,200);
  analogWrite(enC,200);
  analogWrite(enD,200);
  delay(1700);
  
  digitalWrite(input1,LOW);  //停止
  digitalWrite(input2,LOW);
  digitalWrite(input3,LOW);
  digitalWrite(input4,LOW);
  digitalWrite(input5,LOW);
  digitalWrite(input6,LOW);
  digitalWrite(input7,LOW);
  digitalWrite(input8,LOW);
  }

void go()
{
      //测试
      digitalWrite(18,LOW);
      delay(3000);
      digitalWrite(18,HIGH);
      delay(6000);
      digitalWrite(18,LOW);
      delay(3000);
      digitalWrite(18,HIGH);
      delay(6000);
      digitalWrite(18,LOW);
      delay(3000);
      digitalWrite(18,HIGH);
      delay(6000);
}


void goo()
{
      //测试
      digitalWrite(18,HIGH);
      delay(3000);
      digitalWrite(18,LOW);
      delay(30000);
}



void setup()
{
      //蓝牙
      Serial.begin(9600);
      Serial.println("Buletooth is ready!");
      BT.begin(9600);
      pinMode(input1,OUTPUT);
      pinMode(input2,OUTPUT);
      pinMode(enA,OUTPUT);
      pinMode(input3,OUTPUT);
      pinMode(input4,OUTPUT);
      pinMode(enB,OUTPUT);
      pinMode(input6,OUTPUT);
      pinMode(enC,OUTPUT);
      pinMode(input7,OUTPUT);
      pinMode(input5,OUTPUT);
      pinMode(input8,OUTPUT);
      pinMode(enD,OUTPUT);
      pinMode(diancifa,OUTPUT);
      pinMode(18,OUTPUT);//电磁阀
      
}

void loop() {
  if (Serial.available()) {
    val = Serial.read();
    BT.print(val);
  }
  if (BT.available()) {
    val = BT.read();
    Serial.print(val);
    switch(val){
      case '1': bedroom1();break;
      case '2': balcony();break;
      case '3':kitchen();break;
//      case '4':kitchen();break;
      case '5':test();break;
      case '6':go();break;
      case '7':goo();break;
    }
  }
}



//void test()
//{
//  digitalWrite(input1,LOW);  //直行
//  digitalWrite(input2,HIGH);
//  digitalWrite(input3,LOW);
//  digitalWrite(input4,HIGH);
//  digitalWrite(input5,HIGH);
//  digitalWrite(input6,LOW);
//  digitalWrite(input7,HIGH);
//  digitalWrite(input8,LOW);
//  analogWrite(enA,165);
//  analogWrite(enB,240);
//  analogWrite(enC,210);
//  analogWrite(enD,185);

//  }

void test()
{
  digitalWrite(input1,LOW);  //直行
  digitalWrite(input2,HIGH);
  digitalWrite(input3,LOW);
  digitalWrite(input4,HIGH);
  digitalWrite(input5,HIGH);
  digitalWrite(input6,LOW);
  digitalWrite(input7,HIGH);
  digitalWrite(input8,LOW);
  analogWrite(enA,195);
  analogWrite(enB,185);
  analogWrite(enC,210);
  analogWrite(enD,185);
  delay(6000);
  digitalWrite(input1,LOW);  //停止
  digitalWrite(input2,LOW);
  digitalWrite(input3,LOW);
  digitalWrite(input4,LOW);
  digitalWrite(input5,LOW);
  digitalWrite(input6,LOW);
  digitalWrite(input7,LOW);
  digitalWrite(input8,LOW);
  }
