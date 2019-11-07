/*
 * temp_sensor.c
 *
 *  Created on: Nov 7, 2019
 *      Author: Mina
 */

#include "temp_sensor.h"
#include "ADC.h"


uint16 ADC_READ = 0;

void Read_Value (uint16 Analog_Data)
{
	ADC_READ = Analog_Data;
}


EnumTEMPstatus_t TEMP_init (void)
{
	EnumTEMPstatus_t retval = OK;

	ADC_SetCallBack(Read_Value);
	ADC_init();

	return retval;
}





EnumTEMPstatus_t TEMP_read (uint32 * Analog_Data)
{
	EnumTEMPstatus_t retval = OK;

	uint32 temp  = 0;
	temp = (ADC_READ * 4.88);
	*Analog_Data = (temp * 150) / 1500;


	return retval;
}
