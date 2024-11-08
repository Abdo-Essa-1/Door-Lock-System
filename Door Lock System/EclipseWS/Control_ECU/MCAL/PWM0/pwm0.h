/*
 * pwm0.h
 *
 *  Created on: Nov 2, 2024
 *      Author: Abdelrahman Essa
 */

#ifndef PWM0_H_
#define PWM0_H_

#include "../../std_types.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/**
 * @brief  PWM Timer0 Initialization at the given duty cycle.
 * @param  Duty cycle.
 * @return void.
 * */
void PWM_Timer0_Init(uint8 duty_cycle);

#endif /* PWM0_H_ */
