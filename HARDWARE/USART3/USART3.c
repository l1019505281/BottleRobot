#include "USART3.h"
#include "sys.h" 

static unsigned char TxBuffer[256];
static unsigned char TxCounter=0;
static unsigned char count=0; 
extern void CopeSerial2Data(unsigned char ucData);


void USART3_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStruct;
		NVIC_InitTypeDef NVIC_InitStruct;
		USART_InitTypeDef USART_InitStruct;
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
			
		GPIO_PinAFConfig( GPIOB, GPIO_PinSource10,GPIO_AF_USART3);
		GPIO_PinAFConfig( GPIOB, GPIO_PinSource11,GPIO_AF_USART3);
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
		GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
		GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
		GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
		GPIO_InitStruct.GPIO_Speed=GPIO_High_Speed;
		GPIO_Init(GPIOB,&GPIO_InitStruct);
		GPIO_InitStruct.GPIO_Pin=GPIO_Pin_11;
		GPIO_Init(GPIOB,&GPIO_InitStruct);
		USART_InitStruct.USART_BaudRate=9600;
		USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;	
		USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
		USART_InitStruct.USART_Parity=USART_Parity_No;
		USART_InitStruct.USART_StopBits=USART_StopBits_1;
		USART_InitStruct.USART_WordLength=USART_WordLength_8b;
		USART_Init(USART3,&USART_InitStruct);


		USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);

		NVIC_InitStruct.NVIC_IRQChannel=USART3_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
		NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;

		NVIC_Init(&NVIC_InitStruct);
		USART_Cmd(USART3,ENABLE);
}

void USART3_IRQHandler(void)
{
  if(USART_GetITStatus(USART3, USART_IT_TXE) != RESET)
  {   
    USART_SendData(USART3, TxBuffer[TxCounter++]); 
    USART_ClearITPendingBit(USART3, USART_IT_TXE);
    if(TxCounter == count) USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
  }
	else if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
  {
		CopeSerial2Data((unsigned char)USART3->DR);//处理数据
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
  }
	
	USART_ClearITPendingBit(USART3,USART_IT_ORE);
}


void UART3_Put_Char(unsigned char DataToSend)
{
	TxBuffer[count++] = DataToSend;  
  USART_ITConfig(USART3, USART_IT_TXE, ENABLE);  
}

void UART3_Put_String(unsigned char *Str)
{
	while(*Str)
	{
		if(*Str=='\r')UART3_Put_Char(0x0d);
			else if(*Str=='\n')UART3_Put_Char(0x0a);
				else UART3_Put_Char(*Str);
		Str++;
	}
}