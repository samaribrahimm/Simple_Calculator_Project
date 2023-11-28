/*
 * KeyPad_Config.h
 *
 *  Created on: Nov 27, 2023
 *      Author: user
 */

#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

/* num of ROWS AND COLUMS*/
#define ROWS_NUM	4
#define COLUMNS_NUM	    4
#define KEY_NOT_PRESSED		0xff
/*define keys values*/


#define KEYS_ARRVALUES				{\
									{'7', '8', '9', '/'},\
									{'4', '5', '6', 'x'},\
									{'1', '2', '3', '-'},\
									{'c', '0', '=', '+'},\
								}






/*config pins of key pad*/
#define COL1_PORT DIO_u8PORTA
#define COL1_PIN  DIO_u8PIN3

#define COL2_PORT DIO_u8PORTA
#define COL2_PIN  DIO_u8PIN4

#define COL3_PORT DIO_u8PORTA
#define COL3_PIN  DIO_u8PIN5

#define COL4_PORT DIO_u8PORTA
#define COL4_PIN  DIO_u8PIN6

#define ROW1_PORT DIO_u8PORTB
#define ROW1_PIN  DIO_u8PIN7

#define ROW2_PORT DIO_u8PORTB
#define ROW2_PIN  DIO_u8PIN6

#define ROW3_PORT DIO_u8PORTB
#define ROW3_PIN  DIO_u8PIN5

#define ROW4_PORT DIO_u8PORTB
#define ROW4_PIN  DIO_u8PIN4

#endif /* KEYPAD_CONFIG_H_ */
