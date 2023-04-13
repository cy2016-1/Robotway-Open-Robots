void red();
void green();
void off();

void setup()
{
  pinMode( A4 , OUTPUT);
  pinMode( A5 , OUTPUT);
}

void loop()
{
  red();
  delay( 1000 );
  off();
  delay( 1000 );
  green();
  delay( 1000 );
  off();
  delay( 1000 );
}

void red()
{
  digitalWrite( A4 , HIGH );
  digitalWrite( A5 , LOW );
}

void off()
{
  digitalWrite( A4 , LOW );
  digitalWrite( A5 , LOW );
}

void green()
{
  digitalWrite( A4 , LOW );
  digitalWrite( A5 , HIGH );
}
