/*
 * motor.c
 *
 *  Created on: Nov 2, 2024
 *      Author: Abdelrahman Essa
 */

#include "motor.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../MCAL/PWM0/pwm0.h"

/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/

/**
 * @brief  Function to:
 *         1. Setup the direction for the two motor pins through the GPIO driver.
 *         2. Stop at the DC-Motor at the beginning through the GPIO driver.
 * @param  void.
 * @return void.
 */
void DcMotor_Init(void)
{
	/* Set Motor direction control pins as output */
	GPIO_setupPinDirection(MOTOR_PORT_ID, MOTOR_IN1_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_PORT_ID, MOTOR_IN2_PIN_ID, PIN_OUTPUT);

	/* Motor off initially */
	GPIO_writePin(MOTOR_PORT_ID, MOTOR_IN1_PIN_ID,LOGIC_LOW);
	GPIO_writePin(MOTOR_PORT_ID, MOTOR_IN2_PIN_ID, LOGIC_LOW);
}


/**
 * @brief  Function to rotate the DC Motor CW or ACW or stop
 *         the motor based on the state input state value. Send
 *         the required duty cycle to the PWM driver based on the
 *         required speed value.
 * @param  Motor State, Speed.
 * @return void.
 */
void DcMotor_Rotate(DcMotor_State state, uint8 speed)
{
	/* Update state of the motor */
	if(state == MOTOR_STOP)
	{
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_IN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_IN2_PIN_ID, LOGIC_LOW);
	}
	else if(state == MOTOR_CW)
	{
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_IN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_IN2_PIN_ID, LOGIC_HIGH);
	}
	else if(state == MOTOR_ACW)
	{
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_IN1_PIN_ID, LOGIC_HIGH);
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_IN2_PIN_ID, LOGIC_LOW);
	}
	else
	{
		/* Do Nothing */
	}

	/* Update Speed */
	PWM_Timer0_Init(speed);
}
