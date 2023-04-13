#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

const int analogXPin = A0;            //set PAD port
const int analogYPin = A1; 

int xdata, ydata;

void setup()
{
  Serial.begin(9600);

  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"clie1");
  Mirf.payload = sizeof(char);
  Mirf.channel = 10;
  Mirf.config();
}

void loop()
{
  static byte data[2];
  data[0] = x_deal(analogXPin); 
  data[1] = y_deal(analogYPin);

  int tmp = data[0]*10 + data[1];
  data_send(tmp);
  Serial.println(data[0] + (String)('+') +data[1]);
  delay(50);
} 

void data_send(byte data)
{
  Mirf.setTADDR((byte *)"serv1");
  Mirf.send((byte *)&data);
  while(Mirf.isSending()){
  }
}

int x_deal(int value)
{
  int tmp = analogRead(value);
  Serial.print(tmp + (String)('+'));
  if(tmp > 700){
      tmp = 2;
  }
  else if(tmp < 550){
      tmp = 1;
  }
  else
    tmp = 0;
  return tmp;
}

int y_deal(int value)
{
  int tmp = analogRead(value);
  Serial.println(tmp);
  if(tmp > 600){
      tmp = 2;
  }
  else if(tmp < 400){
      tmp = 1;
  }
  else
    tmp = 0;
  return tmp;
}
