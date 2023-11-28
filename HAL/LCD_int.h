/*
 * LCD_int.h
 *
 *  Created on: Nov 24, 2023
 *      Author: Samar ibrahim
 */


#ifndef LCD_INT_H_
#define LCD_INT_H_

ES_t LCD_enuInit(void);
ES_t LCD_enuDisplayChar(u8 Copy_u8Data);
ES_t LCD_enuSendCommand(u8 Copy_u8Command);
void LCD_vidClearScreen(void);
ES_t LCD_enuGoToPosition(u8 Copy_u8Row, u8 Copy_u8Col);
ES_t LCD_enuWriteString(u8 *Copy_pu8Str,u8 Copy_u8Row, u8 Copy_u8Col);
ES_t LCD_enuDisplayNum(s32 Copy_s32Num);
#endif /* LCD_INT_H_ */
