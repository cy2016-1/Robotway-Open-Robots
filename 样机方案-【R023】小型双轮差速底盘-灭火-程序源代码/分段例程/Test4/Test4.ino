/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-07-14 https://www.robotway.com/
  ------------------------------*/
int pin[3] = {A0, A2, A4};	//定义火焰传感器的引脚，此处用到了三个
int value[3];	 //用于存储传感器的变量值

void setup()
{
  SerialUSB.begin(9600);	//打开串口
} 

void loop()
{
	for(int i=0; i<3; i++){		//通过循环扫描读取传感器的值
	    value[i] = analogRead(pin[i]);	//analogRead()用于读取传感器的AD值
	}
    SerialUSB.println(ValueDeal());	//串口打印传感器的触发状态
    delay(500);
}

int ValueDeal()		//火焰传感器识别函数，根据返回值的不同可以判断传感器的触发状态
{
	if(value[0] < 900 || value[1] < 900 || value[2] < 900){
	    if(value[0] < value[1]){
	        if(value [0] < value[2]){
	            return 0;	//A0引脚连接的传感器触发
	        }
	        else
	        	return 2;	//A4引脚连接的传感器触发
	    }
	    else
	    {
	    	if(value[1] < value[2]){
	    	    return 1;	//A2引脚连接的传感器触发
	    	}
	    	else
	    		return 2;
	    }
	}
	return 3;	//无触发
}
