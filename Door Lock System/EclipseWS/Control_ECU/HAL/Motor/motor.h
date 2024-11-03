/*
 * motor.h
 *
 *  Created on: Nov 2, 2024
 *      Author: Abdelrahman Essa
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "../../std_types.h"

/*******************************************************************************
 *                            Types Declaration                                *
 *******************************************************************************/

/* Enumeration for Motor Move Type */
typedef enum {
	MOTOR_STOP, MOTOR_CW, MOTOR_ACW
}DcMotor_State;

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define MOTOR_PORT_ID       PORTD_ID
#define MOTOR_IN1_PIN_ID    PIN6_ID
#define MOTOR_IN2_PIN_ID    PIN7_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/**
 * @brief  Function to:
 *         1. Setup the direction for the two motor pins through the GPIO driver.
 *         2. Stop at the DC-Motor at the beginning through the GPIO driver.
 * @param  void.
 * @return void.
 */
void DcMotor_Init(void);


/**
 * @brief  Function to rotate the DC Motor CW or ACW or stop
 *         the motor based on the state input state value. Send
 *         the required duty cycle to the PWM driver based on the
 *         required speed value.
 * @param  Motor State, Speed.
 * @return void.
 */
void DcMotor_Rotate(DcMotor_State, uint8 speed);

#endif /* MOTOR_H_ */
