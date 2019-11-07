/*
 * main.c
 *
 *  Created on: Nov 7, 2019
 *      Author: abdelqader
 */


#include "LCD.h"
#include "Button.h"
#include "PWM.h"
#include "temp_sensor.h"
#include "ADC.h"


void ButtonCallBack (void)
{
	ADC_VoidStartConversionInterruptBased(0);
}

static uint8 Duty = 0;

int main(void)
{

	LCD_INIT_4bit();
	TEMP_init();
	ButtonEnable();
	ButtonSetter(ButtonCallBack);
	PWM_init(PWM_0);
	PWM_Start (PWM_0, CLK_1024);
	PWM_ChangeDutyCycle (TIMER_0, Duty);
	LCD_String_DISP(0,0,"Temp :");
	LCD_String_DISP(1,0,"Duty:");
	sei();

	uint32 ADCH_Voltage = 0;

	while(1)
	{

		TEMP_read(&ADCH_Voltage);
		LCD_NUM_DISP(0,8,ADCH_Voltage);

		if(ADCH_Voltage > 24)
		{
			Duty = ((ADCH_Voltage -24)/2) *10;
			PWM_ChangeDutyCycle(TIMER_0,Duty);
			LCD_NUM_DISP(1,8,Duty);
		}
		else
		{
			Duty=0;
			PWM_ChangeDutyCycle(TIMER_0,Duty);
		}


	}
	return 0;
}
