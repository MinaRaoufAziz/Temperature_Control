/*
 * Button.h
 *
 *  Created on: Nov 7, 2019
 *      Author: abdelqader
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "avr/interrupt.h"

void ButtonEnable(void);
void ButtonSetter( void (*PTRFunInApp) (void) );

#endif /* BUTTON_H_ */
