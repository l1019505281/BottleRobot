#include "led.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

//��ʼ��PF9��PF10Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOH|RCC_AHB1Periph_GPIOI, ENABLE);//ʹ��GPIODʱ��

  //GPIOF9,F10��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;//�綯��Ͳ
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
  GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��
	GPIO_ResetBits(GPIOD,GPIO_Pin_14 | GPIO_Pin_15);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_11 | GPIO_Pin_10;//
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
  GPIO_Init(GPIOH, &GPIO_InitStructure);//��ʼ��
	GPIO_ResetBits(GPIOH,GPIO_Pin_12 | GPIO_Pin_10 | GPIO_Pin_11 );
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//     4��Ϊ�ײ�����ź�
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
  GPIO_Init(GPIOI, &GPIO_InitStructure);//��ʼ��
	GPIO_ResetBits(GPIOI,GPIO_Pin_0);                                    

	//������ӿ�ΪPinH2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;//�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
  GPIO_Init(GPIOH, &GPIO_InitStructure);//��ʼ��
	GPIO_ResetBits(GPIOH,GPIO_Pin_2);
}






