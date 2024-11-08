/*
 * buzzer.h
 *
 *  Created on: Oct 8, 2024
 *      Author: Essa
 */

#ifndef BUZZER_H_
#define BUZZER_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define BUZZER_PORTID             PORTC_ID
#define BUZZER_PINID              PIN7_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/**
 * @brief  Function to Initialize the Buzzer and turn it initially off.
 * @param  void.
 * @return void.
 */
void Buzzer_init(void);

/**
 * @brief  Function to Turn Buzzer ON.
 * @param  void.
 * @return void.
 */
void Buzzer_ON(void);

/**
 * @brief  Function to Turn Buzzer OFF.
 * @param  void.
 * @return void.
 */
void Buzzer_OFF(void);

/**
 * @brief  Function to Toggle buzzer.
 * @param  void.
 * @return void.
 */
void Buzzer_TOGGLE(void);

#endif /* BUZZER_H_ */
