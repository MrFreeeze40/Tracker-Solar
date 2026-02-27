#ifndef __TIM_H__
#define __TIM_H__

#include "common.h"
#include <stdbool.h>
#include "stm32f446xx.h"

/**
 * @brief Timer modes
 * 
 */
enum TIM_mode_e {
	TIM_NORMAL_MODE,
	TIM_INPUT_CAPTURE_MODE,
	TIM_OUTPUT_COMPARE_MODE
};

enum TIM_channel_e {
	TIM_CHANNEL_1,
	TIM_CHANNEL_2,
	TIM_CHANNEL_3,
	TIM_CHANNEL_4
};

/**
 * @brief Set the timer working mode
 * 
 * @param p_tim Pointer to the TIM peripheral instance.
 *              Valid values: TIM1, TIM2, TIM3, ..., TIMx depending on device.
 * @param mode one member of the @ref TIM_mode_e
  *         @arg @ref TIM_NORMAL_MODE
  *         @arg @ref TIM_INPUT_CAPTURE_MODE
  *         @arg @ref TIM_OUTPUT_COMPARE_MODE
 */
err_t TIM_set_mode(TIM_TypeDef *p_tim, enum TIM_mode_e mode);

/**
 * @brief set the ARR as buffered and updated on update event
 * 
 * @note If this configuration is changed during the timer is started, the effect 
 *
 * @param p_tim Pointer to the TIM peripheral instance.
 *              Valid values: TIM1, TIM2, TIM3, ..., TIMx depending on device.
 */
void TIM_enable_auto_reload_buffering(TIM_TypeDef *p_tim);

/**
 * @brief set the ARR as not buffered 
 * 
 * @param p_tim Pointer to the TIM peripheral instance.
 *              Valid values: TIM1, TIM2, TIM3, ..., TIMx depending on device.
 */
void TIM_disable_auto_reload_buffering(TIM_TypeDef *p_tim);

/**
 * @brief Timer counting direction
 * 
 */
enum TIM_count_direction_e {
	UPCOUNTING,
	DOWNCOUNTING
};

/**
 * @brief set the counting direction of the timer
 * 
 * @param p_tim Pointer to the TIM peripheral instance.
 *              Valid values: TIM1, TIM2, TIM3, ..., TIMx depending on device.
 * @param direction direction of counting
 */
err_t TIM_set_direction(TIM_TypeDef *p_tim, enum TIM_count_direction_e direction);

/**
 * @brief Set the one pulse mode for the timer
 * 
 * @param p_tim Pointer to the TIM peripheral instance.
 *              Valid values: TIM1, TIM2, TIM3, ..., TIMx depending on device.
 */
void TIM_set_one_pulse_mode(TIM_TypeDef *p_tim);

/**
 * @brief Set the timer as operating continuisly
 * 
 * @param p_tim Pointer to the TIM peripheral instance.
 *              Valid values: TIM1, TIM2, TIM3, ..., TIMx depending on device.
 */
void TIM_unset_one_pulse_mode(TIM_TypeDef *p_tim);

/**
 * @brief Settings for the update request source
 * 
 */
enum TIM_update_request_source_e {
	TIM_UPDATE_REQUEST_SOURCE_ALL = 0b0,
	TIM_UPDATE_REQUEST_SOURCE_ONLY_OVERFLOW = 0b1
};

/**
 * @brief Sets the update request source for a timer.
 *
 * @param p_tim Pointer to the TIM peripheral instance.
 *              Valid values: TIM1, TIM2, TIM3, ..., TIMx depending on device.
 * @param source The update request source to set. Should be a value from
 *               the update_request_source_e enumeration.
 *
 * @return err_t Error code indicating the success or failure of the operation.
 */
err_t TIM_SetUpdateRequestSource(TIM_TypeDef *p_tim, enum TIM_update_request_source_e source);

/**
 * @brief Gets the current update request source setting for a timer.
 * 
 * @param p_tim Pointer to the TIM peripheral instance.
 *              Valid values: TIM1, TIM2, TIM3, ..., TIMx depending on device.
 * @return enum update_request_source_e source selected
 */
enum TIM_update_request_source_e TIM_GetUpdateRequestSource(TIM_TypeDef *p_tim);

/**
 * @brief Enable update event generation for a timer.
 * 
 * @param p_tim Pointer to the TIM peripheral instance.
 *              Valid values: TIM1, TIM2, TIM3, ..., TIMx depending on device.
 */
void TIM_enable_update_event(TIM_TypeDef *p_tim);

/**
 * @brief Disable update event generation for a timer.
 * 
 * @param p_tim Pointer to the TIM peripheral instance.
 *              Valid values: TIM1, TIM2, TIM3, ..., TIMx depending on device.
 */
void TIM_disable_update_event(TIM_TypeDef *p_tim);

/**
 * @brief Enable update interrupt for a timer.
 * 
 * @param p_tim Pointer to the TIM peripheral instance.
 *              Valid values: TIM1, TIM2, TIM3, ..., TIMx depending on device.
 */
void TIM_enable_update_interrupt(TIM_TypeDef *p_tim);

/**
 * @brief Disable update interrupt for a timer.
 * 
 * @param p_tim Pointer to the TIM peripheral instance.
 *              Valid values: TIM1, TIM2, TIM3, ..., TIMx depending on device.
 */
void TIM_disable_update_interrupt(TIM_TypeDef *p_tim);

