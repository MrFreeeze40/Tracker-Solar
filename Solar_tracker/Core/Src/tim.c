#include "tim.h"
#include "common.h"
#include "stm32f446xx.h"
#include "stm32f4xx.h"

err_t TIM_set_mode(TIM_TypeDef *p_tim, enum TIM_mode_e mode) {
    if (mode == TIM_NORMAL_MODE) {
        p_tim->CCMR1 &=
            ~TIM_CCMR1_CC1S; // Clear CC1S bits to set output compare mode
        p_tim->CCMR1 &= ~TIM_CCMR1_OC1M; // Clear OC1M bits
    } else if (mode == TIM_INPUT_CAPTURE_MODE) {
        p_tim->CCMR1 |=
            (0b01
             << TIM_CCMR1_CC1S_Pos); // Set CC1S to 01 for input capture mode
    } else if (mode == TIM_OUTPUT_COMPARE_MODE) {
        CLEAR_BIT(p_tim->CCMR1,
                  TIM_CCMR1_CC1S); // Clear CC1S bits to set output compare mode
        CLEAR_BIT(p_tim->CCMR1, TIM_CCMR1_OC1M); // Clear OC1M bits
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

err_t TIM_set_direction(TIM_TypeDef *p_tim,
                        enum TIM_count_direction_e direction) {
    if (direction == UPCOUNTING) {
        p_tim->CR1 &= ~TIM_CR1_DIR;
    } else if (direction == DOWNCOUNTING) {
        p_tim->CR1 |= TIM_CR1_DIR;
    } else {
        return ERR_INVALID_PARAM;
    }
    return ERR_NONE;
}

void TIM_set_one_pulse_mode(TIM_TypeDef *p_tim) { p_tim->CR1 |= TIM_CR1_OPM; }

void TIM_unset_one_pulse_mode(TIM_TypeDef *p_tim) {
    p_tim->CR1 &= ~TIM_CR1_OPM;
}

err_t TIM_SetUpdateRequestSource(TIM_TypeDef *p_tim,
                                 enum TIM_update_request_source_e source) {
    if (source == TIM_UPDATE_REQUEST_SOURCE_ALL) {
        p_tim->CR1 &= ~TIM_CR1_URS;
    } else if (source == TIM_UPDATE_REQUEST_SOURCE_ONLY_OVERFLOW) {
        p_tim->CR1 |= TIM_CR1_URS;
    } else {
        return ERR_INVALID_PARAM;
    }
    return ERR_NONE;
}

enum TIM_update_request_source_e
TIM_GetUpdateRequestSource(TIM_TypeDef *p_tim) {
    if (p_tim->CR1 & TIM_CR1_URS) {
        return TIM_UPDATE_REQUEST_SOURCE_ONLY_OVERFLOW;
    }
    return TIM_UPDATE_REQUEST_SOURCE_ALL;
}

void TIM_enable_update_event(TIM_TypeDef *p_tim) {
    CLEAR_BIT(p_tim->CR1, TIM_CR1_UDIS);
}

void TIM_disable_update_event(TIM_TypeDef *p_tim) {
    SET_BIT(p_tim->CR1, TIM_CR1_UDIS);
}

void TIM_enable_update_interrupt(TIM_TypeDef *p_tim) {
    p_tim->DIER |= TIM_DIER_UIE;
}

void TIM_disable_update_interrupt(TIM_TypeDef *p_tim) {
    p_tim->DIER &= ~TIM_DIER_UIE;
}

err_t TIM_enable_CCx_interrupt(TIM_TypeDef *p_tim, enum TIM_channel_e channel) {
    switch (channel) {
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

err_t TIM_disable_CCx_interrupt(TIM_TypeDef *p_tim,
                                enum TIM_channel_e channel) {
    switch (channel) {
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
    if (READ_BIT(p_tim->SR, TIM_SR_UIF)) {
        return true;
    }
    return false;
}

void TIM_clear_update_interrupt_flag(TIM_TypeDef *p_tim) {
    CLEAR_BIT(p_tim->SR, TIM_SR_UIF);
}

bool TIM_is_CCx_interrupt_pending(TIM_TypeDef *p_tim,
                                  enum TIM_channel_e channel) {
    switch (channel) {
    case TIM_CHANNEL_1:
        return READ_BIT(p_tim->SR, TIM_SR_CC1IF) != 0;
    case TIM_CHANNEL_2:
        return READ_BIT(p_tim->SR, TIM_SR_CC2IF) != 0;
    case TIM_CHANNEL_3:
        return READ_BIT(p_tim->SR, TIM_SR_CC3IF) != 0;
    case TIM_CHANNEL_4:
        return READ_BIT(p_tim->SR, TIM_SR_CC4IF) != 0;
    default:
        return false;
    }
}

err_t TIM_clear_CCx_interrupt_flag(TIM_TypeDef *p_tim,
                                   enum TIM_channel_e channel) {
    switch (channel) {
    case TIM_CHANNEL_1:
        CLEAR_BIT(p_tim->SR, TIM_SR_CC1IF);
        break;
    case TIM_CHANNEL_2:
        CLEAR_BIT(p_tim->SR, TIM_SR_CC2IF);
        break;
    case TIM_CHANNEL_3:
        CLEAR_BIT(p_tim->SR, TIM_SR_CC3IF);
        break;
    case TIM_CHANNEL_4:
        CLEAR_BIT(p_tim->SR, TIM_SR_CC4IF);
        break;
    default:
        return ERR_INVALID_PARAM;
    }
    return ERR_NONE;
}

err_t TIM_generate_CCx_event(TIM_TypeDef *p_tim, enum TIM_channel_e channel) {
    switch (channel) {
    case TIM_CHANNEL_1:
        SET_BIT(p_tim->EGR, TIM_EGR_CC1G);
        break;
    case TIM_CHANNEL_2:
        SET_BIT(p_tim->EGR, TIM_EGR_CC2G);
        break;
    case TIM_CHANNEL_3:
        SET_BIT(p_tim->EGR, TIM_EGR_CC3G);
        break;
    case TIM_CHANNEL_4:
        SET_BIT(p_tim->EGR, TIM_EGR_CC4G);
        break;
    default:
        return ERR_INVALID_PARAM;
    }
    return ERR_NONE;
}

void TIM_generate_update_event(TIM_TypeDef *p_tim) {
    SET_BIT(p_tim->EGR, TIM_EGR_UG);
}

bool TIM_is_started(TIM_TypeDef *p_tim) {
    return (READ_BIT(p_tim->CR1, TIM_CR1_CEN)) ? true : false;
}

void TIM_start(TIM_TypeDef *p_tim) { SET_BIT(p_tim->CR1, TIM_CR1_CEN); }
void TIM_stop(TIM_TypeDef *p_tim) { CLEAR_BIT(p_tim->CR1, TIM_CR1_CEN); }

err_t TIM_set_OCx_compared_value(TIM_TypeDef *p_tim, uint8_t channel,
                                 uint32_t value) {
    switch (channel) {
    case TIM_CHANNEL_1:
        WRITE_REG(p_tim->CCR1, value);
        break;
    case TIM_CHANNEL_2:
        WRITE_REG(p_tim->CCR2, value);
        break;
    case TIM_CHANNEL_3:
        WRITE_REG(p_tim->CCR3, value);
        break;
    case TIM_CHANNEL_4:
        WRITE_REG(p_tim->CCR4, value);
        break;
    default:
        return ERR_INVALID_PARAM;
    }
    return ERR_NONE;
}

err_t TIM_set_output_compare_polarity(TIM_TypeDef *p_tim,
                                      enum TIM_channel_e channel,
                                      enum TIM_OC_Polarity_e polarity) {
    uint32_t CCxP;
    switch (channel) {
    case TIM_CHANNEL_1:
        CCxP = TIM_CCER_CC1P;
        break;
    case TIM_CHANNEL_2:
        CCxP = TIM_CCER_CC2P;
        break;
    case TIM_CHANNEL_3:
        CCxP = TIM_CCER_CC3P;
        break;
    case TIM_CHANNEL_4:
        CCxP = TIM_CCER_CC4P;
        break;
    default:
        return ERR_INVALID_PARAM;
    }

    switch (polarity) {
    case TIM_OC_POL_ACTIVE_HIGH:
        CLEAR_BIT(p_tim->CCER, CCxP);
    case TIM_OC_POL_ACTIVE_LOW:
        SET_BIT(p_tim->CCER, CCxP);
    default:
        return ERR_INVALID_PARAM;
    }

    return ERR_NONE;
}

err_t TIM_set_OCxRef_ETRF_dependency(TIM_TypeDef *p_tim,
                                     enum TIM_channel_e channel,
                                     enum TIM_OCxRef_ETRF_Dep_e dependency) {
    uint32_t OCxCE;
    volatile uint32_t *CCMRx;
    switch (channel) {
    case TIM_CHANNEL_1:
        CCMRx = &(p_tim->CCMR1);
        OCxCE = TIM_CCMR1_OC1CE;
        break;
    case TIM_CHANNEL_2:
        CCMRx = &(p_tim->CCMR1);
        OCxCE = TIM_CCMR1_OC2CE;
        break;
    case TIM_CHANNEL_3:
        CCMRx = &(p_tim->CCMR2);
        OCxCE = TIM_CCMR2_OC3CE;
        break;
    case TIM_CHANNEL_4:
        CCMRx = &(p_tim->CCMR2);
        OCxCE = TIM_CCMR2_OC4CE;
        break;
    default:
        return ERR_INVALID_PARAM;
    }

    switch (dependency) {
    case TIM_OCxREF_ETRF_DEPENDENT:
        CLEAR_BIT(*CCMRx, OCxCE);
    case TIM_OCxREF_ETRF_INDEPENDENT:
        SET_BIT(*CCMRx, OCxCE);
    default:
        return ERR_INVALID_PARAM;
    }

    return ERR_NONE;
}

err_t TIM_set_OCx_mode(TIM_TypeDef *p_tim, enum TIM_channel_e channel,
                       enum TIM_OC_Mode_e mode) {
    uint32_t OCxM, OCxM_offset;
    volatile uint32_t *CCMRx;
    switch (channel) {
    case TIM_CHANNEL_1:
        CCMRx = &(p_tim->CCMR1);
        OCxM = TIM_CCMR1_OC1M;
        OCxM_offset = TIM_CCMR1_OC1M_Pos;
        break;
    case TIM_CHANNEL_2:
        CCMRx = &(p_tim->CCMR1);
        OCxM = TIM_CCMR1_OC2M;
        OCxM_offset = TIM_CCMR1_OC2M_Pos;
        break;
    case TIM_CHANNEL_3:
        CCMRx = &(p_tim->CCMR2);
        OCxM = TIM_CCMR2_OC3M;
        OCxM_offset = TIM_CCMR2_OC3M_Pos;
        break;
    case TIM_CHANNEL_4:
        CCMRx = &(p_tim->CCMR2);
        OCxM = TIM_CCMR2_OC4M;
        OCxM_offset = TIM_CCMR2_OC4M_Pos;
        break;
    default:
        return ERR_INVALID_PARAM;
    }

    CLEAR_BIT(*CCMRx, OCxM);
    SET_BIT(*CCMRx, mode << OCxM_offset);

    return ERR_NONE;
}

err_t TIM_enable_OCx_preload(TIM_TypeDef *p_tim, enum TIM_channel_e channel) {
    switch (channel) {
    case TIM_CHANNEL_1:
        SET_BIT(p_tim->CCMR1, TIM_CCMR1_OC1PE);
        break;
    case TIM_CHANNEL_2:
        SET_BIT(p_tim->CCMR1, TIM_CCMR1_OC2PE);
        break;
    case TIM_CHANNEL_3:
        SET_BIT(p_tim->CCMR2, TIM_CCMR2_OC3PE);
        break;
    case TIM_CHANNEL_4:
        SET_BIT(p_tim->CCMR2, TIM_CCMR2_OC4PE);
        break;
    default:
        return ERR_INVALID_PARAM;
    }

    return ERR_NONE;
}

err_t TIM_disable_OCx_preload(TIM_TypeDef *p_tim, enum TIM_channel_e channel) {
    switch (channel) {
    case TIM_CHANNEL_1:
        CLEAR_BIT(p_tim->CCMR1, TIM_CCMR1_OC1PE);
        break;
    case TIM_CHANNEL_2:
        CLEAR_BIT(p_tim->CCMR1, TIM_CCMR1_OC2PE);
        break;
    case TIM_CHANNEL_3:
        CLEAR_BIT(p_tim->CCMR2, TIM_CCMR2_OC3PE);
        break;
    case TIM_CHANNEL_4:
        CLEAR_BIT(p_tim->CCMR2, TIM_CCMR2_OC4PE);
        break;
    default:
        return ERR_INVALID_PARAM;
    }

    return ERR_NONE;
}

err_t TIM_enable_OCx_fast_mode(TIM_TypeDef *p_tim, enum TIM_channel_e channel) {
    switch (channel) {
    case TIM_CHANNEL_1:
        SET_BIT(p_tim->CCMR1, TIM_CCMR1_OC1FE);
        break;
    case TIM_CHANNEL_2:
        SET_BIT(p_tim->CCMR1, TIM_CCMR1_OC2FE);
        break;
    case TIM_CHANNEL_3:
        SET_BIT(p_tim->CCMR2, TIM_CCMR2_OC3FE);
        break;
    case TIM_CHANNEL_4:
        SET_BIT(p_tim->CCMR2, TIM_CCMR2_OC4FE);
        break;
    default:
        return ERR_INVALID_PARAM;
    }

    return ERR_NONE;
}

err_t TIM_disable_OCx_fast_mode(TIM_TypeDef *p_tim,
                                enum TIM_channel_e channel) {
    switch (channel) {
    case TIM_CHANNEL_1:
        CLEAR_BIT(p_tim->CCMR1, TIM_CCMR1_OC1FE);
        break;
    case TIM_CHANNEL_2:
        CLEAR_BIT(p_tim->CCMR1, TIM_CCMR1_OC2FE);
        break;
    case TIM_CHANNEL_3:
        CLEAR_BIT(p_tim->CCMR2, TIM_CCMR2_OC3FE);
        break;
    case TIM_CHANNEL_4:
        CLEAR_BIT(p_tim->CCMR2, TIM_CCMR2_OC4FE);
        break;
    default:
        return ERR_INVALID_PARAM;
    }

    return ERR_NONE;
}

err_t TIM_set_input_capture_polarity(TIM_TypeDef *p_tim,
                                     enum TIM_channel_e channel,
                                     enum TIM_IC_Polarity_e polarity) {
    uint32_t CCxP, CCxP_offset;
    switch (channel) {
    case TIM_CHANNEL_1:
        CCxP = TIM_CCER_CC1NP_Msk | TIM_CCER_CC1P_Msk;
        CCxP_offset = TIM_CCER_CC1P_Pos;
        break;
    case TIM_CHANNEL_2:
        CCxP = TIM_CCER_CC2NP_Msk | TIM_CCER_CC2P_Msk;
        CCxP_offset = TIM_CCER_CC2P_Pos;
        break;
    case TIM_CHANNEL_3:
        CCxP = TIM_CCER_CC3NP_Msk | TIM_CCER_CC3P_Msk;
        CCxP_offset = TIM_CCER_CC3P_Pos;
        break;
    case TIM_CHANNEL_4:
        CCxP = TIM_CCER_CC4NP_Msk | TIM_CCER_CC4P_Msk;
        CCxP_offset = TIM_CCER_CC4P_Pos;
        break;
    default:
        return ERR_INVALID_PARAM;
    }

    CLEAR_BIT(p_tim->CCER, CCxP);
    SET_BIT(p_tim->CCER, polarity << CCxP_offset);

    return ERR_NONE;
}

err_t TIM_enable_OCx(TIM_TypeDef *p_tim, enum TIM_channel_e channel) {
    switch (channel) {
    case TIM_CHANNEL_1:
        CLEAR_BIT(p_tim->CCMR1, TIM_CCMR1_CC1S);
        SET_BIT(p_tim->CCER, TIM_CCER_CC1E);
        break;
    case TIM_CHANNEL_2:
        CLEAR_BIT(p_tim->CCMR1, TIM_CCMR1_CC2S);
        SET_BIT(p_tim->CCER, TIM_CCER_CC2E);
        break;
    case TIM_CHANNEL_3:
        CLEAR_BIT(p_tim->CCMR2, TIM_CCMR2_CC3S);
        SET_BIT(p_tim->CCER, TIM_CCER_CC3E);
        break;
    case TIM_CHANNEL_4:
        CLEAR_BIT(p_tim->CCMR2, TIM_CCMR2_CC4S);
        SET_BIT(p_tim->CCER, TIM_CCER_CC4E);
        break;
    default:
        return ERR_INVALID_PARAM;
    }
    return ERR_NONE;
}

err_t TIM_disable_OCx(TIM_TypeDef *p_tim, enum TIM_channel_e channel) {
    switch (channel) {
    case TIM_CHANNEL_1:
        CLEAR_BIT(p_tim->CCER, TIM_CCER_CC1E);
        break;
    case TIM_CHANNEL_2:
        CLEAR_BIT(p_tim->CCER, TIM_CCER_CC2E);
        break;
    case TIM_CHANNEL_3:
        CLEAR_BIT(p_tim->CCER, TIM_CCER_CC3E);
        break;
    case TIM_CHANNEL_4:
        CLEAR_BIT(p_tim->CCER, TIM_CCER_CC4E);
        break;
    default:
        return ERR_INVALID_PARAM;
    }
    return ERR_NONE;
}

err_t TIM_enable_ICx(TIM_TypeDef *p_tim, enum TIM_channel_e channel,
                     enum TIM_ICx_mapping_e mapping) {
	// TODO : implement
	return ERR_NONE;

}

err_t TIM_disable_ICx(TIM_TypeDef *p_tim, enum TIM_channel_e channel) {
	// TODO : implement
	return ERR_NONE;
}

err_t TIM_set_ICx_mapping(TIM_TypeDef *p_tim, enum TIM_channel_e channel,
                          enum TIM_ICx_mapping_e mapping) {
    uint32_t CCxP, CCxP_offset;
    switch (channel) {
    case TIM_CHANNEL_1:
        CCxP = TIM_CCER_CC1NP_Msk | TIM_CCER_CC1P_Msk;
        CCxP_offset = TIM_CCER_CC1P_Pos;
        break;
    case TIM_CHANNEL_2:
        CCxP = TIM_CCER_CC2NP_Msk | TIM_CCER_CC2P_Msk;
        CCxP_offset = TIM_CCER_CC2P_Pos;
        break;
    case TIM_CHANNEL_3:
        CCxP = TIM_CCER_CC3NP_Msk | TIM_CCER_CC3P_Msk;
        CCxP_offset = TIM_CCER_CC3P_Pos;
        break;
    case TIM_CHANNEL_4:
        CCxP = TIM_CCER_CC4NP_Msk | TIM_CCER_CC4P_Msk;
        CCxP_offset = TIM_CCER_CC4P_Pos;
        break;
    default:
        return ERR_INVALID_PARAM;
    }

    CLEAR_BIT(p_tim->CCER, CCxP);
    SET_BIT(p_tim->CCER, mapping << CCxP_offset);

    return ERR_NONE;
}

void TIM_set_prescaler(TIM_TypeDef *p_tim, uint32_t prescaler) {
    WRITE_REG(p_tim->PSC, prescaler);
}

void TIM_set_autoreload(TIM_TypeDef *p_tim, uint32_t autoreload) {
    WRITE_REG(p_tim->ARR, autoreload);
}

void TIM_set_counter(TIM_TypeDef *p_tim, uint32_t counter) {
    WRITE_REG(p_tim->CNT, counter);
}