#include <SignalFilter.h>
SignalFilter Filter;
char filtered;

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
  Filter.begin();
  Filter.setFilter('m');
  Filter.setOrder(2);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);            
  // map it to the range of the analog out:
  char outputValue = map(sensorValue, 0, 1023, 0, 255);  
  filtered= Filter.run(outputValue);
  Serial.print(outputValue);
  Serial.println(filtered);   

  delay(100);                     
}
