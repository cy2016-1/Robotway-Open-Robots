#include "LedControl.h"

LedControl lc=LedControl(12,11,13,1);

void setup() 
{
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
  
  lc.setRow(0,0,0xff);
  lc.setRow(0,1,B10000001);
  lc.setRow(0,2,B10100101);
  lc.setRow(0,3,B10000001);
  lc.setRow(0,4,B11000011);
  lc.setRow(0,5,B10100101);
  lc.setRow(0,6,B10011001);
  lc.setRow(0,7,0xff);
}


void loop() 
{ 

}
