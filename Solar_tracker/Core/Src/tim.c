#include "tim.h"
#include "common.h"
#include "stm32f446xx.h"

err_t TIM_set_mode(TIM_TypeDef *p_tim, enum TIM_mode_e mode) {
	if (mode == TIM_NORMAL_MODE) {
		p_tim->CCMR1 &= ~TIM_CCMR1_CC1S; // Clear CC1S bits to set output compare mode
		p_tim->CCMR1 &= ~TIM_CCMR1_OC1M;  // Clear OC1M bits
		p_tim->CCMR1 |= (0b000 << TIM_CCMR1_OC1M_Pos); // Set OC1M to 000 for normal mode
	} else if (mode == TIM_INPUT_CAPTURE_MODE) {
		p_tim->CCMR1 &= ~TIM_CCMR1_OC1M;  // Clear OC1M bits
		p_tim->CCMR1 |= (0b01 << TIM_CCMR1_CC1S_Pos); // Set CC1S to 01 for input capture mode
	} else if (mode == TIM_OUTPUT_COMPARE_MODE) {
		p_tim->CCMR1 &= ~TIM_CCMR1_CC1S; // Clear CC1S bits to set output compare mode
		p_tim->CCMR1 &= ~TIM_CCMR1_OC1M;  // Clear OC1M bits
		p_tim->CCMR1 |= (0b110 << TIM_CCMR1_OC1M_Pos); // Set OC1M to 110 for output compare mode
	} else {
		return ERR_INVALID_PARAM;
	}
	return ERR_NONE;
}

void TIM_enable_auto_reload_buffering(TIM_TypeDef *p_tim) {
	p_tim->CR1 |= TIM_CR1_ARPE;
}

void TIM_disable_auto_reload_buffering(TIM_TypeDef *p_tim) {
	p_tim->CR1 &= ~TIM_CR1_ARPE;
}

err_t TIM_set_direction(TIM_TypeDef *p_tim, enum TIM_count_direction_e direction) {
	if (direction == UPCOUNTING) {
		p_tim->CR1 &= ~TIM_CR1_DIR;
	} else if (direction == DOWNCOUNTING) {
		p_tim->CR1 |= TIM_CR1_DIR;
	} else {
		return ERR_INVALID_PARAM;
	}
	return ERR_NONE;
}

void TIM_set_one_pulse_mode(TIM_TypeDef *p_tim) {
	p_tim->CR1 |= TIM_CR1_OPM;
}

void TIM_unset_one_pulse_mode(TIM_TypeDef *p_tim) {
	p_tim->CR1 &= ~TIM_CR1_OPM;
}


err_t TIM_SetUpdateRequestSource(TIM_TypeDef *p_tim, enum TIM_update_request_source_e source) {
	if (source == TIM_UPDATE_REQUEST_SOURCE_ALL) {
		p_tim->CR1 &= ~TIM_CR1_URS;
	} else if (source == TIM_UPDATE_REQUEST_SOURCE_ONLY_OVERFLOW) {
		p_tim->CR1 |= TIM_CR1_URS;
	} else {
		return ERR_INVALID_PARAM;
	}
	return ERR_NONE;
}

enum TIM_update_request_source_e TIM_GetUpdateRequestSource(TIM_TypeDef *p_tim) {
	if (p_tim->CR1 & TIM_CR1_URS) {
		return TIM_UPDATE_REQUEST_SOURCE_ONLY_OVERFLOW;
	}
	return TIM_UPDATE_REQUEST_SOURCE_ALL;
}

void TIM_enable_update_event(TIM_TypeDef *p_tim) {
	p_tim->CR1 &= ~TIM_CR1_UDIS;
}

void TIM_disable_update_event(TIM_TypeDef *p_tim) {
	p_tim->CR1 |= TIM_CR1_UDIS;
}

void TIM_enable_update_interrupt(TIM_TypeDef *p_tim) {
	p_tim->DIER |= TIM_DIER_UIE;
}

void TIM_disable_update_interrupt(TIM_TypeDef *p_tim) {
	p_tim->DIER &= ~TIM_DIER_UIE;
}

err_t TIM_enable_CCx_interrupt(TIM_TypeDef *p_tim, enum TIM_channel_e channel) {
	switch(channel) {
		case TIM_CHANNEL_1:
			p_tim->DIER |= TIM_DIER_CC1IE;
			break;
		case TIM_CHANNEL_2:
			p_tim->DIER |= TIM_DIER_CC2IE;
			break;
		case TIM_CHANNEL_3:
			p_tim->DIER |= TIM_DIER_CC3IE;
			break;
		case TIM_CHANNEL_4:
			p_tim->DIER |= TIM_DIER_CC4IE;
			break;
		default:
			return ERR_INVALID_PARAM;
	}
	return ERR_NONE;
}

err_t TIM_disable_CCx_interrupt(TIM_TypeDef *p_tim, enum TIM_channel_e channel) {
	switch(channel) {
		case TIM_CHANNEL_1:
			p_tim->DIER &= ~TIM_DIER_CC1IE;
			break;
		case TIM_CHANNEL_2:
			p_tim->DIER &= ~TIM_DIER_CC2IE;
			break;
		case TIM_CHANNEL_3:
			p_tim->DIER &= ~TIM_DIER_CC3IE;
			break;
		case TIM_CHANNEL_4:
			p_tim->DIER &= ~TIM_DIER_CC4IE;
			break;
		default:
			return ERR_INVALID_PARAM;
	}
	return ERR_NONE;
}

bool TIM_is_update_interrupt_pending(TIM_TypeDef *p_tim) {
	if (p_tim->SR & TIM_SR_UIF) {
		return true;
	}
	return false;
}

void TIM_clear_update_interrupt_flag(TIM_TypeDef *p_tim) {
	
}

bool TIM_is_started(TIM_TypeDef *p_tim) {
	return (p_tim->CR1 & TIM_CR1_CEN) ? true : false;
}

void TIM_start(TIM_TypeDef *p_tim) {
	p_tim->CR1 |= TIM_CR1_CEN;
}
void TIM_stop(TIM_TypeDef *p_tim) {
	p_tim->CR1 &= ~TIM_CR1_CEN;
}

void TIM_set_autoreload(TIM_TypeDef *p_tim, uint32_t autoreload) {
	p_tim->ARR = autoreload;
}

void TIM_set_counter(TIM_TypeDef *p_tim, uint32_t counter) {
	p_tim->CNT = counter;
}