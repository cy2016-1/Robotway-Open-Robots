String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() 
{
  if(stringComplete)  //判断是否有数据输入
  {
    stringComplete = false;
    Serial.println((String)(calculate()));  //打印结果
  }
}
/******************************************
函数名称：calculate
函数功能：对输入数据进行四则运算
函数参数：无
返 回 值：运算结果
******************************************/
int calculate()
{
  char case_deal;
  int a, b, result, location;
  String tmp;

  inputString.trim(); //去掉回车
  Serial.print(inputString + '=');

//运算符号判断
  if((location = (inputString.indexOf('+'))) > 0)
  {
      case_deal = 1;
  }
  else if((location = (inputString.indexOf('-'))) > 0)
  {
      case_deal = 2;
  } 
  else if((location = (inputString.indexOf('*'))) > 0)
  {
      case_deal = 3;
  } 
  else if((location = (inputString.indexOf('/'))) > 0)
  {
      case_deal = 4;
  }
  else
  {
    Serial.println("error");  //错误处理
    return -1;
  }

  tmp = inputString.substring(0, location); //解析第一个数字
  a = tmp.toInt();  //将字符串转换成数字
  tmp = inputString.substring(location+1);  //解析第二个数字
  b = tmp.toInt();  //将字符串转换成数字

  switch (case_deal)  //运算处理
  {
       case 1:
         result = a + b;
         break;
       case 2:
         result = a - b;
         break;
       case 3:
          result = a * b;
          break;
       case 4:
          result = a / b;
          break;
       default:
          result = -1;
   } 
  inputString = ""; //输入清空，不然下次读入出错

  return result;
}

void serialEvent() 
{
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}


