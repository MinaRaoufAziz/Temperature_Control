/*
 * temp_sensor.c
 *
 *  Created on: Nov 7, 2019
 *      Author: Mina
 */

#include "temp_sensor.h"

EnumTEMPstatus_t TEMP_init (void)
{
	uint8 retval;
	uint8 init_Status;
	init_Status = ADC_init (void);
	if (OK == init_status)
	{
		retval = TEMP_OK;
	}
	else
	{
		retval = TEMP_INIT_ERR + init_Status;
	}
	return retval;
}

EnumTEMPstatus_t TEMP_read (uint32 * Analog_Data)
{
	uint8 retval;
	uint8 init_Status;
	uint32 temp;
	//read_status = ADC_read (TEMP_SENSOR_PIN, Data);
	temp = (Data * 5000) / 1024;
	*Analog_Data = (temp * 150) / 1500;
	if (OK == read_status)
	{
		retval = TEMP_OK;
	}
	else
	{
		retval = init_Status + TEMP_READ_ERR;
	}

	return retval;
}
