 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: Header file for the LCD driver
 *
 * Author: Mohamed Tarek (Edited by Abdelrahman Essa)
 *
 *******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

#include "../../std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* LCD Data bits mode configuration, its value should be 4 or 8*/
#define LCD_DATA_BITS_MODE 8

#if((LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE != 8))

#error "Number of Data bits should be equal to 4 or 8"

#endif

/* LCD HW Ports and Pins IDs */
#define LCD_RS_PORT_ID                 PORTC_ID
#define LCD_RS_PIN_ID                  PIN0_ID

#define LCD_E_PORT_ID                  PORTC_ID
#define LCD_E_PIN_ID                   PIN1_ID

#define LCD_DATA_PORT_ID               PORTA_ID

#if (LCD_DATA_BITS_MODE == 4)

#define LCD_DB4_PIN_ID                 PIN3_ID
#define LCD_DB5_PIN_ID                 PIN4_ID
#define LCD_DB6_PIN_ID                 PIN5_ID
#define LCD_DB7_PIN_ID                 PIN6_ID

#endif

/* LCD Commands */
#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_CURSORBLINKING_ON                0x0D
#define LCD_CURSORMODE                       LCD_CURSOR_OFF
#define LCD_SET_CURSOR_LOCATION              0x80

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/**
 * @brief  Initialize the LCD:
 *         1. Setup the LCD pins directions by use the GPIO driver.
 *         2. Setup the LCD Data Mode 4-bits or 8-bits.
 * @param  void.
 * @return void.
 */
void LCD_init(void);

/**
 * @brief  Display the required character on the screen.
 * @param  Character to display.
 * @return void.
 */
void LCD_displayCharacter(uint8 data);

/**
 * @brief  Display the required string on the screen.
 * @param  String to display.
 * @return void.
 */
void LCD_displayString(const char *Str);

/**
 * @brief  Move the cursor to a specified row and column index on the screen.
 * @param  Row and Column to where move.
 * @return void.
 */
void LCD_moveCursor(uint8 row,uint8 col);

/**
 * @brief  Display the required string in a specified row and column index on the screen.
 * @param  Row, Column and the string to display.
 * @return void.
 */
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);

/**
 * @brief  Display the required decimal value on the screen.
 * @param  integer to display.
 * @return void.
 */
void LCD_intgerToString(int data);

/**
 * @brief  Send the clear screen command.
 * @param  void.
 * @return void.
 */
void LCD_clearScreen(void);

#endif /* LCD_H_ */
