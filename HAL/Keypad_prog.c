/*
 * Keypad_prog.c
 *
 *  Created on: Nov 27, 2023
 *      Author: samar ibrahim
 */
#include "stdTypes.h"
#include "errorStates.h"

#include "DIO_int.h"

#include "KeyPad_config.h"
#include "KeyPad_priv.h"

#include <util/delay.h>

ES_t Keypad_enuInit(void){
	ES_t Local_enuErrorState =ES_NOK;
	    Local_enuErrorState=DIO_enuSetPinDirection(COL1_PORT,COL1_PIN, DIO_u8OUTPUT);
		Local_enuErrorState=DIO_enuSetPinDirection(COL2_PORT,COL2_PIN, DIO_u8OUTPUT);
		Local_enuErrorState=DIO_enuSetPinDirection(COL3_PORT,COL3_PIN, DIO_u8OUTPUT);
		Local_enuErrorState=DIO_enuSetPinDirection(COL4_PORT,COL4_PIN, DIO_u8OUTPUT);

		Local_enuErrorState=DIO_enuSetPinDirection(ROW1_PORT,ROW1_PIN, DIO_u8INPUT);
		Local_enuErrorState=DIO_enuSetPinDirection(ROW2_PORT,ROW2_PIN, DIO_u8INPUT);
		Local_enuErrorState=DIO_enuSetPinDirection(ROW3_PORT,ROW3_PIN, DIO_u8INPUT);
		Local_enuErrorState=DIO_enuSetPinDirection(ROW4_PORT,ROW4_PIN, DIO_u8INPUT);

		Local_enuErrorState=DIO_enuSetPinVal(COL1_PORT,COL1_PIN, DIO_u8HIGH);
		Local_enuErrorState=DIO_enuSetPinVal(COL2_PORT,COL2_PIN, DIO_u8HIGH);
		Local_enuErrorState=DIO_enuSetPinVal(COL3_PORT,COL3_PIN, DIO_u8HIGH);
		Local_enuErrorState=DIO_enuSetPinVal(COL4_PORT,COL4_PIN, DIO_u8HIGH);

		Local_enuErrorState=DIO_enuSetPinVal(ROW1_PORT,ROW1_PIN, DIO_u8PULLUP);
		Local_enuErrorState=DIO_enuSetPinVal(ROW2_PORT,ROW2_PIN, DIO_u8PULLUP);
		Local_enuErrorState=DIO_enuSetPinVal(ROW3_PORT,ROW3_PIN, DIO_u8PULLUP);
		Local_enuErrorState=DIO_enuSetPinVal(ROW4_PORT,ROW4_PIN, DIO_u8PULLUP);




	 return  Local_enuErrorState ;

}

ES_t Keypad_enuGetPressedKey(u8 * Copy_pu8Value_Key){
	ES_t Local_enuErrorState =ES_NOK;
	if (Copy_pu8Value_Key != NULL)
		{
		    *Copy_pu8Value_Key = KEY_NOT_PRESSED;
		    u8 Local_u8RowIdx , Local_u8ColIdx,Local_u8GetState;
		    static u8 Local_Au8RowPorts[ROWS_NUM]    = { ROW1_PORT, ROW2_PORT, ROW3_PORT, ROW4_PORT };
			static u8 Local_Au8RowPins[ROWS_NUM]     = { ROW1_PIN , ROW2_PIN , ROW3_PIN , ROW4_PIN };
			static u8 Local_Au8ColPorts[COLUMNS_NUM]  = { COL1_PORT, COL2_PORT, COL3_PORT, COL4_PORT };
			static u8 Local_Au8ColPins[COLUMNS_NUM]  = { COL1_PIN , COL2_PIN , COL3_PIN , COL4_PIN };
            static u8 Local_AuKeyPad[ROWS_NUM][COLUMNS_NUM]=KEYS_ARRVALUES;

    for(Local_u8ColIdx=0;Local_u8ColIdx<COLUMNS_NUM;Local_u8ColIdx++)
    {
	   /*Activate current column*/
    	 Local_enuErrorState=DIO_enuSetPinVal(Local_Au8ColPorts[Local_u8ColIdx],Local_Au8ColPins [Local_u8ColIdx],DIO_u8LOW);

        for(Local_u8RowIdx=0;Local_u8RowIdx<ROWS_NUM;Local_u8RowIdx++)
        {
        /*Read the current Row*/
        	 Local_enuErrorState= DIO_enuGetPinVal(Local_Au8RowPorts[Local_u8RowIdx],Local_Au8RowPins [Local_u8RowIdx],&Local_u8GetState);

        /*check if switch is pressed */
       if(DIO_u8LOW==Local_u8GetState){
    	  *Copy_pu8Value_Key=Local_AuKeyPad[Local_u8RowIdx][Local_u8ColIdx];
    	  while(DIO_u8LOW==Local_u8GetState){
    		  Local_enuErrorState =DIO_enuGetPinVal(Local_Au8RowPorts[Local_u8RowIdx],Local_Au8RowPins [Local_u8RowIdx],&Local_u8GetState);
    	  }

       }

        }
        /* Deactive the current column */
        Local_enuErrorState= DIO_enuSetPinVal(Local_Au8ColPorts[Local_u8ColIdx],Local_Au8ColPins [Local_u8ColIdx],DIO_u8HIGH);
          }

		}
	else {
		Local_enuErrorState = ES_NULL_POINTER;
	}


		 return  Local_enuErrorState ;

}
