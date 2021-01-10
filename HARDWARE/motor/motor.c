#include "delay.h"
#include "sys.h"
#include "motor.h"

//02 06 00 43 00 C8 79 BB 
//01 06 00 43 00 C8 79 88 

//01 06 00 40 00 00 88 1E 
//02 06 00 40 00 00 88 2D 

u8 Speed_R_raw[6] = {0x01, 0x06, 0x00, 0x43, 0x00, 0x00};
u8 Speed_L_raw[6] = {0x02, 0x06, 0x00, 0x43, 0x00, 0x00};
u8 Speed_R[8] = {0x01, 0x06, 0x00, 0x43, 0x00, 0x00, 0x00, 0x00};
u8 Speed_L[8] = {0x02, 0x06, 0x00, 0x43, 0x00, 0x00, 0x00, 0x00};

u8 distanceRawLeft[15] = {0x02, 0x10, 0x00, 0x44, 0x00, 0x04, 0x08, 0x01, 0xF4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
u8 distanceLeft[17] = {0x02, 0x10, 0x00, 0x44, 0x00, 0x04, 0x08, 0x01, 0xF4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	
u8 distanceRawRight[15] = {0x01, 0x10, 0x00, 0x44, 0x00, 0x04, 0x08, 0x01, 0xF4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
u8 distanceRight[17] = {0x01, 0x10, 0x00, 0x44, 0x00, 0x04, 0x08, 0x01, 0xF4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	
u8 finaDistance[34] = {0x01, 0x10, 0x00, 0x44, 0x00, 0x04, 0x08, 0x01, 0xF4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x10, 0x00, 0x44, 0x00, 0x04, 0x08, 0x01, 0xF4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
//01 10 00 44 00 04 08 13 88 00 00

void setMotorUp()
{
	u8 upSpeedRight[8] = {0x01, 0x06, 0x00, 0x43, 0x00, 0xC8, 0x79, 0x88};
	u8 upSpeedLeft[8] = {0x02, 0x06, 0x00, 0x43, 0x00, 0xC8, 0x79, 0xBB};
		
	RS485_Send_Data(upSpeedLeft,8);
	delay_ms(30);
	RS485_Send_Data(upSpeedRight,8);
}

void setMotorStop()
{
	u8 upSpeedRight[8] = {0x01, 0x06, 0x00, 0x40, 0x00, 0x00, 0x88, 0x1E};
	u8 upSpeedLeft[8] = { 0x02, 0x06, 0x00, 0x40, 0x00, 0x00, 0x88, 0x2D};
		
	RS485_Send_Data(upSpeedLeft,8);
	delay_ms(30);
	RS485_Send_Data(upSpeedRight,8);}

void setMotorSpeed(uint16_t speed_l, uint16_t speed_r)
{
	uint8_t h,l;
	uint16_t hz_1 = 10*3*speed_l/2;
	uint16_t hz_r = 10*3*speed_r/2;
	
	Speed_L_raw[5] = hz_1&0xFF;
	Speed_L_raw[4] = (hz_1>>8)&0xFF;
	Speed_L[5] = hz_1&0xFF;
	Speed_L[4] = (hz_1>>8)&0xFF;
	h = CRC16_H(Speed_L_raw, 6);
	l = CRC16_L(Speed_L_raw, 6);
	Speed_L[7] = h;
	Speed_L[6] = l;
	

	Speed_R_raw[5] = hz_r&0xFF;
	Speed_R_raw[4] = (hz_r>>8)&0xFF;
	Speed_R[5] = hz_r&0xFF;
	Speed_R[4] = (hz_r>>8)&0xFF;
	h = CRC16_H(Speed_R_raw, 6);
	l = CRC16_L(Speed_R_raw, 6);
	Speed_R[7] = h;
	Speed_R[6] = l;
	RS485_Send_Data(Speed_L, 8);
	delay_ms(15);
	RS485_Send_Data(Speed_R, 8);
}

//负数往下，正数网上
void setMotorDistance(uint32_t disLeft_mm, uint32_t disRight_mm)
{
	//进行单位转换
	uint32_t disLeft = -(int)(-disLeft_mm*2.4);
	uint32_t disRight = -(int)(-disRight_mm*2.4);
	uint8_t highCRC,lowCRC;
		
	distanceRawLeft[14] = disLeft&0xFF;
	distanceRawLeft[13] = (disLeft>>8)&0xFF;
	distanceRawLeft[12] = (disLeft>>16)&0xFF;
	distanceRawLeft[11] = (disLeft>>24)&0xFF;
	distanceLeft[14] = disLeft&0xFF;
	distanceLeft[13] = (disLeft>>8)&0xFF;	
	distanceLeft[12] = (disLeft>>16)&0xFF;
	distanceLeft[11] = (disLeft>>24)&0xFF;
	


	highCRC = CRC16_H(distanceRawLeft, 15);
	lowCRC = CRC16_L(distanceRawLeft, 15);
	distanceLeft[16] = highCRC;
	distanceLeft[15] = lowCRC;
	
	distanceRawRight[14] = disRight&0xFF;
	distanceRawRight[13] = (disRight>>8)&0xFF;
	distanceRawRight[12] = (disRight>>16)&0xFF;
	distanceRawRight[11] = (disRight>>24)&0xFF;
	distanceRight[14] = disRight&0xFF;
	distanceRight[13] = (disRight>>8)&0xFF;	
	distanceRight[12] = (disRight>>16)&0xFF;
	distanceRight[11] = (disRight>>24)&0xFF;
	highCRC = CRC16_H(distanceRawRight, 15);
	lowCRC = CRC16_L(distanceRawRight, 15);
	distanceRight[16] = highCRC;
	distanceRight[15] = lowCRC;

	RS485_Send_Data(distanceLeft, 17);
	delay_ms(30);
	RS485_Send_Data(distanceRight, 17);
}
//只有正数
void setDistanByBottleDiameter(uint32_t BottleDiameter) {
	
	setMotorDistance(-BottleDiameter, -BottleDiameter);
}

//01 10 00 44 00 04 08 13 88 00 00 00 00 00 51 CE 67
//01 10 00 44 00 04 08 01 F4 00 00 00 00 00 51 F3 75

//01 10 00 44 00 04 08 01 F4 00 00 FF FF FF C4 72 CE
// 一单位 30度 1 == 0.416mm
//void setMotorDistance(uint32_t disLeft, uint32_t disRight)
//{
//	uint8_t highCRC,lowCRC;
//	distanceRawLeft[14] = disLeft&0xFF;
//	distanceRawLeft[13] = (disLeft>>8)&0xFF;
//	distanceRawLeft[12] = (disLeft>>16)&0xFF;
//	distanceRawLeft[11] = (disLeft>>24)&0xFF;
//	distanceLeft[14] = disLeft&0xFF;
//	distanceLeft[13] = (disLeft>>8)&0xFF;	
//	distanceLeft[12] = (disLeft>>16)&0xFF;
//	distanceLeft[11] = (disLeft>>24)&0xFF;
//	


//	highCRC = CRC16_H(distanceRawLeft, 15);
//	lowCRC = CRC16_L(distanceRawLeft, 15);
//	distanceLeft[16] = highCRC;
//	distanceLeft[15] = lowCRC;

//	finaDistance[16] = highCRC;
//	finaDistance[15] = lowCRC;

//	
//	distanceRawRight[14] = disRight&0xFF;
//	distanceRawRight[13] = (disRight>>8)&0xFF;
//	distanceRawRight[12] = (disRight>>16)&0xFF;
//	distanceRawRight[11] = (disRight>>24)&0xFF;
//	distanceRight[14] = disRight&0xFF;
//	distanceRight[13] = (disRight>>8)&0xFF;	
//	distanceRight[12] = (disRight>>16)&0xFF;
//	distanceRight[11] = (disRight>>24)&0xFF;
//	highCRC = CRC16_H(distanceRawRight, 15);
//	lowCRC = CRC16_L(distanceRawRight, 15);
//	distanceRight[16] = highCRC;
//	distanceRight[15] = lowCRC;

//	finaDistance[33] = highCRC;
//	finaDistance[32] = lowCRC;
//  //30 12
//	RS485_Send_Data(distanceLeft, 17);
//	delay_ms(30);
//	//73 13
//	RS485_Send_Data(distanceRight, 17);


//	finaDistance[14] = disLeft&0xFF;
//	finaDistance[13] = (disLeft>>8)&0xFF;
//	finaDistance[12] = (disLeft>>16)&0xFF;
//	finaDistance[11] = (disLeft>>24)&0xFF;
//	finaDistance[31] = disLeft&0xFF;
//	finaDistance[30] = (disLeft>>8)&0xFF;
//	finaDistance[29] = (disLeft>>16)&0xFF;
//	finaDistance[28] = (disLeft>>24)&0xFF;

////	RS485_Send_Data(finaDistance, 34);
//}
