#include "usart.h"	
#include "led.h" 
#include "math.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "a4988.h"
#include "pwm.h"

#define PI	3.14
#define LINE_BUFFER_LENGTH 512

typedef enum{
	false = 0,
	true = 1
}bool;

struct point {
  float x;
  float y;  
};

bool verbose = true;
struct point actuatorPos;

float Xmin = -100;                     //定义绘图范围，长60mm , 宽60mm
float Xmax = 100;
float Ymin = -100;
float Ymax = 100;

float Xpos = 0;                       
float Ypos = 0;

char c;	
char line[ LINE_BUFFER_LENGTH ];
int lineIndex;
bool lineIsComment, lineSemiColon;
const int stepsPerRevolution = 3200;   //定义步进电机每圈转动的步数，此处为16细分，每圈 3200 步

void processIncomingLine( char* line, int charNB );
void drawLine(float x1, float y1);

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif
 

char USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
u8 USART_RX_CONUT=0;				//	串口收到数据的计数
//初始化IO 串口1 
//bound:波特率
void usart_init(u32 bound){
  //GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//使能USART1时钟
 
	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9复用为USART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10复用为USART1
	
	//USART1端口配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9与GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA9，PA10

  //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(USART1, &USART_InitStructure); //初始化串口1

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启相关中断
	
	USART_Cmd(USART1, ENABLE);  //使能串口1 
}

//初始化IO 串口3
//bound:波特率	  
void usart3_init(u32 bound)
{  

	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //使能GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//使能USART3时钟

 	USART_DeInit(USART3);  //复位串口3
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIOB11复用为USART3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //GPIOB10复用为USART3	
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_10; //GPIOB11和GPIOB10初始化
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure); //初始化GPIOB11，和GPIOB10
	
	USART_InitStructure.USART_BaudRate = bound;//波特率 
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  
	USART_Init(USART3, &USART_InitStructure); //初始化串口3
 
	USART_Cmd(USART3, ENABLE);               //使能串口 
	
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启中断   
	
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
}

u8 USART3_TX_BUF[USART_REC_LEN]; 	//发送缓冲,最大USART3_MAX_SEND_LEN字节
u8 USART3_RX_BUF[USART_REC_LEN]; 				//接收缓冲,最大USART3_MAX_RECV_LEN个字节.
vu16 USART3_RX_STA=0; 


//串口3,printf 函数
//确保一次发送数据不超过USART3_MAX_SEND_LEN字节
void u3_printf(char* fmt,...)  
{  
	u16 i,j;
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)USART3_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART3_TX_BUF);//此次发送数据的长度
	for(j=0;j<i;j++)//循环发送数据
	{
		 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //循环发送,直到发送完毕   
		USART_SendData(USART3,USART3_TX_BUF[j]);  
	}
}

float Ratio_backs = 3200/(3.14*58.2);//17.5015744

//直线插补函数，参数为点坐标值
void drawLine_new(float x1, float y1)
{
  int dx, dy, n, k, i, f, stepInc;
  //float LEAD = sqrt(2) * 58 * PI;        //定义步进电机转动 1 圈，小车前进的距离，单位 mm
	
  if (x1 >= Xmax) { 
    x1 = Xmax; 
  }
  if (x1 <= Xmin) { 
    x1 = Xmin; 
  }
  if (y1 >= Ymax) {
    y1 = Ymax; 
  }
  if (y1 <= Ymin) { 
    y1 = Ymin; 
  }
	
  x1 = (int)(x1*Ratio_backs*0.31f);
  y1 = (int)(y1*Ratio_backs*0.8660254f);
		
  float x0 = Xpos;
  float y0 = Ypos;

  
  dx = myabs(x1-x0);
  dy = myabs(y1-y0);
  n = myabs(dx+dy);
  
  if(dx==0||dy==0)
  {
    stepInc = 1;
  }
  else
  {
    stepInc = 1;
  }
	
  if(x1 >= x0)
  {
    k = y1 >= y0 ? 1:4;
  }
  else
  {
    k = y1 >= y0 ? 2:3;
  }
  
  for(i=0,f=0;i<n;i+=1)
  {
    if(f>=0)
    {
      switch(k)
      {
         case 1:
				 Move_X_New(1);
         f = f - dy;
         break;
         case 2:
				 Move_X_New(-1);
         f = f - dy;
         break;
         case 3:
				 Move_X_New(-1);
         f = f - dy;
         break;
         case 4:
				 Move_X_New(1);
         f = f - dy;
         break;
         default:break;
      }
    }
    else
    {
      switch(k)
      {
        case 1:
				Move_Y_New(1);
        f = f + dx;
        break;
        case 2:
				Move_Y_New(1);
        f = f + dx;
        break;
        case 3:
				Move_Y_New(-1);
        f = f + dx;
        break;
        case 4:
				Move_Y_New(-1);
        f = f +dx;
        break;
        default:break;
      }
    }
  }
  Xpos = x1;
  Ypos = y1;
}

