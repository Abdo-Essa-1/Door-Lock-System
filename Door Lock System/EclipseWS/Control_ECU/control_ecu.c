/*
 ============================================================================
 Name        : control_ecu.c
 Author      : Abdelrahman Essa
 Date        : 2/11/2024
 Description : Control ECU Handler
 ============================================================================
 */

/************** Includes **************/
#include "std_types.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include "MCAL/UART/uart.h"
#include "MCAL/I2C/twi.h"
#include "MCAL/Timer/timer.h"
#include "HAL/Buzzer/buzzer.h"
#include "HAL/EXT_EEPROM/external_eeprom.h"
#include "HAL/Motor/motor.h"
#include "HAL/PIR/pir.h"

#define PASS_LOAD        0xA0
#define PASS_IN          0xF1
#define PASS_UPDATE      0xE0
#define PASS_CORRECT     0xC0
#define PASS_FAIL        0xF0
#define PEOPLE_IN        0xB0
#define PEOPLE_NO        0xD0
#define ALARM_ON         0xF2
#define start_address    0x0005

uint8 counter = 0;
uint8 PROG_status = 0;
boolean status = FALSE;
boolean peopleIN = FALSE;
uint8 pass[10] = {0};
uint8 i = 0;

void Timer1_handler(void)
{
	++counter;
}

int main()
{
	/********** Initializations **********/
	/* UART Initialization */
	UART_ConfigType uart_cfg = {UART_8BIT_DATA, UART_Parity_OFF, UART_STOPBIT_1, 9600};
	UART_init(&uart_cfg);

	/* BUZZER Initialization */
	Buzzer_init();

	/* I2C Initialization */
	TWI_ConfigType i2c_cfg = {0x01, 2, TWI_PRE_1};
	TWI_init(&i2c_cfg);

	/* Motor Initialization */
	DcMotor_Init();

	/* PIR Initialization */
	PIR_init();

	/* Creating timer 1 object to count time */
	sei();
	Timer_ConfigType time1 = {0, 31250, TIMER1_ID, TIMER_F_CPU_256, TIMER_CTC};
	Timer_init(&time1);
	Timer_setCallBack(Timer1_handler, TIMER1_ID);

	/************** Program **************/
	for(;;)
	{
		PROG_status = UART_receiveByte();
		if(PROG_status == PASS_LOAD)
		{
			/* Start Receiving New password */
			for(i = 0; i < 10; ++i)
			{
				pass[i] = UART_receiveByte();
			}

			/* Checking pass */
			for(i = 0; i < 5; ++i)
			{
				if(pass[i] != pass[i + 5])
				{
					/* Sending HMI that pass is not matched */
					UART_sendByte(PASS_FAIL);
					break;
				}
			}
			if(i == 5)
			{
				/* Sending HMI that pass is correct */
				UART_sendByte(PASS_CORRECT);

				/* Storing new pass to the External EEPROM */
				for(i = 0; i < 5; ++i)
				{
					status = EEPROM_writeByte(start_address + i, pass[i]);
					_delay_ms(10);
				}
			}
		}
		else if(PROG_status == PASS_IN)
		{
			/* Receiving password Entered by the user */
			for(i = 0; i < 5; ++i)
			{
				pass[i] = UART_receiveByte();
			}

			/* Getting Old password from the External EEPROM */
			for(i = 5; i < 10; ++i)
			{
				status = EEPROM_readByte(start_address + i - 5, &pass[i]);
				_delay_ms(10);
			}

			/* Checking pass */
			for(i = 0; i < 5; ++i)
			{
				if(pass[i] != pass[i + 5])
				{
					/* Sending HMI that pass is not matched */
					UART_sendByte(PASS_FAIL);
					break;
				}
			}
			if(i == 5)
			{
				/* Sending HMI that pass is correct */
				UART_sendByte(PASS_CORRECT);

				/* Opening Door for 15 seconds */
				DcMotor_Rotate(MOTOR_CW, 100);
				counter = 0;
				while(counter < 15);

				/* Stop the Motor */
				DcMotor_Rotate(MOTOR_STOP, 0);

				/* Checking if people still entering the door */
				do{
					peopleIN = PIR_getState();
					UART_sendByte(PEOPLE_IN);
				}while(peopleIN);

				/* Closing door for 15 seconds */
				UART_sendByte(PEOPLE_NO);
				counter = 0;
				DcMotor_Rotate(MOTOR_ACW, 100);
				while(counter < 15);
				DcMotor_Rotate(MOTOR_STOP, 0);
			}
		}
		else if(PROG_status == PASS_UPDATE)
		{
			/* Receiving password Entered by the user */
			for(i = 0; i < 5; ++i)
			{
				pass[i] = UART_receiveByte();
			}

			/* Getting Old password from the External EEPROM */
			for(i = 5; i < 10; ++i)
			{
				status = EEPROM_readByte(start_address + i - 5, &pass[i]);
				_delay_ms(10);
			}

			/* Checking pass */
			for(i = 0; i < 5; ++i)
			{
				if(pass[i] != pass[i + 5])
				{
					/* Sending HMI that pass is not matched */
					UART_sendByte(PASS_FAIL);
					break;
				}
			}
			if(i == 5)
			{
				/* Sending HMI that pass is correct */
				UART_sendByte(PASS_CORRECT);

				/* Start Receiving New password */
				for(i = 0; i < 10; ++i)
				{
					pass[i] = UART_receiveByte();
				}

				/* Checking pass */
				for(i = 0; i < 5; ++i)
				{
					if(pass[i] != pass[i + 5])
					{
						/* Sending HMI that pass is not matched */
						UART_sendByte(PASS_FAIL);
						break;
					}
				}
				if(i == 5)
				{
					/* Sending HMI that pass is correct */
					UART_sendByte(PASS_CORRECT);

					/* Storing new pass to the External EEPROM */
					for(i = 0; i < 5; ++i)
					{
						status = EEPROM_writeByte(start_address + i, pass[i]);
						_delay_ms(10);
					}
				}
			}
		}
		else if(PROG_status == ALARM_ON)
		{
			/* Turning Alarm ON */
			Buzzer_ON();
			counter = 0;
			while(counter < 60);
			Buzzer_OFF();
		}
	}
}
