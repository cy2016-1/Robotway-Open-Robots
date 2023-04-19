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

float Xmin = -100;                     //�����ͼ��Χ����60mm , ��60mm
float Xmax = 100;
float Ymin = -100;
float Ymax = 100;

float Xpos = 0;                       
float Ypos = 0;

char c;	
char line[ LINE_BUFFER_LENGTH ];
int lineIndex;
bool lineIsComment, lineSemiColon;
const int stepsPerRevolution = 3200;   //���岽�����ÿȦת���Ĳ������˴�Ϊ16ϸ�֣�ÿȦ 3200 ��

void processIncomingLine( char* line, int charNB );
void drawLine(float x1, float y1);

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif
 

char USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
u8 USART_RX_CONUT=0;				//	�����յ����ݵļ���
//��ʼ��IO ����1 
//bound:������
void usart_init(u32 bound){
  //GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//ʹ��USART1ʱ��
 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10����ΪUSART1
	
	//USART1�˿�����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9��GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA9��PA10

  //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART1, &USART_InitStructure); //��ʼ������1

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	//Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//��������ж�
	
	USART_Cmd(USART1, ENABLE);  //ʹ�ܴ���1 
}

//��ʼ��IO ����3
//bound:������	  
void usart3_init(u32 bound)
{  

	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //ʹ��GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//ʹ��USART3ʱ��

 	USART_DeInit(USART3);  //��λ����3
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIOB11����ΪUSART3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //GPIOB10����ΪUSART3	
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_10; //GPIOB11��GPIOB10��ʼ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOB,&GPIO_InitStructure); //��ʼ��GPIOB11����GPIOB10
	
	USART_InitStructure.USART_BaudRate = bound;//������ 
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  
	USART_Init(USART3, &USART_InitStructure); //��ʼ������3
 
	USART_Cmd(USART3, ENABLE);               //ʹ�ܴ��� 
	
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�����ж�   
	
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
}

u8 USART3_TX_BUF[USART_REC_LEN]; 	//���ͻ���,���USART3_MAX_SEND_LEN�ֽ�
u8 USART3_RX_BUF[USART_REC_LEN]; 				//���ջ���,���USART3_MAX_RECV_LEN���ֽ�.
vu16 USART3_RX_STA=0; 


//����3,printf ����
//ȷ��һ�η������ݲ�����USART3_MAX_SEND_LEN�ֽ�
void u3_printf(char* fmt,...)  
{  
	u16 i,j;
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)USART3_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART3_TX_BUF);//�˴η������ݵĳ���
	for(j=0;j<i;j++)//ѭ����������
	{
		 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������   
		USART_SendData(USART3,USART3_TX_BUF[j]);  
	}
}

float Ratio_backs = 3200/(3.14*58.2);//17.5015744

//ֱ�߲岹����������Ϊ������ֵ
void drawLine_new(float x1, float y1)
{
  int dx, dy, n, k, i, f, stepInc;
  //float LEAD = sqrt(2) * 58 * PI;        //���岽�����ת�� 1 Ȧ��С��ǰ���ľ��룬��λ mm
	
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

//ֱ�߲岹����������Ϊ������ֵ
void drawLine(float x1, float y1)
{
  int dx, dy, n, k, i, f, stepInc;
  //float LEAD = sqrt(2) * 58 * PI;        //���岽�����ת�� 1 Ȧ��С��ǰ���ľ��룬��λ mm
	
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


//�������ݴ�����
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



void USART1_IRQHandler(void)                	//����1�жϷ������
{	
	while(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)//�Ƿ�Ϊ�����ж�
	{
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	  c=USART_ReceiveData(USART1);				//��ȡ�������ݣ�һ�ֽڵ����ݣ�
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
	if(USART_GetFlagStatus(USART1,USART_FLAG_ORE) == SET) // ��� ORE ��־�����������־��
	{
      USART_ClearFlag(USART1,USART_FLAG_ORE);			//	��������־λ
	}	
} 



