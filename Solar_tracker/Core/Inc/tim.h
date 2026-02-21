#ifndef __TIM_H__
#define __TIM_H__

TIM_SetMode();

TIM_EnableAutoReloadPreload();
TIM_DisableAutoReloadPreload();

TIM_SetDirection();

TIM_SetOnePulseMode();
TIM_UnsetOnePulseMode();

TIM_EnableUpdateInterrupt();
TIM_DisableUpdateInterrupt();

// Status checking and update
TIM_UpdateInterruptPending();
TIM_ClearUpdateInterruptFlag();

TIM_CCxInterruptPending(uint8_t channel);
TIM_ClearCCxInterruptFlag(uint8_t channel);

TIM_GenerateCCxEvent();
TIM_GenerateUpdateEvent();

TIM_Start();
TIM_Stop();

TIM_PWM_SetCCRx(uint8_t channel);

TIM_SetPrescaler();

TIM_SetARR();
TIM_SetCounter();

TIM_OutputCompare_Set()

#endif // __TIM_H__