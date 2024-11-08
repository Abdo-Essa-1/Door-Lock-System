 /******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: gpio.h
 *
 * Description: Header file for the AVR GPIO driver
 *
 * Author: Abdelrahman Essa
 *
 *******************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_

#include "../../std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define NUM_OF_PORTS           4
#define NUM_OF_PINS_PER_PORT   8

#define PORTA_ID               0
#define PORTB_ID               1
#define PORTC_ID               2
#define PORTD_ID               3

#define PIN0_ID                0
#define PIN1_ID                1
#define PIN2_ID                2
#define PIN3_ID                3
#define PIN4_ID                4
#define PIN5_ID                5
#define PIN6_ID                6
#define PIN7_ID                7

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/* Enumeration for Pin Direction Type */
typedef enum
{
	PIN_INPUT,PIN_OUTPUT
}GPIO_PinDirectionType;

/* Enumeration for Port Direction Type */
typedef enum
{
	PORT_INPUT,PORT_OUTPUT=0xFF
}GPIO_PortDirectionType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/**
 * @brief  Setup the direction of the required pin input/output.If the
 *         input port number or pin number are not correct, the function
 *         will not handle the request.
 * @param  Port number, Pin number, Pin Direction.
 * @return void.
 */
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction);

/**
 * @brief  Write the value Logic High or Logic Low on the required pin.
 *         If the input port number or pin number are not correct, the
 *         function will not handle the request. If the pin is input, this
 *         function will enable/disable the internal pull-up resistor.
 * @param  Port Number, Pin number, Pin value.
 * @return void.
 */
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value);

/**
 * @brief  Read and return the value for the required pin, it should be
 *         Logic High or Logic Low. If the input port number or pin number
 *         are not correct, The function will return Logic Low.
 * @param  Port Number, Pin number.
 * @return Pin Value.
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num);

/**
 * @brief  Setup the direction of the required port all pins input/output.
 *         If the direction value is PORT_INPUT all pins in this port should be input pins.
 *         If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 *         If the input port number is not correct, The function will not handle the request.
 * @param  Port Number, Port Direction.
 * @return void.
 */
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction);

/**
 * @brief  Write the value on the required port.
 *         If any pin in the port is output pin the value will be written.
 *         If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 *         If the input port number is not correct, The function will not handle the request.
 * @param  Port Number, Port Value.
 * @return void.
 */
void GPIO_writePort(uint8 port_num, uint8 value);

/**
 * @brief  Read and return the value of the required port.
 *         If the input port number is not correct, The function will return ZERO value.
 * @param  Port Number.
 * @return Port Value.
 */
uint8 GPIO_readPort(uint8 port_num);

#endif /* GPIO_H_ */
