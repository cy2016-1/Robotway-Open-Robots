#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

void setup()
{
  Serial.begin(9600);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"serv1");
  Mirf.payload = sizeof(char);
  Mirf.channel=10;
  Mirf.config();
  Motor(0, 0);
  Motor(1, 0);
}

void loop()
{
  byte data[Mirf.payload];
  if(!Mirf.isSending() && Mirf.dataReady())
  {
    Mirf.getData(data);
  }

  int value[2];
  value[0] = data[0]/10;
  value[1] = data[0]%10;

  if(value[1] == 1){  //后
      value[0] = 2;
      value[1] = 2;
  }
  else if(value[1] == 2){ //前
      value[0] = 1;
      value[1] = 1;
  }
  else if(value[0] == 1){ //右转
      value[1] = 0;
      value[0] = 1;
  }
  else if(value[0] == 2){ //左转
      value[1] = 1;
      value[0] = 0;
  }
  else
  {
    value[0] = 0;
    value[1] = 0;
  }

  Motor(0, value[0]);
  Motor(1, value[1]);
}

void Motor( int which , int where )
{
  if( which == 0 )
  {
    if( where == 0)
    {
        digitalWrite( 9 ,LOW );
        digitalWrite( 10 ,LOW );
    }
    if ( where == 1) 
    {
      digitalWrite(9, HIGH);
        digitalWrite( 10 ,LOW  );    
    }
    if ( where == 2) 
    {
      digitalWrite( 9 ,LOW  );
      digitalWrite(10, HIGH);
    }
  }
  if( which == 1 )
  {
    if( where == 0)
    {
      digitalWrite( 5 ,LOW );
      digitalWrite( 6 ,LOW );
    }
    if ( where == 1) 
    {
        digitalWrite( 5 ,HIGH );
        digitalWrite( 6 ,LOW );    
    }
    if ( where == 2) 
    {
      digitalWrite( 5 ,LOW );
      digitalWrite( 6 ,HIGH );    
    }
  }
}
