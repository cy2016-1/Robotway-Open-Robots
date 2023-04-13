import processing.serial.*;

Serial myPort;
String inputString = "";
boolean event = false;
int [] rgb = new int[3];

void setup() 
{
	fill(0);
	size(500, 400);
	background(255);
	myPort = new Serial(this, "COM3", 9600);
}

void draw() 
{
  
    if ( myPort.available() > 0 ) 
    { 
        char inChar = (char)myPort.read();       //get serial data
        inputString += inChar;
        if(inChar=='\n') 
            event = true;
  }

	if (event) 
	{
        background(255);
        
        int x = 0;
        for(int i = 0; i < 3; i++)
        {
          String tmp = inputString.substring(0, inputString.indexOf('+'));
          inputString = inputString.substring(inputString.indexOf('+')+1, inputString.length());
          tmp = tmp.trim();
          rgb[i] = int(tmp);
        }
        
        for(int i = 0; i < 3; i++)
        {
          if(rgb[i] > 255) rgb[i] = 255;
          if(rgb[i] < 0)   rgb[i] = 0;
        }
        
        textSize(25);
        fill(255, 0, 0);
        text('R', 130, 30);
        fill(0, 255, 0);
        text('G', 230, 30);
        fill(0, 0, 255);
        text('B', 330, 30);
        fill(255, 0, 0);
        text(rgb[0], 120, 60);
        fill(0, 255, 0);
        text(rgb[1], 220, 60);
        fill(0, 0, 255);
        text(rgb[2], 320, 60);
        
        colorMode(RGB, 255);
        fill(rgb[0], rgb[1], rgb[2]);
        rect(100, 100, 300, 200);
        String inputString = "";
        event = false;
        fill(0);
        x += 50;
    }
}