#include "task.h"
extern struct TIM2_TASK_COUNTER TIM2_TASK_COUNTER_DATA;

int pressPlatformStatu = 2;
int motorResetFlag = 1;
int pressPlatformDownFlag = 1, pressPlatformUpFlag = 0, magnetFlag = 0;
//如果要复位，则在这里设为1 ， 不需要则0
int RESET_FLAG = 0;

void framework() {
	if (RESET_FLAG) {
		motorReset();
	}
	//
	int but = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
	if (but) {//开关按下，开始执行流程
		//无刷电机复位
		
		//平台控制
		//单位MM
		setMotorDistance(-60,-60);
		
		
		//用来调滚筒正反转和停
		if (GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_13))
		{ 
			GPIO_SetBits(GPIOD,GPIO_Pin_14);
			GPIO_ResetBits(GPIOD,GPIO_Pin_15);
		}
		else if (GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_12))
		{ 
			//左滚筒逆时针  ,右滚筒顺时针
			GPIO_SetBits(GPIOD,GPIO_Pin_15);          // E    //高电平接通        
			GPIO_ResetBits(GPIOD,GPIO_Pin_14);       //  F             //继电器依次接左电机第一个，第二个，右电机第一个第二个为在第一个端口，第二个端口接地
			GPIO_SetBits(GPIOH,GPIO_Pin_2);
		}
		else 
		{
			GPIO_SetBits(GPIOD,GPIO_Pin_14);
			GPIO_SetBits(GPIOD,GPIO_Pin_15);
			GPIO_ResetBits(GPIOH,GPIO_Pin_2);
		}
		//上面用来调滚筒正反转和停
		
		//下面的机构
//   GPIO_ResetBits(GPIOD,GPIO_Pin_13);       //  G         //低电平断开，悬空
//  GPIO_SetBits(GPIOD,GPIO_Pin_12);          // H      //IO口依次接in1,in2,in3,in4           
 //第一个信号端口有输入为逆时针
  
 
		//第一个电机开始运转
//		GPIO_SetBits(GPIOI,GPIO_Pin_0);                   //A
//		GPIO_ResetBits(GPIOH,GPIO_Pin_12);                  //B  
//		GPIO_ResetBits(GPIOH,GPIO_Pin_11);
//		GPIO_ResetBits(GPIOH,GPIO_Pin_10);   
//		if (GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_1))        //I1       //触碰第一个行程开关
//		{
//			GPIO_ResetBits(GPIOI,GPIO_Pin_0); 
//			GPIO_ResetBits(GPIOH,GPIO_Pin_12);                     //第一个电机停止
//    
//			GPIO_SetBits(GPIOH,GPIO_Pin_11);                //C
//			GPIO_ResetBits(GPIOH,GPIO_Pin_10);             //D   //第二个电机运转
//    
//    if (GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_0))     //I2    //第二个电机触碰到限位开关
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
			//下面的机构
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

//		//左滚筒逆时针  ,右滚筒顺时针
//		GPIO_SetBits(GPIOD,GPIO_Pin_13);               //高电平接通        
//		GPIO_ResetBits(GPIOD,GPIO_Pin_12);                       //继电器依次接左电机第一个，第二个，右电机第一个第二个为在第一个端口，第二个端口接地
//		GPIO_ResetBits(GPIOD,GPIO_Pin_15);                  //低电平断开，悬空
//		GPIO_SetBits(GPIOD,GPIO_Pin_14);                 //IO口依次接in1,in2,in3,in4           
//		//第一个信号端口有输入为逆时针

//		//第一个电机开始运转
//		GPIO_SetBits(GPIOI,GPIO_Pin_0);
//		GPIO_ResetBits(GPIOH,GPIO_Pin_10);                      
//		if (GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_1))               //触碰第一个行程开关
//		{
//			GPIO_ResetBits(GPIOI,GPIO_Pin_0);
//			GPIO_ResetBits(GPIOH,GPIO_Pin_10);                     //第一个电机停止

//			GPIO_SetBits(GPIOH,GPIO_Pin_11);
//			GPIO_ResetBits(GPIOH,GPIO_Pin_12);                //第二个电机运转
//			//第二个电机触碰到限位开关
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



//G接in2，H接in1

//void pressPlatformControl(int mode) {
//	if (mode == 1) {
//	//mode 1为平台上升，执行上升动作
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
//	//mode 2为平台下降，执行下降动作
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





////黄色线v，黑色线u

void motorReset() {
	
	//当丝杆抵到复位限位开关时
	int PA1 = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1), PA2 = 0;
	if (PA1||PA2) {
		setMotorStop();
		motorResetFlag = 0;
	} else {
	//让无刷电机转回初始位置	
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
