void stop();
void left();
void right();
void forwards();

void setup()
{
  pinMode( 18, INPUT);
  pinMode( 14, INPUT);
  pinMode( 10, OUTPUT);
  pinMode( 6, OUTPUT);
  pinMode( 5, OUTPUT);
  pinMode( 9, OUTPUT);
}

void loop()
{
  if (( !( digitalRead(14) ) && digitalRead(18) ))
  {
    right();
  }
  else
  {
    if (( digitalRead(14) && !( digitalRead(18) ) ))
    {
      left();
    }
    else
    {
      if (( !( digitalRead(14) ) && !( digitalRead(18) ) ))
      {
        stop();
      }
      else
      {
        forwards();
      }
    }
  }
}

void stop()
{
  analogWrite(5 , 0);
  analogWrite(9 , 0);
  analogWrite(6 , 0);
  analogWrite(10 , 0);
}

void right()
{
  analogWrite(5 , 150);
  analogWrite(9 , 0);
  analogWrite(6 , 0);
  analogWrite(10 , 150);
}

void forwards()
{
  analogWrite(5 , 150);
  analogWrite(9 , 0);
  analogWrite(6 , 150);
  analogWrite(10 , 0);
}

void left()
{
  analogWrite(5 , 0);
  analogWrite(9 , 150);
  analogWrite(6 , 150);
  analogWrite(10 , 0);
}
