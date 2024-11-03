 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Abdelrahman Essa
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "../../std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/* Enumeration for UART Character Size */
typedef enum{
	UART_5BIT_DATA, UART_6BIT_DATA, UART_7BIT_DATA, UART_8BIT_DATA
}UART_BitDataType;

/* Enumeration for UART Parity Mode */
typedef enum{
	UART_Parity_OFF, UART_Parity_EVEN = 2, UART_Parity_ODD
}UART_ParityType;

/* Enumeration for UART Stop Bit Select */
typedef enum{
	UART_STOPBIT_1, UART_STOPBIT_2
}UART_StopBitType;

/* Data Type for UART Baud Rate Value */
typedef uint32 UART_BaudRateType;

/* Data Structure for UART Configurations */
typedef struct{
	UART_BitDataType bit_data;
	UART_ParityType parity;
	UART_StopBitType stop_bit;
	UART_BaudRateType baud_rate;
}UART_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/**
 * @brief  Function to Initialize the UART by the given settings.
 * @param  Constant pointer to the Settings data.
 * @return void.
 */
void UART_init(const UART_ConfigType *Config_Ptr);

/**
 * @brief  Function to send byte to another UART device.
 * @param  Byte to send.
 * @return void.
 */
void UART_sendByte(const uint8 data);

/**
 * @brief  Function to receive byte from another UART device.
 * @param  void.
 * @return Byte received.
 */
uint8 UART_receiveByte(void);

/**
 * @brief  Send the required string through UART to the other UART device.
 * @param  String to send.
 * @return void.
 */
void UART_sendString(const uint8 *Str);

/**
 * @brief  Receive the required string until the '#' symbol through UART from the other UART device.
 * @param  String to receive.
 * @return void.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
