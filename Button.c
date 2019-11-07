/*
 * Button.c
 *
 *  Created on: Nov 7, 2019
 *      Author: abdelqader
 */

#include"Button.h"
#include"avr_reg.h"
#include"STD_Types.h"
#include"avr/interrupt.h"


void (*PTR)(void) = NULL;


void ButtonEnable(void)
{

	DDRB &=~(1<<2);
	GICR |= 1<<INT0;
	MCUCR |= 1<<ISC01|1<<ISC00;
}

void ButtonSetter( void (*PTRFunInApp) (void) )
{
	PTR = PTRFunInApp;
}


ISR(INT0_vect)
{

	if (PTR != NULL)
	{
		PTR();
	}

}
