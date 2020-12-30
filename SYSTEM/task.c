#include "task.h"
extern struct TIM2_TASK_COUNTER TIM2_TASK_COUNTER_DATA;

int pressPlatformStatu = 2;
int motorResetFlag = 1;
int pressPlatformDownFlag = 1, pressPlatformUpFlag = 0, magnetFlag = 0;
void framework() {
	if(1) {//开关按下，开始执行流程
		//无刷电机复位
		if (motorResetFlag) {
			motorReset();
		} else {
			return;
		}
		//平台控制
		if (pressPlatformDownFlag) {
			pressPlatformStatu = 2;
		}
		//电磁铁控制
		if (magnetFlag) {
			GPIO_SetBits(GPIOH,GPIO_Pin_2);
		}
		
		//无刷电机控制	
//		setMotorDistance(900);
		
		//滚筒控制？
		
		//平台控制
//		if (pressPlatformUpFlag) {
//			pressPlatformStatu = 1;
//		}
	} else {
	}
}

void speed_adjust()
{
//	u8 Speed[8] = {0x01, 0x06, 0x00, 0x42, 0x01, 0x6E, 0xA9, 0xA2};
//	RS485_Send_Data(Speed, 8);
//	setMotorSpeed(1000, 1000);
	setMotorDistance(900);
}

//G接in2，H接in1

void pressPlatformControl(int mode) {
	if (mode == 1) {
	//mode 1为平台上升，执行上升动作
		GPIO_SetBits(GPIOD,GPIO_Pin_13);
		GPIO_ResetBits(GPIOD,GPIO_Pin_12);
		if (GPIO_ReadInputDataBit(GPIOH,GPIO_Pin_10)) {
			pressPlatformStatu = 0;
			pressPlatformUpFlag = 0;
			pressPlatformDownFlag = 1;
			
		}
	}
	else if (mode == 2) {
	//mode 2为平台下降，执行下降动作
		GPIO_SetBits(GPIOD,GPIO_Pin_12);
		GPIO_ResetBits(GPIOD,GPIO_Pin_13);
		if (GPIO_ReadInputDataBit(GPIOH,GPIO_Pin_11)) {
			pressPlatformStatu = 0;
			pressPlatformDownFlag = 0;
			pressPlatformUpFlag = 1;
			magnetFlag = 1;
		}
	}
	else {
	GPIO_ResetBits(GPIOD,GPIO_Pin_12);
	GPIO_ResetBits(GPIOD,GPIO_Pin_13);
	}
}







void motorReset() {
	//让无刷电机转回初始位置
	setMotorSpeed(500,500);
	//当丝杆抵到复位限位开关时
	if (GPIO_ReadInputDataBit(GPIOH,GPIO_Pin_12)) {
		setMotorSpeed(0,0);
		motorResetFlag = 0;
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
	framework();
}


void task_1Hz(void)
{
		
}

// 用于使任务按一定频率运行的循环
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
