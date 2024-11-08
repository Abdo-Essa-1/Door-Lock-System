/******************************************************************************
 *
 * Module: TWI(I2C)
 *
 * File Name: twi.h
 *
 * Description: Header file for the TWI(I2C) AVR driver
 *
 * Author: Abdelrahman Essa
 *
 *******************************************************************************/ 

#ifndef TWI_H_
#define TWI_H_

#include "../../std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

/*******************************************************************************
 *                             Types Declaration                               *
 *******************************************************************************/

/* Data type for TWI Address */
typedef uint8     TWI_AddressType;

/* Data type for TWI Baud Rate */
typedef uint32    TWI_BaudRateType;

/* Enumeration for TWI Prescaler */
typedef enum{
	TWI_PRE_1, TWI_PRE_4, TWI_PRE_16, TWI_PRE_64
}TWI_PRESCALER;

/* Data Structure for TWI Configurations */
typedef struct{
	TWI_AddressType  address;
	TWI_BaudRateType bit_rate;
	TWI_PRESCALER    twi_pre;
}TWI_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/**
 * @brief  Function to initialize the TWI module with Chosen settings.
 * @param  Constant pointer to Settings data.
 * @return void.
 */
void TWI_init(const TWI_ConfigType *Config_Ptr);

/**
 * @brief  Function to generate a start condition on the TWI bus to initiate communication.
 * @param  void.
 * @return void.
 */
void TWI_start(void);

/**
 * @brief  Function to generate a stop condition on the TWI bus to terminate communication.
 * @param  void.
 * @return void.
 */
void TWI_stop(void);

/**
 * @brief  Function to Write a byte of data to the TWI bus.
 * @param  Data to be written in TWI bus.
 * @return void.
 */
void TWI_writeByte(uint8 data);

/**
 * @brief  Function to Read a byte of data from the TWI bus with ACK (acknowledge).
 * @param  void.
 * @return Data read from the TWI bus with ACK.
 */
uint8 TWI_readByteWithACK(void);

/**
 * @brief  Function to Read a byte of data from the TWI bus with NACK (no acknowledge).
 * @param  void.
 * @return The byte of data read from the TWI bus with NACK.
 */
uint8 TWI_readByteWithNACK(void);

/**
 * @brief  Function to retrieve the current status of the TWI module.
 * @param  void.
 * @return The status of the TWI module.
 */
uint8 TWI_getStatus(void);

#endif /* TWI_H_ */
