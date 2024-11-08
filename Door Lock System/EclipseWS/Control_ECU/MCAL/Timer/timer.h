/******************************************************************************
 *
 * Module: Timer
 *
 * File Name: timer.c
 *
 * Description: Header file for the AVR Timers driver
 *
 * Author: Abdelrahman Essa
 *
 *******************************************************************************/

#ifndef MCAL_TIMER_TIMER_H_
#define MCAL_TIMER_TIMER_H_

#include "../../std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/* Enumeration for Timer ID */
typedef enum{
	TIMER0_ID, TIMER1_ID, TIMER2_ID
}Timer_ID_Type;

/* Enumeration for Timer Clock Select */
typedef enum{
	TIMER_F_CPU = 1, TIMER_F_CPU_8, TIMER_F_CPU_64, TIMER_F_CPU_256, TIMER_F_CPU_1024,
	TIMER_EXT_FALLING, TIMER_EXT_RISING
}Timer_ClockType;

/* Enumeration for Timer Mode */
typedef enum{
	TIMER_NORMAL, TIMER_CTC
}Timer_ModeType;

/* Data Structure for Timer Configurations */
typedef struct{
	uint16          timer_InitialValue;
	uint16          timer_compare_MatchValue; /*it will be used in compare mode only*/
	Timer_ID_Type   timer_ID;
	Timer_ClockType timer_clock;
	Timer_ModeType  timer_mode;
}Timer_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/**
 * @brief  Function To Initialize the Timer by the Given Settings.
 * @param  Constant pointer to the Settings Data.
 * @return void.
 */
void Timer_init(const Timer_ConfigType *Config_Ptr);

/**
 * @brief  Function to disable the Timer via Timer_ID.
 * @param  Timer ID.
 * @return void.
 */
void Timer_deInit(Timer_ID_Type timer_type);

/**
 * @brief  Function to set the Call Back function address to the required Timer.
 * @param  pointer to Call Back function and Timer Id you want to set The Callback to it.
 * @return void.
 */
void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID);

#endif /* MCAL_TIMER_TIMER_H_ */
