#include <Servo.h>
Servo servo_pin_3;

void setup() {
  // put your setup code here, to run once:
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
Serial.begin(115200);
servo_pin_3.attach(3);
pinMode( 3 , OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly: 
 if ((Serial.available())>0) 
 {
   char inChar =(char) Serial.read();
   //inChar = inputString.toInt();
   Serial.println(inChar);
   if (inChar == '1')
   {
     digitalWrite(5,LOW);
     digitalWrite(6,LOW);
     servo_pin_3.write( 30 );
     delay(2000);
     servo_pin_3.write( 90);
     delay(2000);
   }
   if (inChar == '2')
   {
    digitalWrite(5,HIGH);
    digitalWrite(6,LOW);
     
   }
 }
}


