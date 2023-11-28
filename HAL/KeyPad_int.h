/*
 * KeyPad_int.h
 *
 *  Created on: Nov 27, 2023
 *      Author:samar ibrahim
 */

#ifndef KEYPAD_INT_H_
#define KEYPAD_INT_H_

ES_t Keypad_enuInit(void);

ES_t Keypad_enuGetPressedKey(u8 * Copy_pu8KeyValue);

#endif /* KEYPAD_INT_H_ */
