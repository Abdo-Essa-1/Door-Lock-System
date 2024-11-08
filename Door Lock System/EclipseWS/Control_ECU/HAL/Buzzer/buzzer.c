/*
 * buzzer.c
 *
 *  Created on: Oct 8, 2024
 *      Author: Essa
 */

#include "buzzer.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../std_types.h"

/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/

/**
 * @brief  Function to Initialize the Buzzer and turn it initially off.
 * @param  void.
 * @return void.
 */
void Buzzer_init(void)
{
	GPIO_setupPinDirection(BUZZER_PORTID, BUZZER_PINID, PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORTID, BUZZER_PINID, LOGIC_LOW);
}

/**
 * @brief  Function to Turn Buzzer ON.
 * @param  void.
 * @return void.
 */
void Buzzer_ON(void)
{
	GPIO_writePin(BUZZER_PORTID, BUZZER_PINID, LOGIC_HIGH);
}

/**
 * @brief  Function to Turn Buzzer OFF.
 * @param  void.
 * @return void.
 */
void Buzzer_OFF(void)
{
	GPIO_writePin(BUZZER_PORTID, BUZZER_PINID, LOGIC_LOW);
}

/**
 * @brief  Function to Toggle buzzer.
 * @param  void.
 * @return void.
 */
void Buzzer_TOGGLE(void)
{
	GPIO_writePin(BUZZER_PORTID, BUZZER_PINID, LOGIC_TOGGLE);
}
