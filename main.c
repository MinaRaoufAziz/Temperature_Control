/*
 * main.c
 *
 *  Created on: Nov 7, 2019
 *      Author: Mina
 */


#include "temp_sensor.h"
#include <avr/io.h>

int main ()
{
	/* Test Case 1: Input the value of 41 Decimal as input of MC.
	 * Then check if the temperature equals 20 degree or not
	 * if equals 20. Toggle led0
	 * else if equals 21. toggle led1*/
	uint32 var=0;
	while (1)
	{
		TEMP_read(&var);
		if (20 == var)
		{
			PORTB = 0x10;
		}
		else if (21 == var)
		{
			PORTB = 0x80;
		}


	}


	return 0;
}
