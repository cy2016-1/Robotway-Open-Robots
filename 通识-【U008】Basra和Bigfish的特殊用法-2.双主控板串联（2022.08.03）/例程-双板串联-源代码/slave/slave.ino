

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() 
{

	pinMode(5,OUTPUT);
	pinMode(6,OUTPUT);
	  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
	
	
}

void loop() 
{	
	  // print the string when a newline arrives:
  // ServoStay();
  if (stringComplete) 
  {
    Serial.print(inputString); 

    if(inputString=="a") 
   {
     digitalWrite(5,HIGH);
     digitalWrite(6,LOW);
   }
  }
}

void serialEvent() {
	 int  data =0;
  while (Serial.available()) {
    // get the new byte:
  //  String oldinputString ;
  if(data<1)
  { 
  	inputString = "";
    data++;
 }
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
     if (inChar == '\n') 
     {         
      stringComplete = true;

     } 
    else inputString += inChar;

    } 
  }

