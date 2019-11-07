/*
 * ADC.c
 *
 *  Created on: Nov 7, 2019
 *      Author: abdelqader
 */

#include "ADC.h"
#include "avr_reg.h"
#include "STD_Types.h"

PtrFunctionForCallBack PtrFunction = NULL;

// RETURN VALUE OF THE FUNCTION
static uint16 ADCH_ADCL = 0;
static uint8 ADCL_Value = 0;



EnumADCstatus_t ADC_init (void)
{
	EnumADCstatus_t StateVal = ADC_OK;

	// VOLTAGE REFREANCE CONFIGURATION
#if ADC_VREF_SIGNAL==VREFExternal
	ADMUX |= (1<<REFS0);
	ADMUX &= ~(1<<REFS1);
#elif ADC_VREF_SIGNAL==VREFInternal
	ADMUX |= (1<<REFS0);
	ADMUX |= (1<<REFS1);
#else
	ADMUX &= ~(1<<REFS0);
	ADMUX &= ~(1<<REFS1);
#endif

	// ADJUSTEMENT CONFIGURATION
#if ADC_ADJUSTMENT_SIGNAL==LeftAdjustment
	ADMUX |= (1<<ADLAR);
#elif ADC_ADJUSTMENT_SIGNAL==RightAdjustment
	ADMUX &= ~(1<<ADLAR);
#endif

	// CLEAR FLAG
	ADCSRA |= (1<<ADIF);

	// PRESCALER CONFIGURATION
	ADC_PRESCALER_SIGNAL;


	// INTERRUPT DRIVEN CONFIGURATION
#if ADC_INTERRUPT_ENABLE_SIGNAL==InterruptEnable
	ADCSRA |= (1<<ADIE);
#endif

	// AUTOTRIGGER CONFIGURATION
#if	ADC_AUTOTRIGGER_SIGNAL==ADC_AutoTriggerOff
	ADCSRA &= ~(1<<ADATE);
#else
	ADCSRA |= (1<<ADATE);
#endif

	// ADC GENERAL ENABLE
	ADCSRA |= (1<<ADEN);

	return StateVal;
}


EnumADCstatus_t ADC_read (uint8 ADC_Channel, uint16 * Data)
{
	EnumADCstatus_t StateVal = ADC_NOK;

	// SELECTING THE USED CHANNEL
	ADC_Channel &= 0x07;
	ADMUX &= 0xE0;
	ADMUX |= ADC_Channel;

	// START CONVERSION
	ADCSRA |= (1<<ADSC);


	// ADJUSTEMENT CONFIGURATION
#if	ADC_ADJUSTMENT_SIGNAL==LeftAdjustment

	 //	POLLING IS USED
	while( ((ADCSRA >> ADIF)&1) == 0);
	  // CLEAR INTERRUPT FLAG
	  ADCSRA |= (1<<ADIF);
	  ADCL_Value = (ADCL>>6);
	  ADCH_ADCL = ( (ADCH<<2) | ADCL_Value);


#elif ADC_ADJUSTMENT_SIGNAL==RightAdjustment

	 //	POLLING IS USED
	  while( ((ADCSRA >> ADIF)&1) == 0);
	  // CLEAR INTERRUPT FLAG
	  ADCSRA |= (1<<ADIF);
	  ADCL_Value = ADCL;
	  ADCH_ADCL = ( (ADCH<<8) | ADCL_Value);

#endif

	  *Data = ADCH_ADCL;

	return StateVal;
}

void ADC_SetCallBack (PtrFunctionForCallBack PtrToFunctionInApp)
{
	PtrFunction = PtrToFunctionInApp;
}


void ADC_VoidStartConversionInterruptBased (uint8 ADC_Channel){
	// Channel between 0 and 7
	// SELECT THE CHANNAL
	ADC_Channel &= 0x07;
	ADMUX &= 0xE0;
	ADMUX |= ADC_Channel;
	// START CONVERSION BIT
	ADCSRA |= (1<<ADSC);
	// ENABLE GLOBAL INTERRUPT
	SREG |= (1<<7);
}


ISR(ADC_vect){

	// ADJUSTEMENT CONFIGURATION
#if	ADC_ADJUSTMENT_SIGNAL==LeftAdjustment
	  ADCL_Value = (ADCL>>6);
	  ADCH_ADCL = ( (ADCH<<2) | ADCL_Value);

#elif ADC_ADJUSTMENT_SIGNAL==RightAdjustment
	  ADCL_Value = ADCL;
	  ADCH_ADCL = ( (ADCH<<8) | ADCL_Value);

#endif

	if (PtrFunction != NULL)
	{
		// call back function execution with the argument of the return of the reading for the ADC
		PtrFunction(ADCH_ADCL);
	}

}