/**
 * @brief Enable capture/compare interrupt for a specific channel of a timer.
 * 
 * @param p_tim Pointer to the TIM peripheral instance.
 *              Valid values: TIM1, TIM2, TIM3, ..., TIMx depending on device.
 * @param channel The channel number (e.g., TIM_CHANNEL_1, TIM_CHANNEL_2, etc.)
 */
err_t TIM_enable_CCx_interrupt(TIM_TypeDef *p_tim, enum TIM_channel_e channel);

/**
 * @brief Disable capture/compare interrupt for a specific channel of a timer.
 * 
 * @param p_tim Pointer to the TIM peripheral instance.
 *              Valid values: TIM1, TIM2, TIM3, ..., TIMx depending on device.
 * @param channel The channel number (e.g., TIM_CHANNEL_1, TIM_CHANNEL_2, etc.)
 */
err_t TIM_disable_CCx_interrupt(TIM_TypeDef *p_tim, enum TIM_channel_e channel);

// Status checking and update
/**
 * @brief Checks if a timer update interrupt is pending.
 * 
 * @param p_tim Pointer to the TIM peripheral instance to check.
 *              Valid values: TIM1, TIM2, TIM3, ..., TIMx depending on device.
 * 
 * @note This function queries the update interrupt flag (UIF) of the specified timer.
 *       Use this to determine if an update event has occurred since the flag was last cleared.
 * 
 * @see TIM_clear_update_interrupt_flag()
 */
bool TIM_is_update_interrupt_pending(TIM_TypeDef *p_tim);

/**
 * @brief Clears the update interrupt flag for a timer.
 * 
 * @param p_tim 
 */
void TIM_clear_update_interrupt_flag(TIM_TypeDef *p_tim);

/**
 * @brief Checks if a capture/compare interrupt is pending for a specific channel of a timer.
 * 
 * @param p_tim Pointer to the TIM peripheral instance.
 *              Valid values: TIM1, TIM2, TIM3, ..., TIMx depending on device.
 * @param channel The channel number (e.g., TIM_CHANNEL_1, TIM_CHANNEL_2, etc.)
 * @return true if the interrupt is pending, false otherwise.
 */
bool TIM_is_CCx_interrupt_pending(TIM_TypeDef *p_tim, enum TIM_channel_e channel);

/**
 * @brief 
 * 
 * @param p_tim 
 * @param channel 
 * @return err_t 
 */
err_t TIM_clear_CCx_interrupt_flag(TIM_TypeDef *p_tim, enum TIM_channel_e channel);

void TIM_generate_CCx_event(TIM_TypeDef *p_tim, enum TIM_channel_e channel);
void TIM_generate_update_event(TIM_TypeDef *p_tim);

/**
 * @brief Checks if the timer counter is currently active (counting).
 * 
 * @param p_tim Pointer to the TIM peripheral instance to check.
 *              Valid values: TIM1, TIM2, TIM3, ..., TIMx depending on device.
 * 
 * @return true if the timer is active (counting), false otherwise.
 */
bool TIM_is_started(TIM_TypeDef *p_tim);

/**
 * @brief Start timer counter
 * 
 * @param p_tim Pointer to the TIM peripheral instance to start.
 *              Valid values: TIM1, TIM2, TIM3, ..., TIMx depending on device.
 */
 void TIM_start(TIM_TypeDef *p_tim);
 
 /**
 * @brief Stop timer counter
 * 
 * @param p_tim Pointer to the TIM peripheral instance to stop.
 *              Valid values: TIM1, TIM2, TIM3, ..., TIMx depending on device.
 */
void TIM_stop(TIM_TypeDef *p_tim);

/**
 * @brief Set compared value of the output compare of the channel x
 * 
 * @param channel channel to set
 */
void TIM_set_OCx_compared_value(uint8_t channel);

void TIM_set_output_compare_polarity(TIM_TypeDef *p_tim);
void TIM_set_OCxRef_ETRF_dependency(TIM_TypeDef *p_tim);
void TIM_set_OCx_mode(TIM_TypeDef *p_tim);

void TIM_enable_OCx_preload(TIM_TypeDef *p_tim);
void TIM_disable_OCx_preload(TIM_TypeDef *p_tim);


err_t TIM_enable_OCx_fast_mode(TIM_TypeDef *p_tim);
err_t TIM_disable_OCx_fast_mode(TIM_TypeDef *p_tim);

void TIM_set_input_capture_polarity(TIM_TypeDef *p_tim);

enum TIM_ICx_mapping_e {
	TIM_ICx_MAPPED_ON_TI1,
	TIM_ICx_MAPPED_ON_TI2,
	TIM_ICx_MAPPED_ON_TRC,
};

err_t TIM_set_ICx_mapping(TIM_TypeDef *p_tim);

uint32_t TIM_get_ICx_value(TIM_TypeDef *p_tim);

void TIM_set_prescaler(TIM_TypeDef *p_tim, uint32_t prescaler);

/**
 * @brief Sets the autoreload value for a timer.
 * 
 * @param p_tim Pointer to the TIM_TypeDef structure that contains
 *              the configuration information for the specified timer.
 * @param autoreload The autoreload value to set.
 */
void TIM_set_autoreload(TIM_TypeDef *p_tim, uint32_t autoreload);

/**
 * @brief Set the timer counter to a specific value
 * 
 * @param p_tim pointer to the timer registers struct
 * @param counter value to set the counter to
 */
void TIM_set_counter(TIM_TypeDef *p_tim, uint32_t counter);

#endif // __TIM_H__