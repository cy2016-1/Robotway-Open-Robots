#define ECHOPIN A0 //使用宏定义对超声波模块连接的引脚进行定义
#define TRIGPIN A1


#include <Arduino.h>
#include <Wire.h>
#include <MultiLCD.h>

LCD_SSD1306 lcd; /* for SSD1306 OLED module */

void setup()
{
	lcd.begin();
        int a=0;
        pinMode(ECHOPIN, INPUT);
        pinMode(TRIGPIN, OUTPUT);
        
}

void loop()

{   lcd.clear();

        int a=Distance();
	lcd.clear();
	lcd.setCursor(0, 2);
	lcd.print("The distance is:");

	lcd.setCursor(0, 4);
	lcd.print(a);


	lcd.setCursor(0, 5);
	lcd.print("cm");
        delay(3000);
}

int Distance() //超声波距离测量函数，返回测量的距离
{
digitalWrite(TRIGPIN, LOW);
delayMicroseconds(2);
digitalWrite(TRIGPIN, HIGH);
delayMicroseconds(10);
digitalWrite(TRIGPIN, LOW);
int distance = pulseIn(ECHOPIN, HIGH);
distance= distance/58;
return distance;
}
