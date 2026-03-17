#ifndef __SERVO_H__
#define __SERVO_H__
#include "common.h"
#include "stm32f446xx.h"
#include "tim.h"

extern const float SERVO_MIN_ANGLE;
extern const float SERVO_MAX_ANGLE;
extern const uint32_t SERVO_MIN_COMPARE_VALUE;
extern const uint32_t SERVO_MAX_COMPARE_VALUE; 

extern TIM_TypeDef *SERVO_TIM_INSTANCE;
extern enum TIM_channel_e SERVO_TIM_CHANNEL;

void Servo_Init();

void Servo_SetAngle(uint32_t angle);

#endif // __SERVO_H__