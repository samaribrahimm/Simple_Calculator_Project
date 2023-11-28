/*
 * LCD_Config.h
 *
 *  Created on: Nov 24, 2023
 *      Author: user
 */

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

/* mode of LCD 8 BITS OR 4 BITS */
#define LCD_MODE EIGHT_BIT


/*Control PIN */
#define RS_PORT DIO_u8PORTA
#define RS_PIN  DIO_u8PIN0

#define RW_PORT DIO_u8PORTA
#define RW_PIN  DIO_u8PIN1

#define EN_PORT DIO_u8PORTA
#define EN_PIN  DIO_u8PIN2


/*DATA PINS*/
#define D7_PORT DIO_u8PORTB
#define D7_PIN  DIO_u8PIN0

#define D6_PORT DIO_u8PORTB
#define D6_PIN  DIO_u8PIN1

#define D5_PORT DIO_u8PORTB
#define D5_PIN  DIO_u8PIN2

#define D4_PORT DIO_u8PORTC
#define D4_PIN  DIO_u8PIN0

#define D3_PORT DIO_u8PORTC
#define D3_PIN  DIO_u8PIN1

#define D2_PORT DIO_u8PORTC
#define D2_PIN  DIO_u8PIN2

#define D1_PORT DIO_u8PORTD
#define D1_PIN  DIO_u8PIN0

#define D0_PORT DIO_u8PORTD
#define D0_PIN  DIO_u8PIN1




#endif /* LCD_CONFIG_H_ */
