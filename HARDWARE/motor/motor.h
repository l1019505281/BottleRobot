#include "sys.h"
#include "CRC.h"
#include "rs485.h"
void setMotorSpeed(uint16_t speed_l, uint16_t speed_r);
void setMotorPWM(uint16_t pwm_l, uint16_t pwm_r);
void setMotorDistance(uint32_t disLeft, uint32_t disRight);
void setMotorUp(void);
void setMotorStop(void);