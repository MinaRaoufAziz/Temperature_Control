/*
 * temp_sensor.h
 *
 *  Created on: Nov 7, 2019
 *      Author: Mina
 */

#ifndef TEMP_SENSOR_H_
#define TEMP_SENSOR_H_

#include "STD_Types.h"

#define TEMP_SENSOR_PIN		0

typedef enum {TEMP_INIT_ERR = -9, TEMP_READ_ERR, TEMP_OK = 10}EnumTEMPstatus_t;

void Read_Value (uint16 Analog_Data);
EnumTEMPstatus_t TEMP_init (void);
EnumTEMPstatus_t TEMP_read (uint32 * Analog_Data);


#endif /* TEMP_SENSOR_H_ */
