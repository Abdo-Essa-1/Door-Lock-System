 /******************************************************************************
 *
 * Module: TWI(I2C)
 *
 * File Name: twi.h
 *
 * Description: Source file for the TWI(I2C) AVR driver
 *
 * Author: Abdelrahman Essa
 *
 *******************************************************************************/

#include "twi.h"
#include "../../common_macros.h"
#include <avr/io.h>

/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/

/**
 * @brief  Function to initialize the TWI module with Chosen settings.
 * @param  Constant pointer to Settings data.
 * @return void.
 */
void TWI_init(const TWI_ConfigType *Config_Ptr)
{
    /* SCL Calculation using the user-defined Prescaler and Bit Rate
     *
     * SCL = (F_CPU / (16 + 2 * TWBR * Prescaler))
     *
     * SCL Common Speeds:
     *     Normal Mode       100 Kb/s (The Most Common)
     *     Fast Mode         400 Kb/s
     *     Fast Mode Plus    1 Mb/s
     *     High-Speed Mode   3.4 Mb/s (Mostly Not used)
     */
    TWBR = Config_Ptr->bit_rate;
	TWSR = Config_Ptr->twi_pre;
	
    /* Two Wire Bus address my address if any master device want to call me (used in case this MC is a slave device)
       General Call Recognition: Off */
    TWAR = ((Config_Ptr->address & 0x7F) << 1);
	
    TWCR = (1<<TWEN); /* enable TWI */
}

/**
 * @brief  Function to generate a start condition on the TWI bus to initiate communication.
 * @param  void.
 * @return void.
 */
void TWI_start(void)
{
    /* 
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    
    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

/**
 * @brief  Function to generate a stop condition on the TWI bus to terminate communication.
 * @param  void.
 * @return void.
 */
void TWI_stop(void)
{
    /* 
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

/**
 * @brief  Function to Write a byte of data to the TWI bus.
 * @param  Data to be written in TWI bus.
 * @return void.
 */
void TWI_writeByte(uint8 data)
{
    /* Put data On TWI data Register */
    TWDR = data;
    /* 
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */ 
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register(data is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

/**
 * @brief  Function to Read a byte of data from the TWI bus with ACK (acknowledge).
 * @param  void.
 * @return Data read from the TWI bus with ACK.
 */
uint8 TWI_readByteWithACK(void)
{
	/* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1 
	 */ 
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}

/**
 * @brief  Function to Read a byte of data from the TWI bus with NACK (no acknowledge).
 * @param  void.
 * @return The byte of data read from the TWI bus with NACK.
 */
uint8 TWI_readByteWithNACK(void)
{
	/* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}

/**
 * @brief  Function to retrieve the current status of the TWI module.
 * @param  void.
 * @return The status of the TWI module.
 */
uint8 TWI_getStatus(void)
{
    uint8 status;
    /* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
    status = TWSR & 0xF8;
    return status;
}
