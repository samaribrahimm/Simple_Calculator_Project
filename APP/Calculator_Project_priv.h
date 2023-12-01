/*
 * Calculator_Project_priv.h
 *
 *  Created on: Nov 28, 2023
 *      Author: Samar ibrahim
 */

#ifndef CALCULATOR_PROJECT_PRIV_H_
#define CALCULATOR_PROJECT_PRIV_H_

/* operator */
#define ADDITION   '+'
#define SUBTRACTOR '-'
#define MULTIPLER  'x'
#define DIVISION   '/'
#define EQUAL      '='
#define CALCULATOR_ON 'c'


#define DIGIT_NINE  '9'
#define DIGIT_ZERO  '0'
/**/
#define RESET  '\0'
#define NUM_NEG  1
u8 Isoperator(u8 key);
u8 Isnum( u8 key);

void LCD_enuDisplayNumWithFraction(f32 number);
#endif /* CALCULATOR_PROJECT_PRIV_H_ */
