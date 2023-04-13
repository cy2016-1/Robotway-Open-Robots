int a = 0 ;
int b = 0 ;

void ADGet();
void SerialPrint();

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  ADGet();
  SerialPrint();
  delay( 100 );
}

void ADGet()
{
  a = analogRead(14) ;
  b = analogRead(15) ;
  a = map ( a , 0 , 1024 , 0 , 3 )  ;
  b = map ( b , 0 , 1024 , 0 , 3 )  ;
}

void SerialPrint()
{
  if (( ( ( a ) == ( 0 ) ) && ( ( b ) == ( 1 ) ) ))
  {
    Serial.print("1");
    Serial.println();
  }
  if (( ( ( a ) == ( 1 ) ) && ( ( b ) == ( 0 ) ) ))
  {
    Serial.print("2");
    Serial.println();
  }
  if (( ( ( a ) == ( 1 ) ) && ( ( b ) == ( 1 ) ) ))
  {
    Serial.print("3");
    Serial.println();
  }
  if (( ( ( a ) == ( 1 ) ) && ( ( b ) == ( 2 ) ) ))
  {
    Serial.print("4");
    Serial.println();
  }
  if (( ( ( a ) == ( 2 ) ) && ( ( b ) == ( 1 ) ) ))
  {
    Serial.print("5");
    Serial.println();
  }
}