//直线插补函数，参数为点坐标值
void drawLine(float x1, float y1)
{
  int dx, dy, n, k, i, f, stepInc;
  //float LEAD = sqrt(2) * 58 * PI;        //定义步进电机转动 1 圈，小车前进的距离，单位 mm
	
  if (x1 >= Xmax) { 
    x1 = Xmax; 
  }
  if (x1 <= Xmin) { 
    x1 = Xmin; 
  }
  if (y1 >= Ymax) {
    y1 = Ymax; 
  }
  if (y1 <= Ymin) { 
    y1 = Ymin; 
  }
	
  x1 = (int)(x1*Ratio_backs*0.4897777f);
  y1 = (int)(y1*Ratio_backs*0.8660254f);
		
  float x0 = Xpos;
  float y0 = Ypos;

  
  dx = myabs(x1-x0);
  dy = myabs(y1-y0);
  n = myabs(dx+dy);
  
  if(dx==0||dy==0)
  {
    stepInc = 1;
  }
  else
  {
    stepInc = 1;
  }
	
  if(x1 >= x0)
  {
    k = y1 >= y0 ? 1:4;
  }
  else
  {
    k = y1 >= y0 ? 2:3;
  }
  
  for(i=0,f=0;i<n;i+=1)
  {
    if(f>=0)
    {
      switch(k)
      {
         case 1:
				 Move_X_New(1);
         f = f - dy;
         break;
         case 2:
				 Move_X_New(-1);
         f = f - dy;
         break;
         case 3:
				 Move_X_New(-1);
         f = f - dy;
         break;
         case 4:
				 Move_X_New(1);
         f = f - dy;
         break;
         default:break;
      }
    }
    else
    {
      switch(k)
      {
        case 1:
				Move_Y_New(1);
        f = f + dx;
        break;
        case 2:
				Move_Y_New(1);
        f = f + dx;
        break;
        case 3:
				Move_Y_New(-1);
        f = f + dx;
        break;
        case 4:
				Move_Y_New(-1);
        f = f +dx;
        break;
        default:break;
      }
    }
  }
  Xpos = x1;
  Ypos = y1;
}


