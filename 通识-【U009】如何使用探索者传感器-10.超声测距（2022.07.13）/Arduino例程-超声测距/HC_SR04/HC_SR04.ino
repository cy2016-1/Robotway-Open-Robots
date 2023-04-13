#define ECHOPIN A0
#define TRIGPIN A1 

#include <Arduino.h>
#include <Wire.h>
#include <MultiLCD.h>
LCD_SSD1306 lcd;
String distanceLcd="";

void setup()
{
  Serial.begin(9600);
  lcd.begin();
  pinMode(ECHOPIN, INPUT);
  pinMode(TRIGPIN, OUTPUT);
} 

void loop()
{
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
  float distance = pulseIn(ECHOPIN, HIGH);
  distance= distance/58;

  distanceLcd = "d=";
  distanceLcd += (int)distance;
  distanceLcd += ".";
  distanceLcd += ((int)(distance*10))%10;
  Serial.println(distanceLcd);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(distanceLcd);
  
  delay(1000);
}
