//Read amarino Sensor data and draw a graph like shown on the cellphone

import processing.serial.*;

Serial myPort;                  // Create object from Serial class
char buf_tmp    = 0;             // temp serial data
char [] buf     = new char[3];   // 
int x=0;
int y=0;
int filtered=0;
int i=0;

void setup() 
{
  fill(0);
  size(800,600);
  background(255);
  myPort = new Serial(this, "COM8", 9600); //change the COM number to meet your computer
}

void draw()
{
  if ( myPort.available() > 0 ) 
  { 
    buf_tmp = (char) myPort.read();       //get serial data
    if(buf_tmp=='\n')
    {
      i=0;
      x++;
      line(x-1,y,x,buf[0]);
      y=buf[0];
      line(x-1,filtered,x,buf[1]+300);
      filtered=buf[1]+300;
    }
    else
    {
      buf[i]= buf_tmp;
      i++;
    }
    if(x>width)
    {
      x=0;
      background(255);
    }
  }
}

