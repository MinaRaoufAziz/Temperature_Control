/*
 * main.c
 *
 *  Created on: Nov 7, 2019
 *      Author: abdelqader
 */

#include "ADC.h"
#include "avr_reg.h"


uint16 ADCH_ADCL = 0;


void Fun (uint16 Val)
{

	ADCH_ADCL = Val;

}


int main(void)
{

	uint8 ADCH_Voltage = 0;

	DDRD = 0xff;
	DDRB = 0xff;

	ADC_SetCallBack(Fun);
	ADC_init();


	while(1)
	{
		ADC_VoidStartConversionInterruptBased(0);

		ADCH_Voltage =  ( (ADCH_ADCL * 5) / 1023) ;

		if ( (ADCH_Voltage >= 1) && (ADCH_Voltage <= 2) ){

			PORTB ^= (1);
		}

		else if ((ADCH_Voltage >= 3) && (ADCH_Voltage <= 4)){

			PORTD ^= 1;
		}

	}
	return 0;
}
