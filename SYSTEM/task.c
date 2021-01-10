#include "task.h"
extern struct TIM2_TASK_COUNTER TIM2_TASK_COUNTER_DATA;

int pressPlatformStatu = 2;
int motorResetFlag = 1;
int pressPlatformDownFlag = 1, pressPlatformUpFlag = 0, magnetFlag = 0;
//���Ҫ��λ������������Ϊ1 �� ����Ҫ��0
int RESET_FLAG = 0;

void framework() {
	if (RESET_FLAG) {
		motorReset();
	}
	//
	int but = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
	if (but) {//���ذ��£���ʼִ������
		//��ˢ�����λ
		
		//ƽ̨����
		//��λMM
		setMotorDistance(-60,-60);
		
		
		//��������Ͳ����ת��ͣ
		if (GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_13))
		{ 
			GPIO_SetBits(GPIOD,GPIO_Pin_14);
			GPIO_ResetBits(GPIOD,GPIO_Pin_15);
		}
		else if (GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_12))
		{ 
			//���Ͳ��ʱ��  ,�ҹ�Ͳ˳ʱ��
			GPIO_SetBits(GPIOD,GPIO_Pin_15);          // E    //�ߵ�ƽ��ͨ        
			GPIO_ResetBits(GPIOD,GPIO_Pin_14);       //  F             //�̵������ν�������һ�����ڶ������ҵ����һ���ڶ���Ϊ�ڵ�һ���˿ڣ��ڶ����˿ڽӵ�
			GPIO_SetBits(GPIOH,GPIO_Pin_2);
		}
		else 
		{
			GPIO_SetBits(GPIOD,GPIO_Pin_14);
			GPIO_SetBits(GPIOD,GPIO_Pin_15);
			GPIO_ResetBits(GPIOH,GPIO_Pin_2);
		}
		//������������Ͳ����ת��ͣ
		
		//����Ļ���
//   GPIO_ResetBits(GPIOD,GPIO_Pin_13);       //  G         //�͵�ƽ�Ͽ�������
//  GPIO_SetBits(GPIOD,GPIO_Pin_12);          // H      //IO�����ν�in1,in2,in3,in4           
 //��һ���źŶ˿�������Ϊ��ʱ��
  
 
		//��һ�������ʼ��ת
//		GPIO_SetBits(GPIOI,GPIO_Pin_0);                   //A
//		GPIO_ResetBits(GPIOH,GPIO_Pin_12);                  //B  
//		GPIO_ResetBits(GPIOH,GPIO_Pin_11);
//		GPIO_ResetBits(GPIOH,GPIO_Pin_10);   
//		if (GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_1))        //I1       //������һ���г̿���
//		{
//			GPIO_ResetBits(GPIOI,GPIO_Pin_0); 
//			GPIO_ResetBits(GPIOH,GPIO_Pin_12);                     //��һ�����ֹͣ
//    
//			GPIO_SetBits(GPIOH,GPIO_Pin_11);                //C
//			GPIO_ResetBits(GPIOH,GPIO_Pin_10);             //D   //�ڶ��������ת
//    
//    if (GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_0))     //I2    //�ڶ��������������λ����
//     {
//       GPIO_ResetBits(GPIOH,GPIO_Pin_11);
//       GPIO_ResetBits(GPIOH,GPIO_Pin_12);
//     }
//  else
//     { 
//		 GPIO_ResetBits(GPIOI,GPIO_Pin_0);
//     GPIO_ResetBits(GPIOH,GPIO_Pin_10);
//     GPIO_ResetBits(GPIOH,GPIO_Pin_11);
//     GPIO_ResetBits(GPIOH,GPIO_Pin_12);
//    }
//}
			//����Ļ���
	} else {
		if (!RESET_FLAG) {
		setMotorDistance(0,0);
		}
		GPIO_ResetBits(GPIOH,GPIO_Pin_2);
		GPIO_SetBits(GPIOD,GPIO_Pin_14);
		GPIO_SetBits(GPIOD,GPIO_Pin_15);
	}
	

}
			 
//		GPIO_SetBits(GPIOH,GPIO_Pin_2);

//		//���Ͳ��ʱ��  ,�ҹ�Ͳ˳ʱ��
//		GPIO_SetBits(GPIOD,GPIO_Pin_13);               //�ߵ�ƽ��ͨ        
//		GPIO_ResetBits(GPIOD,GPIO_Pin_12);                       //�̵������ν�������һ�����ڶ������ҵ����һ���ڶ���Ϊ�ڵ�һ���˿ڣ��ڶ����˿ڽӵ�
//		GPIO_ResetBits(GPIOD,GPIO_Pin_15);                  //�͵�ƽ�Ͽ�������
//		GPIO_SetBits(GPIOD,GPIO_Pin_14);                 //IO�����ν�in1,in2,in3,in4           
//		//��һ���źŶ˿�������Ϊ��ʱ��

//		//��һ�������ʼ��ת
//		GPIO_SetBits(GPIOI,GPIO_Pin_0);
//		GPIO_ResetBits(GPIOH,GPIO_Pin_10);                      
//		if (GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_1))               //������һ���г̿���
//		{
//			GPIO_ResetBits(GPIOI,GPIO_Pin_0);
//			GPIO_ResetBits(GPIOH,GPIO_Pin_10);                     //��һ�����ֹͣ

//			GPIO_SetBits(GPIOH,GPIO_Pin_11);
//			GPIO_ResetBits(GPIOH,GPIO_Pin_12);                //�ڶ��������ת
//			//�ڶ��������������λ����
//			if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_0))         
//				{
//					GPIO_ResetBits(GPIOH,GPIO_Pin_11);
//					GPIO_ResetBits(GPIOH,GPIO_Pin_12);
//				}
//		} 
//	 else
//		{ 
//			GPIO_ResetBits(GPIOI,GPIO_Pin_0);
//			GPIO_ResetBits(GPIOH,GPIO_Pin_10);
//			GPIO_ResetBits(GPIOH,GPIO_Pin_11);
//			GPIO_ResetBits(GPIOH,GPIO_Pin_12);
//		}



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

void motorReset() {
	
	//��˿�˵ֵ���λ��λ����ʱ
	int PA1 = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1), PA2 = 0;
	if (PA1||PA2) {
		setMotorStop();
		motorResetFlag = 0;
	} else {
	//����ˢ���ת�س�ʼλ��	
		setMotorUp();
	}
}

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
	
}


void task_1Hz(void)
{
	framework();	
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
