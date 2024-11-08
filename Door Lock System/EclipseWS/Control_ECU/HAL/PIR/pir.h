/*
 * pir.h
 *
 *  Created on: Nov 2, 2024
 *      Author: Essa
 */

#ifndef HAL_PIR_PIR_H_
#define HAL_PIR_PIR_H_

#include "../../std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define PIR_PORTID             PORTC_ID
#define PIR_PINID              PIN2_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/**
 * @brief  Function to Initialize the PIR Sensor.
 * @param  void.
 * @return void.
 */
void PIR_init(void);

/**
 * @brief  Function to get the PIR Sensor State.
 * @param  void.
 * @return Sensor State.
 */
uint8 PIR_getState(void);

#endif /* HAL_PIR_PIR_H_ */
