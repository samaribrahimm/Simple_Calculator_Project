/*
 * Calculator_Project_prog.c
 *
 *  Created on: Nov 28, 2023
 *      Author: Samar ibrahim
 */
#include "errorStates.h"
#include "stdTypes.h"

#include "DIO_int.h"
#include "DIO_config.h"

#include "LCD_int.h"
#include "LCD_Config.h"

#include "KeyPad_int.h"
#include "KeyPad_Config.h"

#include "Calculator_Project_int.h"
#include "Calculator_Project_priv.h"

#include "util/delay.h"9
/*Variable*/
s8 op1 = RESET, op2 = RESET, num = RESET;
u8 operator = RESET, signflag = RESET, key = KEY_NOT_PRESSED;
f32 result=RESET;

void Cal_enuRun(void) {

    Keypad_enuInit();
    /*LCD cannot initiates until key =CALCULATOR_ON*/
    do {
        Keypad_enuGetPressedKey(&key);
    } while (key != CALCULATOR_ON);

    LCD_enuInit();
    LCD_enuWriteString("WELCOME TO CAL.", 0, 0);
    _delay_ms(300);
    LCD_vidClearScreen();
    LCD_enuGoToPosition(0, 0);
    key = KEY_NOT_PRESSED;

    while(1){
    	 Keypad_enuGetPressedKey(&key);
    	 _delay_ms(30);
    	if(key==EQUAL){  // if user pressed '='

    		/*check is neg num*/
    		if (signflag == NUM_NEG) {
    		                num = -num;
    		                signflag = 0;
    		            }

    		            if (operator != RESET) {  // check if there is operator or not
    		                op2 = num;
    		                LCD_enuDisplayChar(key);
    		                key = KEY_NOT_PRESSED;
    		                Calculator(operator);

    		                //op1 = result;
    		            } else {
    		                LCD_enuDisplayChar(key);
    		                result = num;
    		                LCD_enuDisplayNum(result);
    		                key = KEY_NOT_PRESSED;
    		            }

    		            num = RESET;  //reset num to another operation

    	}
    	else if(key==CALCULATOR_ON){
    		LCD_vidClearScreen();
    		op1 = RESET, op2 = RESET, num = RESET;
    		operator = RESET, signflag = RESET, key = KEY_NOT_PRESSED;
    		//result=RESET;
    	}
    	else if(key=='-'){
    		if (num == RESET && (operator == RESET || operator != RESET)) {
    		                signflag = NUM_NEG;
    		                LCD_enuDisplayChar(key);
    		                key = KEY_NOT_PRESSED;
    		            } else {
    		                operator = key;
    		                if (op1 == RESET) {
    		                    op1 = num;
    		                }
    		                num = RESET;
    		                LCD_enuDisplayChar(key);
    		                key = KEY_NOT_PRESSED;
    	}}
    	else if(Isoperator(key)){
    		 operator = key;
    		if (signflag == NUM_NEG) {
    		    num = -num;
    		    signflag = RESET;
    		}
    		if (op1 == RESET) {
    		    op1 = num;
    		}
    		num = RESET;
    		LCD_enuDisplayChar(key);
    		key = KEY_NOT_PRESSED;
    	}
    	else if(Isnum(key)){
    		 num = num * 10 + (key - '0');
    		 LCD_enuDisplayChar(key);

    	}
    }


}
u8 Isoperator(u8 key){
	return ((key==ADDITION)||(key==SUBTRACTOR)||(key==MULTIPLER)||(key==DIVISION));
}
u8 Isnum( u8 key){
	return ((key<=DIGIT_NINE)&&(key>=DIGIT_ZERO));
}
void Calculator(u8 opr){
	switch (opr) {
	        case '+':
	            result = op1 + op2;
	            LCD_enuDisplayNum(result);
	            break;
	        case '-':
	            result = op1 - op2;
	            LCD_enuDisplayNum(result);
	            break;
	        case 'x':
	            result = op1 * op2;
	            LCD_enuDisplayNum(result);
	            break;
	        case '/':
	            if (op2 != 0) {
	                result = (f32)op1 / op2;
	                LCD_enuDisplayNum(result);
	            } else {
	                LCD_vidClearScreen();
	                LCD_enuWriteString("ERROR", 1, 6);
	                _delay_ms(2000);
	                LCD_vidClearScreen();
	                return;
	            }
	            break;
	        default:
	            break;
	    }

	    //op2 = RESET, num = RESET, signflag = RESET, key = KEY_NOT_PRESSED;
	}

