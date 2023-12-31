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

#include "util/delay.h"
/*Variable*/
s32 op1 = RESET, op2 = RESET, num = RESET;
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
   // LCD_enuGoToPosition(0, 0);
    key = KEY_NOT_PRESSED;

    while(1){
    	 Keypad_enuGetPressedKey(&key);
    	 _delay_ms(30);
    	 label:
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
                            while(key!=CALCULATOR_ON){
                            	Keypad_enuGetPressedKey(&key);
                            	if(Isoperator(key)){
                            		op1 = result;							/* last result is the 1st operand */
                            		LCD_vidClearScreen();										/* clear the screen */
                            		LCD_enuDisplayNum(op1)	;					/* display op1 on lcd */
                            		operator = key;			/* save value of opcode */
                            		//LCD_enuDisplayChar(key);			/* display opcode on lcd */
                            		goto label;
                            		//Calculator(operator);								/* get the value of the 2nd operand */
                            	}
                            }
                            LCD_vidClearScreen();
                            result = RESET,op1=RESET,op2=RESET;



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
    		result=RESET, op1 = RESET, operator=RESET , op2 = RESET, num = RESET, signflag = RESET, key = KEY_NOT_PRESSED;
    	}


    	else if(Isoperator(key)){

    		if (key == '-') {
    		    	    if (num == RESET  && (operator == RESET || operator != RESET)) {
    		    	        // Case where '-' is pressed when no number is entered yet
    		    	        if (op1 != RESET && operator == RESET) {
    		    	            operator = key;
    		    	        }
    		    	        else{
    		    	        	signflag = NUM_NEG;
    		    	        	 //   num = -num;
    		    	        }

    		    	        LCD_enuDisplayChar(key);
    		    	        key = KEY_NOT_PRESSED;
    		    	    } else {
    		    	        // Case where '-' is pressed after a number and possibly an operator
    		    	        operator = key;
    		    	        if (op1 == RESET) {
    		    	        	if(signflag==NUM_NEG){
    		    	        		 num = -num;
    		    	        		 signflag=0;
    		    	        	}
    		    	        	 op1 = num;

    		    	        }
    		    	        num = RESET;
    		    	        LCD_enuDisplayChar(key);
    		    	        key = KEY_NOT_PRESSED;
    		    	    }
    		    	}
    		else{
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
    	}}

    	else if(Isnum(key)){
    		 num = num * 10 + (key - DIGIT_ZERO);
    		 LCD_enuDisplayChar(key);


    	}
    }


}
u8 Isoperator(u8 key){
	return ((key==ADDITION)||(key==MULTIPLER)||(key==DIVISION)||(key==SUBTRACTOR));
}
u8 Isnum( u8 key){
	return ((key<=DIGIT_NINE)&&(key>=DIGIT_ZERO));
}
/*function to calculate sum ,division,sub,and multipler   two operands*/
void Calculator(u8 opr){
	switch (opr) {
	        case ADDITION:
	            result = op1 + op2;

	            LCD_enuDisplayNumWithFraction(result);
	            break;
	        case SUBTRACTOR:
	            result = op1 - op2;
	            LCD_enuDisplayNumWithFraction(result);
	            break;
	        case MULTIPLER:
	            result = op1 * op2;
	            LCD_enuDisplayNumWithFraction(result);
	            break;
	        case DIVISION:
	            if (op2 != 0) {
	                result = (f32)op1 / op2;
	                LCD_enuDisplayNumWithFraction(result);
	            } else {
	                LCD_vidClearScreen();
	                LCD_enuWriteString("MATH ERROR ", 0,2);
	                key=KEY_NOT_PRESSED;
	                _delay_ms(2000);
	                LCD_vidClearScreen();

	            }
	            break;
	        default:
	            break;
	    }
            /*reset variable*/
	//op1 = result, operator=RESET , op2 = RESET, num = RESET, signflag = RESET, key = KEY_NOT_PRESSED;
	}
void Cal_viRestart(void){
while(key!=CALCULATOR_ON){
	            Keypad_enuGetPressedKey(&key);
	            if(Isoperator(key)){
	            	op1 = result;							/* last result is the 1st operand */
	            				LCD_vidClearScreen();										/* clear the screen */
	            				LCD_enuDisplayNum(op1)	;					/* display op1 on lcd */
	            				operator = key;			/* save value of opcode */
	            				LCD_enuDisplayChar(key);			/* display opcode on lcd */
	            				Calculator(operator);								/* get the value of the 2nd operand */
	            			}
	            		}
	            		LCD_vidClearScreen();
	            		result = RESET;
	            }


/*fun to display fraction number*/

void LCD_enuDisplayNumWithFraction(f32 number) {
    s32 integerPart = (s32)number;
    s32 fractionalPart = (s32)((number - integerPart) * 100); // For DECIMAL_PLACES = 2

    LCD_enuDisplayNum(integerPart);
    LCD_enuDisplayChar('.');

    // Print leading zeros for the fractional part
    if (fractionalPart < 10) {LCD_enuDisplayChar('0');}

    LCD_enuDisplayNum(fractionalPart);
}

