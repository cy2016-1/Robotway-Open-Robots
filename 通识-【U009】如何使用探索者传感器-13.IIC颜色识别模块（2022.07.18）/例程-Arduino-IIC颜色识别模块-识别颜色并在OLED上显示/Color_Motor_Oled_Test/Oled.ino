
void Oled_Init() //oled屏幕初始化
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);  // initialize with the I2C addr 0x3C (for the 128x64)
  // init done
  
  display.display(); // show splashscreen
  delay(2000);
  display.clearDisplay();   // clears the screen and buffer  
}


void Get_Color_Data()
{
  display.clearDisplay(); //清屏
  String color_data = "";
  uint16_t clear, red, green, blue; //分别定义用于存储红、绿、蓝三色值变量
  tcs.getRGBC(&red, &green, &blue, &clear); //将原始R/G/B值转换为色温（以度为单位）
  tcs.lock();  //禁用中断（可省略）
  
  uint32_t sum = clear;           //===========
  float r, g, b;                  // 计算红
  r = red; r /= sum;              // 绿、蓝
  g = green; g /= sum;            // 三色数
  b = blue; b /= sum;             // 值
  r *= 256; g *= 256; b *= 256;   //===========
//  Serial.print("\t");////////////////////////////////////////////
//  Serial.print((int)r); Serial.print("\t"); // 在串口中分别打印
//  Serial.print((int)g); Serial.print("\t"); // 红、绿、蓝三色
//  Serial.print((int)b);                     // 值
//  Serial.println();//////////////////////////////////////////////
  if( (r > 0) && (g>0) && (b>0) && (r>g) && (r>b) )   //如果检测到红色，小车前进，oled屏幕显示red
  {
    color_data = "red";
    Motor_Go(Forward, 100);
  }

  else if( (r > 0) && (g>0) && (b>0) && (r<g) && (b<g) ) //如果检测到绿色，小车后退，oled屏幕显示green
  {
    color_data = "green";
    Motor_Go(Back, 100);
  }
  
  else if( (r > 0) && (g>0) && (b>0) && (r<b) && (g<b) ) //如果检测到蓝色，小车左转，oled屏幕显示blue
  {
    color_data = "blue";
    Motor_Go(Left, 100);
  }

  else{                        //否则，小车停止，oled屏幕显示none
    color_data = "none";
    Motor_Go(Stop, 0);
  }
  display.setTextSize(3); //修改字体大小
  display.setTextColor(WHITE); //修改字体颜色
  display.setCursor(20,24);  //修改字体位置  
  display.println(color_data); //显示内容
  display.display();
  delay(20);  
}
