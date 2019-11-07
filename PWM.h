/*
 * PWM.h
 *
 *  Created on: Nov 7, 2019
 *      Author: abdelqader
 */

#ifndef PWM_H_
#define PWM_H_

#include "STD_Types.h"
#include "avr_reg.h"
#include "PWM_conf.h"


typedef enum { PWM_NOK, PWM_OK, PWM_NotRunning } EnumPWMStatus_t;


EnumPWMStatus_t PWM_init (uint8 TimerSpecs);
EnumPWMStatus_t PWM_Start (uint8 TimerName, uint8 Prescaler_Conf) ;
EnumPWMStatus_t PWM_Stop (uint8 TimerName);
EnumPWMStatus_t PWM_ChangeDutyCycle (EnumPWMState_t TimerNumber, uint8 DutyCyclePercentage);

#endif /* PWM_H_ */
