/*
 * LCD_priv.h
 *
 *  Created on: Nov 24, 2023
 *      Author: user
 */

#ifndef LCD_PRIV_H_
#define LCD_PRIV_H_

#define EIGHT_BIT 8
#define FOUR_BIT  4
#define MASK_NUM  1
#define Local_Iter 7


#define BIT_SEVEN 7
#define BIT_SIX   6
#define BIT_FIVE  5
#define BIT_FOUR  4
#define BIT_THREE 3
#define BIT_TWO   2
#define BIT_ONE   1
#define BIT_ZERO  0

/*initialization*/
#define FUN_SET_EIGHT  0x38
#define FUN_SET_FOUR   0x28
#define DISPLAY_ON 0x0f
#define DISPLAY_CLEAR  0x01
#define ENTRY_MODE     0x06

/*Proto type of fun */
static inline void LCD_invidSendCommand(u8 Copy_u8Command);
static void LCD_vidLantch(u8 Copy_u8Data);

#endif /* LCD_PRIV_H_ */
