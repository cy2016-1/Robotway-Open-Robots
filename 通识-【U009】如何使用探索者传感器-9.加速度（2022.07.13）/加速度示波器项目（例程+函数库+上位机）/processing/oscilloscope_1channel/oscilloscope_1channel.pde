import processing.serial.*;

Serial myPort;                  // Create object from Serial class
int buf_tmp    = 0;             // temp serial data
int x=0;
int y=0;

void setup() 
{
  fill(0);
  size(800,300);
  background(255);
  myPort = new Serial(this, "COM6", 9600); //change the COM number to meet your computer
}

void draw()
{
  if ( myPort.available() > 0 ) 
  { 
    buf_tmp = myPort.read();       //get serial data
    x++;
    line(x-1,y,x,buf_tmp);
    y=buf_tmp;
    if(x>width)
    {
      x=0;
      background(255);
    }
  }
}
