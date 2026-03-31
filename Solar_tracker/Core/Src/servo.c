#include "servo.h"

const float SERVO_MIN_ANGLE = 0;
const float SERVO_MAX_ANGLE = 180;
const uint32_t SERVO_MIN_COMPARE_VALUE = 500;
const uint32_t SERVO_MAX_COMPARE_VALUE = 2500;

TIM_TypeDef *SERVO_TIM_INSTANCE = TIM2;
enum TIM_channel_e SERVO_TIM_CHANNEL = TIM_CHANNEL_2;

void Servo_Init() {

  if (TIM_is_started(SERVO_TIM_INSTANCE)) {
    TIM_stop(SERVO_TIM_INSTANCE);
  }
  TIM_set_prescaler(SERVO_TIM_INSTANCE, 8400);
  TIM_set_autoreload(SERVO_TIM_INSTANCE, 200);
  TIM_set_counter(SERVO_TIM_INSTANCE, 0);
  TIM_enable_auto_reload_buffering(SERVO_TIM_INSTANCE);
  TIM_disable_OCx_preload(SERVO_TIM_INSTANCE, SERVO_TIM_CHANNEL);
  TIM_set_direction(SERVO_TIM_INSTANCE, UPCOUNTING);
  TIM_set_OCx_compared_value(SERVO_TIM_INSTANCE, SERVO_TIM_CHANNEL, 190);
  TIM_set_output_compare_polarity(SERVO_TIM_INSTANCE, SERVO_TIM_CHANNEL, TIM_OC_POL_ACTIVE_LOW);
  TIM_set_OCx_mode(SERVO_TIM_INSTANCE, SERVO_TIM_CHANNEL, TIM_OC_MODE_PWM1);
  TIM_enable_OCx(SERVO_TIM_INSTANCE, SERVO_TIM_CHANNEL);

  TIM_start(SERVO_TIM_INSTANCE);
}

void Servo_SetAngle(uint32_t angle) {
    if (angle < SERVO_MIN_ANGLE) {
        angle = SERVO_MIN_ANGLE;
    } else if (angle > SERVO_MAX_ANGLE) {
        angle = SERVO_MAX_ANGLE;
    }

    //uint32_t compare_value = (uint32_t)((angle / SERVO_MAX_ANGLE) * (SERVO_MAX_COMPARE_VALUE - SERVO_MIN_COMPARE_VALUE) + SERVO_MIN_COMPARE_VALUE);
    uint32_t compare_value = 175 + ((angle * 2000) / 180) / 100; // Formule linéaire pour convertir l'angle en valeur de comparaison
    TIM_set_OCx_compared_value(SERVO_TIM_INSTANCE, SERVO_TIM_CHANNEL, compare_value);
}
