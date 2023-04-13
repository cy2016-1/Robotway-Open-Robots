int _ABVAR_1_Data_of_bluetooth = 0 ;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  _ABVAR_1_Data_of_bluetooth = Serial.parseInt() ;
  if (( ( _ABVAR_1_Data_of_bluetooth ) > ( 0 ) ))
  {
    if (( ( _ABVAR_1_Data_of_bluetooth ) == ( 1 ) ))
    {
      Serial.print("I receive:1");
      Serial.println();
    }
    if (( ( _ABVAR_1_Data_of_bluetooth ) == ( 2 ) ))
    {
      Serial.print("I receive:2");
      Serial.println();
    }
  }
  else
  {
    delay( 10 );
  }
}


