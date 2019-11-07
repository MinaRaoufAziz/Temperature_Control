/*
 * PWM_conf.c
 *
 *  Created on: Nov 7, 2019
 *      Author: abdelqader
 */


#include"PWM_conf.h"


//  TIMER , MODE, COMP_PIN, CHANNAL,  COMP_REG,  TOP_VALUE, PRESCALER, STATE

PWM_Conf_t PWM_Array [NUM_PWM_STATES] = {

	{TIMER_0 , Fast_PWM , Inverted , NA_T , 200 , NA_T, CLK_1024}
};
