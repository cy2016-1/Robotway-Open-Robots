#include <Servo.h> 
#include <MsTimer2.h>

int servoPort[5]={8,3,11,7,4};
Servo myServo[5];
long servoCount[5];
boolean begin[5] = {true,true,true,true,true};
boolean complete[5] = {false,false,false,false,false};
int direct[5] = {1,1,1,1,1};
int delta[5] = {0,0,0,0,0};

long timeCount;
#define DELTATIME 10

int up = 30;
int down = 120;
int turnTime = 1000;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {         
  Serial.begin(9600);       
  for(int i = 0; i < 5; i++)
  	myServo[i].attach(servoPort[i]);    
  MsTimer2::set(DELTATIME, Timer); 
  MsTimer2::start();
  delay(100);
}


void loop() {
	static int phase[5] = {0,0,0,0,0};

	if (stringComplete) {
		Serial.println(inputString); 

		up = inputString.substring(0,inputString.indexOf(',')).toInt();
		inputString = inputString.substring(inputString.indexOf(',')+1,inputString.length());

		down = inputString.substring(0,inputString.indexOf(',')).toInt();
		turnTime = inputString.substring(inputString.indexOf(',')+1,inputString.length()).toInt();

		Serial.println(up);
		Serial.println(down);
		Serial.println(turnTime);

		inputString = "";
		stringComplete = false;
	}

	if(phase[0] == 0)
		if(ServoMove(0,up,down,turnTime))
			phase[0] = 1;
	if(phase[0] == 1)
		if(ServoMove(0,down,up,turnTime))
			phase[0] = 0;	

	if(servoCount[0]>0 && (timeCount - servoCount[0])>(turnTime/(4*DELTATIME))){
		if(phase[1] == 0)
			if(ServoMove(1,up,down,turnTime))
				phase[1] = 1;
		if(phase[1] == 1)
			if(ServoMove(1,down,up,turnTime))
				phase[1] = 0;		
	}

	
	if(servoCount[1]>0 && (timeCount - servoCount[1])>(turnTime/(4*DELTATIME))){
		if(phase[2] == 0)
			if(ServoMove(2,up,down,turnTime))
				phase[2] = 1;
		if(phase[2] == 1)
			if(ServoMove(2,down,up,turnTime))
				phase[2] = 0;	
	}

	if(servoCount[2]>0 && (timeCount - servoCount[2])>(turnTime/(4*DELTATIME))){
		if(phase[3] == 0)
			if(ServoMove(3,up,down,turnTime))
				phase[3] = 1;
		if(phase[3] == 1)
			if(ServoMove(3,down,up,turnTime))
				phase[3] = 0;
	}

	if(servoCount[3]>0 && (timeCount - servoCount[3])>(turnTime/(4*DELTATIME))){
		if(phase[4] == 0)
			if(ServoMove(4,up,down,turnTime))
				phase[4] = 1;
		if(phase[4] == 1)
			if(ServoMove(4,down,up,turnTime))
				phase[4] = 0;	
	}
}

void Timer() {
	timeCount++;
}

void serialEvent() {
	while (Serial.available()) {
		char inChar = (char)Serial.read(); 
		inputString += inChar;
    	if (inChar == '\n')
			stringComplete = true;
  	}
}

boolean ServoMove(int which, int start, int finish, long t)
{
	if(begin[which]){
		if( ( start - finish ) > 0 ) 
			direct[which] = -1;
		else 
			direct[which] = 1;

		servoCount[which] = timeCount;
		begin[which] = false;
		complete[which] = false;
	}
	else{
		if( ( timeCount - servoCount[which] ) < (t/DELTATIME) ){
			if( ( timeCount - servoCount[which] ) > ( delta[which] * (t/DELTATIME) / (abs(start-finish)) ) ){
				myServo[which].write( start + delta[which] * direct[which] );	
				delay(1);
				delta[which]++;			
				//Serial.println(start + i * a);
			}
		}
		else{
			delta[which] = 0;
			begin[which] = true;
			//servoCount[which] = 0;
			complete[which] = true;
		}		
	}

	return (complete[which]);
}
