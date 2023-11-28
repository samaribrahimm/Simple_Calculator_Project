/*
 * LCD_Prog.c
 *
 *  Created on: Nov 24, 2023
 *      Author: Samar ibrahim
 */

#include "stdTypes.h"
#include "errorStates.h"

#include "DIO_int.h"

#include "LCD_config.h"
#include "LCD_priv.h"

#include "util/delay.h"
ES_t LCD_enuInit(void)
{
	ES_t Local_enuErrorState = ES_NOK;
	_delay_ms(30);
/*set direction for control pins "Output"*/
DIO_enuSetPinDirection(RS_PORT,RS_PIN,DIO_u8OUTPUT);
DIO_enuSetPinDirection(RW_PORT,RW_PIN,DIO_u8OUTPUT);
DIO_enuSetPinDirection(EN_PORT,EN_PIN,DIO_u8OUTPUT);
/*set direction for Data pins "Output"*/
DIO_enuSetPinDirection(D7_PORT,D7_PIN,DIO_u8OUTPUT);
DIO_enuSetPinDirection(D6_PORT,D6_PIN,DIO_u8OUTPUT);
DIO_enuSetPinDirection(D5_PORT,D5_PIN,DIO_u8OUTPUT);
DIO_enuSetPinDirection(D4_PORT,D4_PIN,DIO_u8OUTPUT);

#if LCD_MODE == EIGHT_BIT
DIO_enuSetPinDirection(D3_PORT,D3_PIN,DIO_u8OUTPUT);
DIO_enuSetPinDirection(D2_PORT,D2_PIN,DIO_u8OUTPUT);
DIO_enuSetPinDirection(D1_PORT,D1_PIN,DIO_u8OUTPUT);
DIO_enuSetPinDirection(D0_PORT,D0_PIN,DIO_u8OUTPUT);

/*Function Set for 8 mode*/
LCD_invidSendCommand(FUN_SET_EIGHT);

#elif LCD_MODE == FOUR_BIT
/*Function Set for 4 mode*/
LCD_invidSendCommend(FUN_SET_FOUR);
#else
#error "LCD_MODE has a wrong selection"
#endif
   _delay_ms(1);
	LCD_invidSendCommand(DISPLAY_ON); //display on and cursor and blink
	_delay_ms(1);
	LCD_invidSendCommand(DISPLAY_CLEAR);
	_delay_ms(2);
	LCD_invidSendCommand(ENTRY_MODE); //Write left to right increase
	return Local_enuErrorState;


}
ES_t LCD_enuDisplayChar(u8 Copy_u8Data)
{
	ES_t Local_enuErrorState = ES_NOK;

	/*set pin value for RS=1 to DATA*/
	DIO_enuSetPinVal(RS_PORT , RS_PIN , DIO_u8HIGH);

	LCD_vidLantch(Copy_u8Data);

	return Local_enuErrorState;


}
ES_t LCD_enuSendCommand(u8 Copy_u8Command)
{
	ES_t Local_enuErrorState = ES_NOK;

	/*set pin value for RS=0 to command*/
	Local_enuErrorState=DIO_enuSetPinVal(RS_PORT,RS_PIN,DIO_u8LOW);
	 LCD_vidLantch(Copy_u8Command);



	return Local_enuErrorState;


}
static void LCD_vidLantch(u8 Copy_u8Data){


	    /* set pin value for RW=0 to write ,Enable pin (EN)=LOW */
		DIO_enuSetPinVal(RW_PORT,RW_PIN,DIO_u8LOW);
	    DIO_enuSetPinVal(EN_PORT,EN_PIN,DIO_u8LOW);

	    /* set pin value for DATA pins */
	    DIO_enuSetPinVal(D7_PORT,D7_PIN,(Copy_u8Data>>BIT_SEVEN)&MASK_NUM);
	    DIO_enuSetPinVal(D6_PORT,D6_PIN,(Copy_u8Data>>BIT_SIX  )&MASK_NUM);
	    DIO_enuSetPinVal(D5_PORT,D5_PIN,(Copy_u8Data>>BIT_FIVE )&MASK_NUM);
	    DIO_enuSetPinVal(D4_PORT,D4_PIN,(Copy_u8Data>>BIT_FOUR)&MASK_NUM);
#if LCD_MODE ==EIGHT_BIT
		DIO_enuSetPinVal(D3_PORT,D3_PIN,(Copy_u8Data>>BIT_THREE)&MASK_NUM);
		DIO_enuSetPinVal(D2_PORT,D2_PIN,(Copy_u8Data>>BIT_TWO  )&MASK_NUM);
		DIO_enuSetPinVal(D1_PORT,D1_PIN,(Copy_u8Data>>BIT_ONE  )&MASK_NUM);
		DIO_enuSetPinVal(D0_PORT,D0_PIN,(Copy_u8Data>>BIT_ZERO )&MASK_NUM);
#elif LCD_MODE ==FOUR_BIT

		  /*Enable*/
	      DIO_enuSetPinVal(EN_PORT,EN_PIN,DIO_u8HIGH);
	      _delay_ms(10);
	      DIO_enuSetPinVal(EN_PORT,EN_PIN,DIO_u8LOW);

		 DIO_enuSetPinVal(D7_PORT,D7_PIN,(Copy_u8Data>>BIT_THREE)&MASK_NUM);
	     DIO_enuSetPinVal(D6_PORT,D6_PIN,(Copy_u8Data>>BIT_TWO  )&MASK_NUM);
	     DIO_enuSetPinVal(D5_PORT,D5_PIN,(Copy_u8Data>>BIT_ONE  )&MASK_NUM);
		 DIO_enuSetPinVal(D4_PORT,D4_PIN,(Copy_u8Data>>BIT_ZERO &MASK_NUM);
#else
#error "LCD_MODE has a wrong selection"
#endif
		/*Enable*/
		 DIO_enuSetPinVal(EN_PORT,EN_PIN,DIO_u8HIGH);
		 _delay_ms(10);
		 DIO_enuSetPinVal(EN_PORT,EN_PIN,DIO_u8LOW);

		// _delay_ms(10);
}


void LCD_vidClearScreen(void)
{
	LCD_invidSendCommand(DISPLAY_CLEAR);
	//LCD_u8PosCounter = 0;
}

static inline void LCD_invidSendCommand(u8 Copy_u8Command)
{

		/*set pin value for RS=0 to command*/
		DIO_enuSetPinVal(RS_PORT,RS_PIN,DIO_u8LOW);

		LCD_vidLantch(  Copy_u8Command);
}

ES_t LCD_enuGoToPosition(u8 Copy_u8Row, u8 Copy_u8Col){
	ES_t Local_enuErrorState = ES_NOK;
    u8 Local_u8Address;
    if(Copy_u8Row<2&&Copy_u8Col<16){
    	Local_u8Address=(Copy_u8Row*0x40+Copy_u8Col);
    	Local_u8Address |= (1 << 7);
    	LCD_enuSendCommand(Local_u8Address);

    }

	return Local_enuErrorState;
}

ES_t LCD_enuWriteString(u8 *Copy_pu8Str,u8 Copy_u8Row, u8 Copy_u8Col){
	ES_t Local_enuErrorState = ES_NOK;
	LCD_enuGoToPosition(Copy_u8Row,  Copy_u8Col);
	u8 Local_u8Index=0;
	u8 Local_u8Line=Copy_u8Row;
	if(Copy_pu8Str!=NULL){
		while(Copy_pu8Str[Local_u8Index] !='\0' && ((Copy_u8Row*16)+(Copy_u8Col+Local_u8Index))<32){
			if(((Copy_u8Row*16)+(Copy_u8Col+Local_u8Index))<16){

				Local_enuErrorState=LCD_enuDisplayChar(Copy_pu8Str[Local_u8Index]);
				Local_u8Index++;
			}
			else if(((Copy_u8Row*16)+(Copy_u8Col+Local_u8Index))==16 && Local_u8Line==0){
				LCD_enuGoToPosition(1,0);
				Local_u8Line++;

			}
			else if((Copy_u8Col+Local_u8Index)<32 && Local_u8Line==1){
				Local_enuErrorState=LCD_enuDisplayChar(Copy_pu8Str[Local_u8Index]);
				Local_u8Index++;
			}
		}
	}
	else
		{
			return ES_NULL_POINTER;
		}
		return Local_enuErrorState;

}
ES_t LCD_enuDisplayNum(s32 Copy_s32Num)
{
	ES_t Local_enuErrorState = ES_NOK;
	u32 Local_As8Container[16];
	s32 Local_s32Reverse=0;
	u8 Local_u8Remainder=0 , Local_u8NumDigit=0;
   u8 x=0;
	if(Copy_s32Num <0)
	{
		LCD_enuDisplayChar('-');
		Copy_s32Num *= -1 ;
	}
	while (Copy_s32Num)
	{
		Local_u8Remainder = Copy_s32Num % 10;
		Local_s32Reverse = Local_s32Reverse * 10 + Local_u8Remainder;
		Copy_s32Num /=10;
		Local_u8NumDigit ++;
	}

	while (Local_u8NumDigit)
	{
		Local_u8Remainder = Local_s32Reverse % 10;

		x=Local_u8Remainder + '0';
		LCD_enuDisplayChar(x);
		Local_s32Reverse /= 10;
		Local_u8NumDigit --;
	}

	return Local_enuErrorState;
}
