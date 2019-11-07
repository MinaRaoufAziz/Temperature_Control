/*
 * main.c
 *
 *  Created on: Nov 7, 2019
 *      Author: abdelqader
 */

#include "avr_reg.h"
#include "PWM.h"
#include "avr/delay.h"


int main(void)
{
	PWM_init (PWM_0);


	while (1)
	{
		_delay_ms(2000);
		PWM_ChangeDutyCycle(TIMER_0, 25);
	}

	return 1;
}

