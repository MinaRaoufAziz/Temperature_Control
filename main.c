/*
 * main.c
 *
 *  Created on: Nov 7, 2019
 *      Author: Rafaat
 */

#include "LCD.h"
#include "avr/io.h"
#include "avr/interrupt.h"
#include "avr/sleep.h"
#include "avr_reg.h"
#include "PWM.h"
void TEMP_init (void);

void TEMP_read (void);
void ExternalInterrupt();
uint16  TempData=0;
uint8 ADC_completeFlag=0;
uint16 TempValue=0;
uint16 TempValue1=0;
uint8 	Duty=0;
int main(void)
{
	LCD_INIT_4bit();
	ExternalInterrupt();
	TEMP_init();
	PWM_init(PWM_0);
	PWM_Start (PWM_0, CLK_1024);
	PWM_ChangeDutyCycle (TIMER_0, Duty);
	LCD_String_DISP(0,0,"Temp :");
	LCD_String_DISP(1,0,"Duty:");
    sei();
	while(1)
	{
		LCD_NUM_DISP(0,8,TempValue);
		if(TempValue > 24)
		{
			Duty = ((TempValue -24)/2) *10;
			PWM_ChangeDutyCycle(TIMER_0,Duty);
			LCD_NUM_DISP(1,8,Duty);
		}
		else
		{
			Duty=0;
			PWM_ChangeDutyCycle(TIMER_0,Duty);
		}
		MCUCR|=1<<SE;
		//set_sleep_mode(SLEEP_MODE_IDLE);
		//	_delay_ms(100);
	}
	return 0;

}


void TEMP_init (void)
{
	ADMUX |= 1<<REFS0; //reference
	ADCSRA |=1<<ADEN; //Enable ADC
	ADCSRA  |= 1<<ADPS0 | 1<<ADPS1|1<<ADPS2; // prescaler
	ADCSRA |=1<<ADIE|1<<ADATE; // enable int
	SFIOR|=1<<ADTS1;
}
void TEMP_read (void)
{
	ADMUX |=0x40;		// PIN 0 in multiplexer

}

ISR(ADC_vect)
{
//ADC_completeFlag=0;
	TempValue=(ADC*4.88)/(10);
}

ISR(INT0_vect)
{
	PORTB ^=1<<PINB4;

	//TEMP_read (); //start conv
}

void ExternalInterrupt()
{
	DDRB|=1<<PINB4|1<<PINB5|1<<PINB6;
	PORTB |=1<<PINB4;
	DDRB&=~(1<<PIND2);
	GICR|=1<<INT0;
	MCUCR |=1<<ISC01|1<<ISC00;
}

