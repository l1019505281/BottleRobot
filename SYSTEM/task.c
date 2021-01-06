#include "task.h"
extern struct TIM2_TASK_COUNTER TIM2_TASK_COUNTER_DATA;

int pressPlatformStatu = 2;
int motorResetFlag = 1;
int pressPlatformDownFlag = 1, pressPlatformUpFlag = 0, magnetFlag = 0;
void framework() {
	GPIO_SetBits(GPIOH,GPIO_Pin_2);

	//���Ͳ��ʱ��  ,�ҹ�Ͳ˳ʱ��
	GPIO_SetBits(GPIOD,GPIO_Pin_13);               //�ߵ�ƽ��ͨ        
	GPIO_ResetBits(GPIOD,GPIO_Pin_12);                       //�̵������ν�������һ�����ڶ������ҵ����һ���ڶ���Ϊ�ڵ�һ���˿ڣ��ڶ����˿ڽӵ�
	GPIO_ResetBits(GPIOD,GPIO_Pin_15);                  //�͵�ƽ�Ͽ�������
	GPIO_SetBits(GPIOD,GPIO_Pin_14);                 //IO�����ν�in1,in2,in3,in4           
	//��һ���źŶ˿�������Ϊ��ʱ��

	//��һ�������ʼ��ת
	GPIO_SetBits(GPIOI,GPIO_Pin_0);
	GPIO_ResetBits(GPIOH,GPIO_Pin_10);                      
	if (GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_1))               //������һ���г̿���
		{
			GPIO_ResetBits(GPIOI,GPIO_Pin_0);
			GPIO_ResetBits(GPIOH,GPIO_Pin_10);                     //��һ�����ֹͣ

			GPIO_SetBits(GPIOH,GPIO_Pin_11);
			GPIO_ResetBits(GPIOH,GPIO_Pin_12);                //�ڶ��������ת
			//�ڶ��������������λ����
			if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_0))         
				{
					GPIO_ResetBits(GPIOH,GPIO_Pin_11);
					GPIO_ResetBits(GPIOH,GPIO_Pin_12);
				}
		} 
	 else
		{ 
			GPIO_ResetBits(GPIOI,GPIO_Pin_0);
			GPIO_ResetBits(GPIOH,GPIO_Pin_10);
			GPIO_ResetBits(GPIOH,GPIO_Pin_11);
			GPIO_ResetBits(GPIOH,GPIO_Pin_12);
		}
}
			 
//	if(1) {//���ذ��£���ʼִ������
//		//��ˢ�����λ
//		if (motorResetFlag) {
//			motorReset();
//		} else {
//			return;
//		}
//		//ƽ̨����
//		if (pressPlatformDownFlag) {
//			pressPlatformStatu = 2;
//		}
//		//���������
//		if (magnetFlag) {
//			GPIO_SetBits(GPIOH,GPIO_Pin_2);
//		}
//		
//		//��ˢ�������	
////		setMotorDistance(900);
//		
//		//��Ͳ���ƣ�
//		
//		//ƽ̨����
////		if (pressPlatformUpFlag) {
////			pressPlatformStatu = 1;
////		}
//	} else {
//	}



//G��in2��H��in1

//void pressPlatformControl(int mode) {
//	if (mode == 1) {
//	//mode 1Ϊƽ̨������ִ����������
//		GPIO_SetBits(GPIOD,GPIO_Pin_13);
//		GPIO_ResetBits(GPIOD,GPIO_Pin_12);
//		if (GPIO_ReadInputDataBit(GPIOH,GPIO_Pin_10)) {
//			pressPlatformStatu = 0;
//			pressPlatformUpFlag = 0;
//			pressPlatformDownFlag = 1;
//			
//		}
//	}
//	else if (mode == 2) {
//	//mode 2Ϊƽ̨�½���ִ���½�����
//		GPIO_SetBits(GPIOD,GPIO_Pin_12);
//		GPIO_ResetBits(GPIOD,GPIO_Pin_13);
//		if (GPIO_ReadInputDataBit(GPIOH,GPIO_Pin_11)) {
//			pressPlatformStatu = 0;
//			pressPlatformDownFlag = 0;
//			pressPlatformUpFlag = 1;
//			magnetFlag = 1;
//		}
//	}
//	else {
//	GPIO_ResetBits(GPIOD,GPIO_Pin_12);
//	GPIO_ResetBits(GPIOD,GPIO_Pin_13);
//	}
//}





////��ɫ��v����ɫ��u

//void motorReset() {
//	//����ˢ���ת�س�ʼλ��
//	setMotorSpeed(500,500);
//	//��˿�˵ֵ���λ��λ����ʱ
//	if (GPIO_ReadInputDataBit(GPIOH,GPIO_Pin_12)) {
//		setMotorSpeed(0,0);
//		motorResetFlag = 0;
//	}
//}

void task_1000Hz(void)
{

}


void task_500Hz(void)
{

}


void task_200Hz(void)
{
	
}


void task_100Hz(void)
{
	
}


void task_50Hz(void)
{
	
}


void task_20Hz(void)
{

}


void task_10Hz(void)
{
	
}


void task_5Hz(void)
{
	
}


void task_2Hz(void)
{
	framework();
}


void task_1Hz(void)
{
		
}

// ����ʹ����һ��Ƶ�����е�ѭ��
void task_frequency_control_main_loop(void)
{
	while(1)
	{
		if(TIM2_TASK_COUNTER_DATA.COUNTER_1MS >= 1)
		{
			task_1000Hz();
			TIM2_TASK_COUNTER_DATA.COUNTER_1MS = 0;
		}
		
		if(TIM2_TASK_COUNTER_DATA.COUNTER_2MS >= 2)
		{
			task_500Hz();
			TIM2_TASK_COUNTER_DATA.COUNTER_2MS = 0;
		}	
		
		if(TIM2_TASK_COUNTER_DATA.COUNTER_5MS >= 5)
		{
			task_200Hz();
			TIM2_TASK_COUNTER_DATA.COUNTER_5MS = 0;
		}	

		if(TIM2_TASK_COUNTER_DATA.COUNTER_10MS >= 10)
		{
			task_100Hz();
			TIM2_TASK_COUNTER_DATA.COUNTER_10MS = 0;
		}

		if(TIM2_TASK_COUNTER_DATA.COUNTER_20MS >= 20)
		{
			task_50Hz();
			TIM2_TASK_COUNTER_DATA.COUNTER_20MS = 0;
		}

		if(TIM2_TASK_COUNTER_DATA.COUNTER_50MS >= 50)
		{
			task_20Hz();
			TIM2_TASK_COUNTER_DATA.COUNTER_50MS = 0;
		}

		if(TIM2_TASK_COUNTER_DATA.COUNTER_100MS >= 100)
		{
			task_10Hz();
			TIM2_TASK_COUNTER_DATA.COUNTER_100MS = 0;
		}

		if(TIM2_TASK_COUNTER_DATA.COUNTER_200MS >= 200)
		{
			task_5Hz();
			TIM2_TASK_COUNTER_DATA.COUNTER_200MS = 0;
		}

		if(TIM2_TASK_COUNTER_DATA.COUNTER_500MS >= 500)
		{
			task_2Hz();
			TIM2_TASK_COUNTER_DATA.COUNTER_500MS = 0;
		}		
		
		if(TIM2_TASK_COUNTER_DATA.COUNTER_1000MS >= 1000)
		{
			task_1Hz();
			TIM2_TASK_COUNTER_DATA.COUNTER_1000MS = 0;
		}	
	}
}
