#include"timer_conf.h"



//  TIMER , MODE, COMP_PIN, CHANNAL,  COMP_REG,  TOP_VALUE, PRESCALER, INTERRUPT, STATE

PWM_Conf_t PWM_Array [NUM_PWM_STATES] = {

	{TIMER_1 , Fast_PWM , Inverted , NA_T , 125 , NA_T, CLK_32, Disable},

};