//串口数据处理函数
void processIncomingLine( char* line, int charNB ) 
{
	char* indexX;
	char* indexY;
  int currentIndex = 0;
  char buffer[ 64 ];                                 // Hope that 64 is enough for 1 parameter
  struct point newPos;

  newPos.x = 0.0;
  newPos.y = 0.0;

  while( currentIndex < charNB ) {
    switch ( line[ currentIndex++ ] ) {              // Select command, if any

    case 'U':
      //stepper_moves(z_dir, z_stp, 2000); 
      break;
    case 'D':
      //stepper_moves(z_dir, z_stp, -2000); 
      break;
    case 'G':
      buffer[0] = line[ currentIndex++ ];
      buffer[1] = '\0';
		  //printf( "buffer: %c\n", buffer[0]);
		  //printf( "buffer: %c\n", buffer[1]);
		  //printf( "atof-buffer: %d\n", atoi( buffer ));
      switch ( atoi( buffer ) )
				{                   // Select G command
          case 0:                                   // G00 & G01 - Movement or fast movement. Same here
          case 1:
          indexX = strchr( line+currentIndex, 'X' );  // Get X/Y position in the string (if any)
          indexY = strchr( line+currentIndex, 'Y' );
					//printf( "indexX: %s\n", indexX);
					//printf( "indexY: %s\n", indexY);					
          if ( indexY <= 0 ) 
						{
              newPos.x = atof( indexX + 1); 
              newPos.y = actuatorPos.y;
							//printf( "x: %f\n", newPos.x);
							//printf( "y: %f\n", newPos.y);
            } 
          else if ( indexX <= 0 ) 
						{
              newPos.y = atof( indexY + 1);
              newPos.x = actuatorPos.x;
							//printf( "x: %f\n", newPos.x);
							//printf( "y: %f\n", newPos.y);							
            } 
          else 
						{
              newPos.y = atof( indexY + 1);
              indexY = "\0";
              newPos.x = atof( indexX + 1);
							//printf( "x: %f\n", newPos.x);
							//printf( "y: %f\n", newPos.y);							
            }
          drawLine(newPos.x, newPos.y );
          actuatorPos.x = newPos.x;
          actuatorPos.y = newPos.y;
          break;
					case 4:
						delay_ms(350);
						break;
        }
      break;
    case 'M':
      buffer[0] = line[ currentIndex++ ];        // /!\ Dirty - Only works with 3 digit commands
      buffer[1] = line[ currentIndex++ ];
      buffer[2] = line[ currentIndex++ ];
      buffer[3] = '\0';
      switch ( atoi( buffer ) ){
      case 300:
        {
          char* indexS = strchr( line+currentIndex, 'S' );
          float Spos = atof( indexS + 1);
          if (Spos == 30) {
						//stepper_move(z_dir, z_stp, 24);
            Put_Down();
						//stepper_move(z_dir, z_stp, -2000);
          }
          if (Spos == 50) {
						//stepper_move(z_dir, z_stp, -24);
            Put_Up();
						//stepper_move(z_dir, z_stp, 2000); 
          }
          break;
        }
      case 114:                                // M114 - Repport position
        printf( "Absolute position : X = %f",  actuatorPos.x);
			  printf( "%f\n", actuatorPos.x );
        printf( "  -  Y = %f\n", actuatorPos.y);
			  printf( "%f\n",actuatorPos.y );
        break;
      default:
        printf( "Command not recognized : M");
        printf( "%s\n", buffer );
      }
    }
  }
   
}



void USART1_IRQHandler(void)                	//串口1中断服务程序
{	
	while(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)//是否为接收中断
	{
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	  c=USART_ReceiveData(USART1);				//读取串口数据（一字节的数据）
      if (( c == '\n') || (c == '\r') ) {             // End of line reached
        if ( lineIndex > 0 ) {                        // Line is complete. Then execute!
          line[ lineIndex ] = '\0';                   // Terminate string
          if (verbose) { 
            printf("recv:%s\n", line);
          }
          processIncomingLine( line, lineIndex );
          lineIndex = 0;
        } 
        else { 
          // Empty or comment line. Skip block.
        }
        lineIsComment = false;
        lineSemiColon = false;
        printf("ok\n");    
      } 
      else {
        if ( (lineIsComment) || (lineSemiColon) ) {   // Throw away all comment characters
          if ( c == ')' )  lineIsComment = false;     // End of comment. Resume line.
        } 
        else {
          if ( c <= ' ' ) {                           // Throw away whitepace and control characters
          } 
          else if ( c == '/' ) {                    	// Block delete not supported. Ignore character.
          } 
          else if ( c == '(' ) {                    	// Enable comments flag and ignore all characters until ')' or EOL.
            lineIsComment = true;
          } 
          else if ( c == ';' ) {
            lineSemiColon = true;
          } 
          else if ( lineIndex >= LINE_BUFFER_LENGTH-1 ) {
            printf( "ERROR - lineBuffer overflow\n" );
            lineIsComment = false;
            lineSemiColon = false;
          } 
          else if ( c >= 'a' && c <= 'z' ) {        	// Upcase lowercase
            line[ lineIndex++ ] = c-'a'+'A';
          } 
          else {
            line[ lineIndex++ ] = c;
          }
        }
      }
		
	}
	if(USART_GetFlagStatus(USART1,USART_FLAG_ORE) == SET) // 检查 ORE 标志（串口溢出标志）
	{
      USART_ClearFlag(USART1,USART_FLAG_ORE);			//	清除溢出标志位
	}	
} 



