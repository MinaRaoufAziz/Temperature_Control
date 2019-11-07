/*
 * ADC_preconf.h
 *
 *  Created on: Nov 7, 2019
 *      Author: abdelqader
 */

#ifndef ADC_PRECONF_H_
#define ADC_PRECONF_H_

// A MODE TO GET THE ADC AS INTERRUPT DRIVEN DEVICE
// PLEASE CHOOSE BETWEEN (InterruptEnable, InterruptDisable)
#define ADC_INTERRUPT_ENABLE_SIGNAL 	InterruptEnable


// A MODE TO CHANGE THE VOLTAGE REFREANCE CONFIGURATION
// PLEASE CHOOSE BETWEEN (VREFInternal, VREFExternal, VREFAREF)
#define ADC_VREF_SIGNAL	VREFExternal


// A MODE TO CHANGE THE AUTO TRIGGER MODE
// PLEASE CHOOSE BETWEEN (ADC_AutoTriggerOn, ADC_AutoTriggerOff)
#define ADC_AUTOTRIGGER_SIGNAL	ADC_AutoTriggerOn


// A MODE TO CHANGE THE PRESCALER OF THE ADC
// PLEASE CHOOSE BETWEEN (ADC_PRESCALER_32, ADC_PRESCALER_64, ADC_PRESCALER_128)
#define	ADC_PRESCALER_SIGNAL	ADC_PRESCALER_64


// A MODE TO CHANGE THE LEFT ADJUSTEMENT MODE OF THE ADC
// PLEASE CHOOSE BETWEEN (LeftAdjustment, RightAdjustment)
#define ADC_ADJUSTMENT_SIGNAL	LeftAdjustment

#endif /* ADC_PRECONF_H_ */
