void stop();
void spin();

void setup()
{
  pinMode( 14, INPUT);
  pinMode( 5 , OUTPUT);
  pinMode( 6 , OUTPUT);
}

void loop()
{
  if (!( digitalRead(14) ))
  {
    spin();
  }
  else
  {
    stop();
  }
}

void stop()
{
  digitalWrite( 5 , LOW );
  digitalWrite( 6 , LOW );
}

void spin()
{
  digitalWrite( 5 , HIGH );
  digitalWrite( 6 , LOW );
}


