#ifndef __MOTOR_H
#define __MOTOR_H

#include "main.h"
void motor_Init(uint8_t enable,uint8_t num);
void motor_enable(uint8_t enable,uint8_t num);
void motor_DIR(uint8_t dir,uint8_t num);  //电机转向
void motor_pwm_set(uint8_t num,int duty);
void MySPI_SwapByte(uint8_t Enable);
void DRV8462_WriteReg(uint8_t Enable,uint8_t addr, uint8_t data);

#endif
