/*
 * main.c
 *
 *  Created on: Nov 7, 2019
 *      Author: abdelqader
 */

#include "ADC.h"
#include "LCD.h"
#include "avr_reg.h"


uint16 ADCH_ADCL = 0;


void Fun (uint16 Val)
{

	ADCH_ADCL = Val;

}


int main(void)
{

	LCD_INIT_4bit();
	LCD_CHAR_DISP(0,0, 'B');

	uint8 ADCH_Voltage = 0;

	DDRB = 0xff;

	ADC_SetCallBack(Fun);

	ADC_init();



	while(1)
	{




		ADC_VoidStartConversionInterruptBased(0);

		ADCH_Voltage =  ( (ADCH_ADCL * 5) / 1023) ;

		if ( (ADCH_Voltage >= 1) && (ADCH_Voltage <= 2) ){
			LCD_NUM_DISP(0,0, ADCH_Voltage);
			PORTB ^= (1<<7);
		}

		else if ((ADCH_Voltage >= 3) && (ADCH_Voltage <= 4)){
			LCD_NUM_DISP(0,0, ADCH_Voltage);
			PORTB ^= (1<<6);
		}

	}
	return 0;
}
