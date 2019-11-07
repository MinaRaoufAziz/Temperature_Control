/*
 * ADC.h
 *
 *  Created on: Nov 7, 2019
 *      Author: abdelqader
 */

#ifndef ADC_H_
#define ADC_H_

#include "ADC_preconf.h"
#include "STD_Types.h"


typedef void (*PtrFunctionForCallBack) (uint16 ADC_READING);
typedef enum { ADC_NOK, ADC_OK } EnumADCstatus_t;



// ------------------------ Function Prototype ---------------------------------------//


EnumADCstatus_t ADC_init (void);
EnumADCstatus_t ADC_read (uint8 ADC_Channel, uint16 * Data);
void ADC_VoidStartConversionInterruptBased(uint8 ADC_Channel);
void ADC_SetCallBack (PtrFunctionForCallBack PtrToFunctionInApp);

//-------------------------------------------------------------------------------------------------------//

/*

ADCSRA REGISTER'S PINS

7 	   6 	5 	 4 	   3 	2 	  1 	0
ADEN ADSC ADATE ADIF ADIE ADPS2 ADPS1 ADPS0

*/


#define ADEN	7
#define	ADSC	6
#define ADATE	5
#define	ADIF	4
#define	ADIE	3
#define	ADPS2	2
#define	ADPS1	1
#define	ADPS0	0


/*

ADMUX REGISTER'S PINS

  7 	6 	  5 	4 	3 	  2    1 	0
REFS1 REFS0 ADLAR MUX4 MUX3 MUX2 MUX1 MUX0

*/

#define REFS1	7
#define REFS0	6
#define ADLAR	5
#define	MUX4	4
#define MUX3	3
#define	MUX2	2
#define	MUX1	1
#define	MUX0	0




#define ADTS0		5
#define ADTS1		6
#define ADTS2		7

// ---------------------------------- CONFIGURATION -------------------------------------------//


#define InterruptEnable 1
#define InterruptDisable 0


#define VREFInternal 0
#define	VREFExternal 1
#define	VREFAREF	2

#define ADC_AutoTriggerOn	1
#define ADC_AutoTriggerOff	0

#define	LeftAdjustment	1
#define	RightAdjustment 0


#define	PRESCALER_32 0
#define	PRESCALER_64 1
#define PRESCALER_128 2



#define ADC_PRESCALER_32	ADCSRA |= (1<<ADPS0) | (1<<ADPS2)
#define ADC_PRESCALER_64	ADCSRA |= (1<<ADPS1) | (1<<ADPS2)
#define ADC_PRESCALER_128	ADCSRA |= (1<<ADPS1) |  (1<<ADPS0) | (1<<ADPS2)



//-----------------------------------------------------------------------------------------------------------//

// INTERRUPT SERVICE ROUNTINE ATTRIBUTES
#  define ISR(vector, ...)            \
    void vector (void) __attribute__ ((signal,__INTR_ATTRS)) __VA_ARGS__; \
    void vector (void)

// VECTOR NUMBER OF ADC
#define _VECTOR(N) __vector_ ## N
#define ADC_vect			_VECTOR(16)

//----------------------------------------------------------------------------------------------------------//





#endif /* ADC_H_ */
