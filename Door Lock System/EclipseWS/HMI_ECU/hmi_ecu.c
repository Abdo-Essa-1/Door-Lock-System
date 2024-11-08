/*
 ============================================================================
 Name        : hmi_ecu.c
 Author      : Abdelrahman Essa
 Date        : 2/11/2024
 Description : Human Interface ECU Handler
 ============================================================================
 */

/************** Includes **************/
#include "std_types.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include "MCAL/UART/uart.h"
#include "MCAL/Timer/timer.h"
#include "HAL/LCD/lcd.h"
#include "HAL/Keypad/keypad.h"

#define PASS_LOAD        0xA0
#define PASS_IN          0xF1
#define PASS_UPDATE      0xE0
#define PASS_CORRECT     0xC0
#define PASS_FAIL        0xF0
#define PEOPLE_IN        0xB0
#define PEOPLE_NO        0xD0
#define ALARM_ON         0xF2

/* Array to Store Password */
uint8 pass[10] = {0};
uint8 i = 0;
uint8 pass_state = 0;
uint8 key = 0;
uint8 counter = 0;
uint8 enter_fails = 0;
uint8 update_fails = 0;
uint8 people_status = 0;

void Timer1_handler(void)
{
	++counter;
}

int main()
{
	/********** Initializations **********/
	/* LCD Initialization */
	LCD_init();

	/* UART Initialization */
	UART_ConfigType uart_cfg = {UART_8BIT_DATA, UART_Parity_OFF, UART_STOPBIT_1, 9600};
	UART_init(&uart_cfg);

	/* Creating timer 1 object to count time */
	sei();
	Timer_ConfigType time1 = {0, 31250, TIMER1_ID, TIMER_F_CPU_256, TIMER_CTC};
	Timer_init(&time1);
	Timer_setCallBack(Timer1_handler, TIMER1_ID);

	/* Enter Password for the first Time */
	while(pass_state != PASS_CORRECT)
	{
		UART_sendByte(PASS_LOAD);
		LCD_clearScreen();
		LCD_displayString("Plz Enter Pass:");
		LCD_moveCursor(1, 0);
		for(i = 0; i < 5; ++i)
		{
			pass[i] = KEYPAD_getPressedKey();
			LCD_displayCharacter('*');
			_delay_ms(500);
		}
		while(KEYPAD_getPressedKey() != '=');
		_delay_ms(500);
		LCD_clearScreen();
		LCD_displayString("Plz re-enter the");
		LCD_displayStringRowColumn(1, 0, "same pass: ");
		for(i = 5; i < 10; ++i)
		{
			pass[i] = KEYPAD_getPressedKey();
			LCD_displayCharacter('*');
			_delay_ms(500);
		}
		while(KEYPAD_getPressedKey() != '=');
		_delay_ms(500);

		/* Sending Password to Control ECU Using UART */
		for(i = 0; i < 10; ++i)
		{
			UART_sendByte(pass[i]);
		}

		/* Checking pass */
		pass_state = UART_receiveByte();
		if(pass_state == PASS_FAIL)
		{
			/* the program will return to entering password again */
			LCD_clearScreen();
			LCD_displayString("PASS WRONG");
			counter = 0;
			while(counter < 3);
		}
	}

	/************** Program **************/
	for(;;)
	{
		/* Entering main window */
		LCD_clearScreen();
		LCD_displayString("+ : OPEN DOOR");
		LCD_displayStringRowColumn(1, 0, "- : CHANGE PASS");

		/* Waiting for user order */
		do{
			key = KEYPAD_getPressedKey();
		}while(key != '+' && key != '-');

		/* Checking order type */
		if(key == '+')
		{
			/* Waiting for user to enter old password */
			UART_sendByte(PASS_IN);
			LCD_clearScreen();
			LCD_displayString("Plz enter old");
			LCD_displayStringRowColumn(1, 0, "pass: ");
			for(i = 0; i < 5; ++i)
			{
				pass[i] = KEYPAD_getPressedKey();
				LCD_displayCharacter('*');
				_delay_ms(500);
			}
			while(KEYPAD_getPressedKey() != '=');
			_delay_ms(500);

			/* Sending Password to Control ECU Using UART */
			for(i = 0; i < 5; ++i)
			{
				UART_sendByte(pass[i]);
			}

			/* Checking pass */
			pass_state = UART_receiveByte();
			if(pass_state == PASS_CORRECT)
			{
				enter_fails = 0;
				/* Open door for 15 seconds */
				LCD_clearScreen();
				LCD_displayStringRowColumn(0, 1, "Door Unlocking");
				LCD_displayStringRowColumn(1, 3, "Please Wait");
				counter = 0;
				while(counter < 15);

				/* Check people entering */
				LCD_clearScreen();
				people_status = UART_receiveByte();
				while(people_status == PEOPLE_IN)
				{
					LCD_displayStringRowColumn(0, 0, "Wait for People");
					LCD_displayStringRowColumn(1, 3, "to Enter");
					people_status = UART_receiveByte();
				}
				if(people_status == PEOPLE_NO)
				{
					LCD_clearScreen();
					LCD_displayStringRowColumn(0, 2, "Door Locking");
					counter = 0;
					while(counter < 15);
				}
			}
			else if(pass_state == PASS_FAIL)
			{
				++enter_fails;
				if(enter_fails == 3)
				{
					/* Lock system for 1 minute */
					UART_sendByte(ALARM_ON);
					LCD_clearScreen();
					LCD_displayStringRowColumn(0, 1, "System LOCKED");
					LCD_displayStringRowColumn(1, 0, "Wait for 1 min");
					counter = 0;
					while(counter < 60);
					enter_fails = 0;
				}
				else
				{
					/* the program will return to entering password again */
					LCD_clearScreen();
					LCD_displayString("PASS WRONG");
					counter = 0;
					while(counter < 3);
				}
			}
		}
		else if(key == '-')
		{
			/* Waiting for user to enter old password */
			UART_sendByte(PASS_UPDATE);
			LCD_clearScreen();
			LCD_displayString("Plz enter old");
			LCD_displayStringRowColumn(1, 0, "pass: ");
			for(i = 0; i < 5; ++i)
			{
				pass[i] = KEYPAD_getPressedKey();
				LCD_displayCharacter('*');
				_delay_ms(500);
			}
			while(KEYPAD_getPressedKey() != '=');
			_delay_ms(500);

			/* Sending Password to Control ECU Using UART */
			for(i = 0; i < 5; ++i)
			{
				UART_sendByte(pass[i]);
			}

			/* Checking pass */
			pass_state = UART_receiveByte();
			if(pass_state == PASS_CORRECT)
			{
				update_fails = 0;
				LCD_clearScreen();
				LCD_displayString("Plz Enter Pass:");
				LCD_moveCursor(1, 0);
				for(i = 0; i < 5; ++i)
				{
					pass[i] = KEYPAD_getPressedKey();
					LCD_displayCharacter('*');
					_delay_ms(500);
				}
				while(KEYPAD_getPressedKey() != '=');
				_delay_ms(500);
				LCD_clearScreen();
				LCD_displayString("Plz re-enter the");
				LCD_displayStringRowColumn(1, 0, "same pass: ");
				for(i = 5; i < 10; ++i)
				{
					pass[i] = KEYPAD_getPressedKey();
					LCD_displayCharacter('*');
					_delay_ms(500);
				}
				while(KEYPAD_getPressedKey() != '=');
				_delay_ms(500);

				/* Sending Password to Control ECU Using UART */
				for(i = 0; i < 10; ++i)
				{
					UART_sendByte(pass[i]);
				}

				/* Checking pass */
				pass_state = UART_receiveByte();
				if(pass_state == PASS_FAIL)
				{
					/* the program will return to entering password again */
					LCD_clearScreen();
					LCD_displayString("PASS WRONG");
					counter = 0;
					while(counter < 3);
				}
			}
			else if(pass_state == PASS_FAIL)
			{
				++update_fails;
				if(update_fails == 3)
				{
					/* Lock system for 1 minute */
					LCD_clearScreen();
					LCD_displayStringRowColumn(0, 1, "System LOCKED");
					LCD_displayStringRowColumn(1, 0, "Wait for 1 min");
					counter = 0;
					while(counter < 60);
					update_fails = 0;
				}
				else
				{
					/* the program will return to entering password again */
					LCD_clearScreen();
					LCD_displayString("PASS WRONG");
					counter = 0;
					while(counter < 3);
				}
			}
		}
	}
}
