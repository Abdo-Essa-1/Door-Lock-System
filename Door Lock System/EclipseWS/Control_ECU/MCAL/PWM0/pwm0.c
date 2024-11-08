/*
 * pwm0.c
 *
 *  Created on: Nov 2, 2024
 *      Author: Abdelrahman Essa
 */

#include <avr\io.h>
#include "pwm0.h"

/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/

/**
 * @brief  Generate a PWM signal with frequency 488Hz.
 *         Timer0 will be used with Prescaler F_CPU/64.
 *         F_PWM = (F_CPU) / (256 * N) = (8 * 10^6)/(256 * 64) = 488Hz.
 *         Duty Cycle can be changed by updating the value
 *         in The Compare Register.
 * @param  Duty cycle.
 * @return void.
 */
void PWM_Timer0_Init(uint8 duty_cycle)
{
	/* Set Timer Initial value */
	TCNT0 = 0;

	/* Set Compare Value */
	uint8 duty = (uint8)(((float32) duty_cycle / 100) * 255);
	OCR0 = (uint8)duty;

	/* set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC */
	DDRB |= (1<<PB3);

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/64 CS00=1 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01) | (1<<CS00);
}
