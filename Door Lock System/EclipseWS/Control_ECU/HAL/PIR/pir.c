/*
 * pir.c
 *
 *  Created on: Nov 1, 2024
 *      Author: Essa
 */

#include "pir.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../std_types.h"

/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/

/**
 * @brief  Function to Initialize the PIR Sensor.
 * @param  void.
 * @return void.
 */
void PIR_init(void)
{
	GPIO_setupPinDirection(PIR_PORTID, PIR_PINID, PIN_INPUT);
}

/**
 * @brief  Function to get the PIR Sensor State.
 * @param  void.
 * @return Sensor State.
 */
uint8 PIR_getState(void)
{
	return GPIO_readPin(PIR_PORTID, PIR_PINID);
}
