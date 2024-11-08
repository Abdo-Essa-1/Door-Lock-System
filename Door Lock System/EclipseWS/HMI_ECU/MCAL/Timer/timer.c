/******************************************************************************
 *
 * Module: Timer
 *
 * File Name: timer.c
 *
 * Description: Source file for the AVR Timers driver
 *
 * Author: Abdelrahman Essa
 *
 *******************************************************************************/

#include "timer.h"
#include <avr/io.h> /* To use the Timer Registers */
#include <avr/interrupt.h> /* For Timer ISR */
#include "../../common_macros.h" /* To use the macros */

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static void (*g_callBackPtr_Timer0)(void) = NULL_PTR;
static void (*g_callBackPtr_Timer1)(void) = NULL_PTR;
static void (*g_callBackPtr_Timer2)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

/* ISR For Timer0 in Normal Mode */
ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtr_Timer0 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr_Timer0)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/* ISR For Timer0 in CTC Mode */
ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtr_Timer0 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr_Timer0)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/* ISR For Timer1 in Normal Mode */
ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr_Timer1 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr_Timer1)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/* ISR For Timer1 in CTC Mode */
ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr_Timer1 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr_Timer1)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/* ISR For Timer2 in Normal Mode */
ISR(TIMER2_OVF_vect)
{
	if(g_callBackPtr_Timer2 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr_Timer2)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/* ISR For Timer2 in CTC Mode */
ISR(TIMER2_COMP_vect)
{
	if(g_callBackPtr_Timer2 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr_Timer2)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/**
 * @brief  Function To Initialize the Timer by the Given Settings.
 * @param  Constant pointer to the Settings Data.
 * @return void.
 */
void Timer_init(const Timer_ConfigType *Config_Ptr)
{
	switch(Config_Ptr->timer_ID)
	{
	case TIMER0_ID:

		/* FOC0 = 1 for non-PWM Modes */
		TCCR0 = (1 << FOC0);

		/* Load the initial value to Timer0 counter */
		TCNT0 = (uint8)Config_Ptr->timer_InitialValue;

		if (Config_Ptr->timer_mode == TIMER_NORMAL)
		{
			/* Enable Timer0 Overflow Interrupt */
			TIMSK |= (1 << TOIE0);
		}
		else if(Config_Ptr->timer_mode == TIMER_CTC)
		{
			/* Setting Timer0 to CTC */
			TCCR0 |= (1 << WGM01);

			/* Enable Timer0 Compare Interrupt */
			TIMSK |= (1 << OCIE0);

			/* Storing the Compare Match Value */
			OCR0 = (uint8)Config_Ptr->timer_compare_MatchValue;
		}
		else
		{
			/* Do nothing */
		}

		/* Start Timer0 */
		TCCR0 |= (Config_Ptr->timer_clock);

		break;
	case TIMER1_ID:

		/* FOC1A = 1, FOC1B = 1 for non-PWM Modes */
		TCCR1A = (1 << FOC1A) | (1 << FOC1B);
		TCCR1B = 0;

		/* Load the initial value to Timer1 counter */
		TCNT1 = Config_Ptr->timer_InitialValue;

		if (Config_Ptr->timer_mode == TIMER_NORMAL)
		{
			/* Enable Timer1 Overflow Interrupt */
			TIMSK |= (1 << TOIE1);
		}
		else if(Config_Ptr->timer_mode == TIMER_CTC)
		{
			/* Setting CTC Mode */
			TCCR1B = (1 << WGM12);

			/* Enable Timer1 Compare Interrupt */
			TIMSK |= (1 << OCIE1A);

			/* Storing the Compare Match Value */
			OCR1A = Config_Ptr->timer_compare_MatchValue;
		}
		else
		{
			/* Do nothing */
		}

		/* Start Timer1 */
		TCCR1B |= (Config_Ptr->timer_clock);

		break;
	case TIMER2_ID:

		/* FOC2 = 1 for non-PWM Modes */
		TCCR2 = (1 << FOC2);

		/* Load the initial value to Timer2 counter */
		TCNT2 = (uint8)Config_Ptr->timer_InitialValue;

		if (Config_Ptr->timer_mode == TIMER_NORMAL)
		{
			/* Enable Timer2 Overflow Interrupt */
			TIMSK |= (1 << TOIE2);
		}
		else if(Config_Ptr->timer_mode == TIMER_CTC)
		{
			/* Setting Timer2 to CTC */
			TCCR2 |= (1 << WGM21);

			/* Enable Timer2 Compare Interrupt */
			TIMSK |= (1 << OCIE2);

			/* Storing the Compare Match Value */
			OCR2 = (uint8)Config_Ptr->timer_compare_MatchValue;
		}
		else
		{
			/* Do nothing */
		}

		/* Start Timer2 */
		TCCR2 |= (Config_Ptr->timer_clock);

		break;
	}
}

/**
 * @brief  Function to disable the Timer via Timer_ID.
 * @param  Timer ID.
 * @return void.
 */
void Timer_deInit(Timer_ID_Type timer_type)
{
	/* Clear all registers contents and Disable Interrupts */
	switch(timer_type)
	{
	case TIMER0_ID:
		TCCR0 = 0;
		TCNT0 = 0;
		OCR0 = 0;
		TIMSK &= ~(1 << TOIE0) & ~(1 << OCIE0);
		break;
	case TIMER1_ID:
		TCCR1A = 0;
		TCNT1 = 0;
		OCR1A = 0;
		TIMSK &= ~(1 << TOIE1) & ~(1 << OCIE1A);
		break;
	case TIMER2_ID:
		TCCR2 = 0;
		TCNT2 = 0;
		OCR2 = 0;
		TIMSK &= ~(1 << TOIE2) & ~(1 << OCIE2);
		break;
	}
}


/**
 * @brief  Function to set the Call Back function address to the required Timer.
 * @param  pointer to Call Back function and Timer Id you want to set The Callback to it.
 * @return void.
 */
void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID)
{
	switch(a_timer_ID)
	{
	case TIMER0_ID:
		g_callBackPtr_Timer0 = a_ptr;
		break;
	case TIMER1_ID:
		g_callBackPtr_Timer1 = a_ptr;
		break;
	case TIMER2_ID:
		g_callBackPtr_Timer2 = a_ptr;
		break;
	}
}
