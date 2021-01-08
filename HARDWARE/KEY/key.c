#include "key.h"
#include "delay.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//按键输入驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

//按键初始化函数
void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH|RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOH,GPIOE时钟
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_11|GPIO_Pin_10; //10总开关,11为上面的限位开关，12为无刷电机的复位开关。
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//下拉
  GPIO_Init(GPIOH, &GPIO_InitStructure);//初始化
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13; //10总开关,11为上面的限位开关，12为无刷电机的复位开关。
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//下拉
  GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化
	 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_0; //10总开关,11为上面的限位开关，12为无刷电机的复位开关。
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//下拉
  GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化	
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//WK_UP对应引脚PA0
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;//下拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA0
 
} 



















