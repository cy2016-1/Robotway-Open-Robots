int a = 0 ;
int a_his = 0 ;
int b = 0 ;

void Right();
void Select();
void Stop();
void Left();
void Back();
void Forward();

void setup()
{
  Serial.begin(9600);
  pinMode( 5 , OUTPUT);
  pinMode( 6 , OUTPUT);
  pinMode( 9 , OUTPUT);
  pinMode( 10 , OUTPUT);
  a = 3 ;
  a_his = 3 ;

}

void loop()
{
  a = Serial.parseInt() ;
  if (( ( a ) > ( 0 ) ))
  {
    Select();
  }
  else
  {
    a = a_his ;
    Select();
  }
  a_his = a ;
  a = b ;
  delay( 50 );
}

void Select()
{
  if (( ( a ) == ( 1 ) ))
  {
    Forward();
  }
  if (( ( a ) == ( 2 ) ))
  {
    Back();
  }
  if (( ( a ) == ( 3 ) ))
  {
    Stop();
  }
  if (( ( a ) == ( 4 ) ))
  {
    Left();
  }
  if (( ( a ) == ( 5 ) ))
  {
    Right();
  }
}

void Back()
{
  digitalWrite( 5 , LOW );
  digitalWrite( 6 , HIGH );
  digitalWrite( 9 , LOW );
  digitalWrite( 10 , HIGH );
}

void Forward()
{
  digitalWrite( 5 , HIGH );
  digitalWrite( 6 , LOW );
  digitalWrite( 9 , HIGH );
  digitalWrite( 10 , LOW );
}

void Stop()
{
  digitalWrite( 5 , LOW );
  digitalWrite( 6 , LOW );
  digitalWrite( 9 , LOW );
  digitalWrite( 10 , LOW );
}

void Left()
{
  digitalWrite( 5 , LOW );
  digitalWrite( 6 , HIGH );
  digitalWrite( 9 , HIGH );
  digitalWrite( 10 , LOW );
}

void Right()
{
  digitalWrite( 5 , HIGH );
  digitalWrite( 6 , LOW );
  digitalWrite( 9 , LOW );
  digitalWrite( 10 , HIGH );
}
