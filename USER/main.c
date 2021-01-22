#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "key.h"
#include "rs485.h"
#include "CRC.h"
#include "motor.h"
#include "JY901.h"
#include "PID.h"
#include <string.h>
#include <stdio.h>
#include "USART3.h"
#include "JY901.h"
#include "task.h"
#include "tim2.h"

extern u8  USART_RX_BUF[USART_REC_LEN]; 
int data;
u8 rs485cmd[8] = {0x01, 0x06, 0x00, 0x42, 0x00, 0x64, 0x28, 0x35};
u8 rs485dat[8];	
uint8_t h,l;

u8 PWM_10_R[8] = {0x01, 0x06, 0x00, 0x42, 0x00, 0x64, 0x28, 0x35};
u8 PWM_10_L[8] = {0x02, 0x06, 0x00, 0x42, 0x00, 0x64, 0x28, 0x06};
u8 Stop[8] = {0x01,0x06,0x00,0x40,0x00,0x00,0x88,0x1E};
u8 Stop2[8] = {0x02,0x06,0x00,0x40,0x00,0x00,0x88,0x2D};
u8 PWM_f30_R[8] = {0x01,0x06,0x00,0x42,0xFE,0xD4,0x69,0xE1};


extern u8 Speed_R[8];

int main(void)
{ 
	char str[100];
	u8 key, num;
	u8 cnt=0;
	float angle;
	//u8 rs485buf[5]; 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);   //初始化延时函数
	uart_init(115200);	//初始化串口波特率为115200
	LED_Init();					//初始化LED 
	KEY_Init(); 				//按键初始化  
	RS485_Init(6400);		//初始化RS485串口2	
	tim2_TIM2_init();
	uart6_init(6400);
	task_frequency_control_main_loop();
}


 
