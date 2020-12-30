#ifndef __USART3_H
#define __USART3_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 

void UART3_Put_String(unsigned char *Str);
void UART3_Put_Char(unsigned char DataToSend);
void USART3_IRQHandler(void);
void USART3_Init(void);

#endif