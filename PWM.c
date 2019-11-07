/*
 * PWM.c
 *
 *  Created on: Nov 7, 2019
 *      Author: abdelqader
 */

#include"PWM.h"

EnumPWMStatus_t PWM_init (uint8 TimerSpecs)
{
	EnumPWMStatus_t StateVar = PWM_OK;
    // check if the timer exists in Array or not
    if (TimerSpecs < NUM_PWM_STATES)
    {
        // at which timer user wants to operate

		/************************************************************************/
		  /*                            Timer 0								*/
		/************************************************************************/
        if (PWM_Array[TimerSpecs].TIMER == TIMER_0)
        {

            switch(PWM_Array[TimerSpecs].MODE)
            {
				/************************************************************************/
				                /*            Fast PWM	        */
				/************************************************************************/
                case Fast_PWM:

                    TCCR0 = (1<<WGM01) | (1<<WGM00);
                    switch(PWM_Array[TimerSpecs].COMP_PIN)
                    {
                        case Disconnect:
                            TCCR0 &= (~(1<<COM00)) & (~(1<<COM01));
                            break;
                        case Non_Inverted:
                            TCCR0 &= (~(1<<COM00)) & (~(1<<COM01));
                            TCCR0 |= (1<<COM01);
							DDRB |= (1<<OC0);
                            break;
                        case Inverted:
                            TCCR0 &= (~(1<<COM00)) & (~(1<<COM01));
                            TCCR0 |= (1<<COM01) | (1<<COM00);
							DDRB |= (1<<OC0);
                            break;
						default:
							StateVar = PWM_NOK;
							break;
                    }
					OCR0 = PWM_Array[TimerSpecs].COMP_REG;
					break;
				/************************************************************************/
				                /*           Phase correct	        */
				/************************************************************************/
                case Phase_Correct:

                    TCCR0 = (1<<WGM00);
                    switch(PWM_Array[TimerSpecs].COMP_PIN)
                    {
                        case Disconnect:
                            TCCR0 &= (~(1<<COM00)) & (~(1<<COM01));
                            break;
                        case Non_Inverted:
                            TCCR0 &= (~(1<<COM00)) & (~(1<<COM01));
							DDRB |= (1<<OC0);
                            TCCR0 |= (1<<COM01);
                            break;
                        case Inverted:
                            TCCR0 &= (~(1<<COM00)) & (~(1<<COM01));
							DDRB |= (1<<OC0);
                            TCCR0 |= (1<<COM01) | (1<<COM00);
                            break;
						default:
							StateVar = PWM_NOK;
							break;
                    }
					OCR0 = PWM_Array[TimerSpecs].COMP_REG;
					break;

                default:
					StateVar = PWM_NOK;
                    break;
            }

            switch (PWM_Array[TimerSpecs].PRESCALER)
            {
            case No_Clock:
                TCCR0 &= (~(1<<CS00)) & (~(1<<CS01)) & (~(1<<CS02));
                PWM_Array[TimerSpecs].STATE = Not_Running;
                break;
            case No_Prescaler:
                TCCR0 &= (~(1<<CS00)) & (~(1<<CS01)) & (~(1<<CS02));
                TCCR0 |= (1<<CS00);
                PWM_Array[TimerSpecs].STATE = Running;
                break;
            case CLK_8:
                TCCR0 &= (~(1<<CS00)) & (~(1<<CS01)) & (~(1<<CS02));
                TCCR0 |=(1<<CS01);
                PWM_Array[TimerSpecs].STATE = Running;
                break;
            case CLK_64:
                TCCR0 &= (~(1<<CS00)) & (~(1<<CS01)) & (~(1<<CS02));
                TCCR0 |=(1<<CS00)|(1<<CS01);
                PWM_Array[TimerSpecs].STATE = Running;
                break;
            case CLK_256:
                TCCR0 &= (~(1<<CS00)) & (~(1<<CS01)) & (~(1<<CS02));
                TCCR0 |=(1<<CS02);
                PWM_Array[TimerSpecs].STATE = Running;
                break;
            case CLK_1024:
                TCCR0 &= (~(1<<CS00)) & (~(1<<CS01)) & (~(1<<CS02));
                TCCR0 |=(1<<CS00) | (1<<CS02);
                PWM_Array[TimerSpecs].STATE = Running;
                break;
            default:
				StateVar = PWM_NOK;
                break;
            }

        }

		/************************************************************************/
		    /* 			        	TIMER 1								   */
		/************************************************************************/
        else if (PWM_Array[TimerSpecs].TIMER == TIMER_1)
        {

			/************************************************************************/
			/*                   FAST_PWM using 10 bits                 s      */
			/************************************************************************/
            if (PWM_Array[TimerSpecs].MODE == Fast_PWM_10b)
            {
				TCCR1A = (1<<WGM10) | (1<<WGM11);
				TCCR1B &=~(1<<WGM13);
				TCCR1B = (1<<WGM12);

				switch(PWM_Array[TimerSpecs].CHANNAL)
				{
					case Channel_A:
						OCR1AH =  (PWM_Array[TimerSpecs].COMP_REG >> 8);
						OCR1AL =  ((PWM_Array[TimerSpecs].COMP_REG) & 0x00FF);

						switch(PWM_Array[TimerSpecs].COMP_PIN)
						{
							case Disconnect:
								TCCR1A &= (~(1<<COM1A0)) & (~(1<<COM1A1));
								break;
							case Non_Inverted:
								TCCR1A &= (~(1<<COM1A0)) & (~(1<<COM1A1));
								TCCR1A |= (1<<COM1A1);
                                DDRD |= (1<<OC1A);
								break;
							case Inverted:
								TCCR1A &= (~(1<<COM1A0)) & (~(1<<COM1A1));
								TCCR1A |= (1<<COM1A1) | (1<<COM1A0);
                                DDRD |= (1<<OC1A);
								break;
							default:
								StateVar = PWM_NOK;
								break;
						}
						break;

					case Channel_B:
						OCR1BH =  (PWM_Array[TimerSpecs].COMP_REG >> 8);
						OCR1BL =  ((PWM_Array[TimerSpecs].COMP_REG) & 0x00FF);

					switch(PWM_Array[TimerSpecs].COMP_PIN)
					{
						case Disconnect:
							TCCR1A &= (~(1<<COM1B0)) & (~(1<<COM1B1));
							break;
						case Non_Inverted:
							TCCR1A &= (~(1<<COM1B0)) & (~(1<<COM1B1));
							TCCR1A |= (1<<COM1B1);
                            DDRD |= (1<<OC1B);
							break;
						case Inverted:
							TCCR1A &= (~(1<<COM1B0)) & (~(1<<COM1B1));
							TCCR1A |= (1<<COM1B1) | (1<<COM1B0);
                            DDRD |= (1<<OC1B);
							break;
						default:
							StateVar = PWM_NOK;
							break;
					}
					break;
                    default:
                        StateVar = PWM_NOK;
                        break;
				}
            }

			/************************************************************************/
			/* FAST_PWM using ICR as a TOP value                                    */
			/************************************************************************/

            else if (PWM_Array[TimerSpecs].MODE == Fast_PWM_ICR)
            {
                TCCR1A |= (1u << WGM11);
                TCCR1B |= (1u << WGM12) | (1u << WGM13);
                // value of ICR
                ICR1H = (uint8) (PWM_Array[TimerSpecs].TOP_VALUE >> 8);
                ICR1L = (uint8) (PWM_Array[TimerSpecs].TOP_VALUE);
                switch (PWM_Array[TimerSpecs].CHANNAL )
                {
                    case Channel_A:
                    OCR1AH = (uint8) (PWM_Array[TimerSpecs].COMP_REG >> 8);
                    OCR1AL = (uint8) (PWM_Array[TimerSpecs].COMP_REG);

                    switch(PWM_Array[TimerSpecs].COMP_PIN)
                    {
                        case Disconnect:
						TCCR1A &= (~(1<<COM1A0)) & (~(1<<COM1A1));
                        break;
                        case Inverted:
                        DDRD |= (1u << OC1A);
						TCCR1A |= (1u<<COM1A1) | (1u<<COM1A0);
                        break;
                        case Non_Inverted:
                        DDRD |= (1u << OC1A);
                        TCCR1A |= (1u<<COM1A1);
                        break;
                        default:
                        StateVar = PWM_NOK;
                        break;
                    }
                    break;
                    case Channel_B:
                    OCR1BH = (uint8) (PWM_Array[TimerSpecs].COMP_REG >> 8);
                    OCR1BL = (uint8) (PWM_Array[TimerSpecs].COMP_REG);


                    switch(PWM_Array[TimerSpecs].COMP_PIN){
                        case Disconnect:
						TCCR1A &= (~(1<<COM1B0)) & (~(1<<COM1B1));
                        break;
                        case Inverted:
                        DDRD |= (1u << OC1B);
						TCCR1A |= (1u<<COM1B1) | (1u<<COM1B0);
                        break;
                        case Non_Inverted:
                        DDRD |= (1u << OC1B);
                        TCCR1A |= (1u<<COM1B1);
                        break;
                        default:
                        StateVar = PWM_NOK;
                        break;
                    	}
                    break;
                    default:
                    StateVar = PWM_NOK;
                    break;
                }
            }

			/************************************************************************/
			/* Phase Correct PWM using 10 bits                                   */
			/************************************************************************/
            else if (PWM_Array[TimerSpecs].MODE == Phase_Correct_10b)
            {
                TCCR1A |= (1u << WGM10) | (1u << WGM11);
                switch (PWM_Array[TimerSpecs].CHANNAL )
                {
                    case Channel_A:
                    OCR1AH = (uint8) (PWM_Array[TimerSpecs].COMP_REG >> 8);
                    OCR1AL = (uint8) (PWM_Array[TimerSpecs].COMP_REG);

                    switch(PWM_Array[TimerSpecs].COMP_PIN){
                        case Disconnect:
						TCCR1A &= (~(1<<COM1A0)) & (~(1<<COM1A1));
                        break;
                        case Inverted:
                        DDRD |= (1u << OC1A);
						TCCR1A |= (1u<<COM1A1) | (1u<<COM1A0);
                        break;
                        case Non_Inverted:
                        DDRD |= (1u << OC1A);
                        TCCR1A |= (1u<<COM1A1);
                        break;
                        default:
                        StateVar = PWM_NOK;
                        break;
                    }
                    break;
                    case Channel_B:
                    OCR1BH = (uint8) (PWM_Array[TimerSpecs].COMP_REG >> 8);
                    OCR1BL = (uint8) (PWM_Array[TimerSpecs].COMP_REG);
                    switch(PWM_Array[TimerSpecs].COMP_PIN){
                        case Disconnect:
						TCCR1A &= (~(1<<COM1B0)) & (~(1<<COM1B1));
                        break;
                        case Inverted:
                        DDRD |= (1u << OC1B);
						TCCR1A |= (1u<<COM1B1) | (1u<<COM1B0);
                        break;
                        case Non_Inverted:
                        DDRD |= (1u << OC1B);
                        TCCR1A |= (1u<<COM1B1);
                        break;
                        default:
                        StateVar = PWM_NOK;
                        break;
                    }
                    break;
                    default:
                    StateVar = PWM_NOK;
                    break;
                }
            }

			/************************************************************************/
			/*           Phase correct with ICR as TOP value                   */
			/************************************************************************/

            else if (PWM_Array[TimerSpecs].MODE == Phase_Correct_ICR)
            {
                TCCR1A |= (1u << WGM11);
                TCCR1B |= (1u << WGM13);
                // value of ICR
                ICR1H = (uint8) (PWM_Array[TimerSpecs].TOP_VALUE >> 8);
                ICR1L = (uint8) (PWM_Array[TimerSpecs].TOP_VALUE);
                switch (PWM_Array[TimerSpecs].CHANNAL )
                {
                    case Channel_A:
                    OCR1AH = (uint8) (PWM_Array[TimerSpecs].COMP_REG >> 8);
                    OCR1AL = (uint8) (PWM_Array[TimerSpecs].COMP_REG);
                    switch(PWM_Array[TimerSpecs].COMP_PIN){
                        case Disconnect:
						TCCR1A &= (~(1<<COM1A0)) & (~(1<<COM1A1));
                        break;
                        case Inverted:
                        DDRD |= (1u << OC1A);
						TCCR1A |= (1u<<COM1A1) | (1u<<COM1A0);
                        break;
                        case Non_Inverted:
                        DDRD |= (1u << OC1A);
                        TCCR1A |= (1u<<COM1A1);
                        break;
                        default:
                        StateVar = PWM_NOK;
                        break;
                    }
                    break;
                    case Channel_B:
                    OCR1BH = (uint8) (PWM_Array[TimerSpecs].COMP_REG >> 8);
                    OCR1BL = (uint8) (PWM_Array[TimerSpecs].COMP_REG);
                    switch(PWM_Array[TimerSpecs].COMP_PIN){
                        case Disconnect:
						TCCR1A &= (~(1<<COM1B0)) & (~(1<<COM1B1));
                        break;
                        case Inverted:
                        DDRD |= (1u << OC1B);
						TCCR1A |= (1u<<COM1B1) | (1u<<COM1B0);
                        break;
                        case Non_Inverted:
                        DDRD |= (1u << OC1B);
                        TCCR1A |= (1u<<COM1B1);
                        break;
                        default:
                        StateVar = PWM_NOK;
                        break;
                    }
                    break;
                    default:
                    StateVar = PWM_NOK;
                    break;
                }
            }

            /************************************************************************/
			/*        Phase and frequency correct with ICR as TOP value           */
			/************************************************************************/

            else if (PWM_Array[TimerSpecs].MODE == Phase_Freq_Correct_ICR)
            {
                TCCR1B |= (1u << WGM13);
                // value of the ICR
                ICR1H = (uint8) (PWM_Array[TimerSpecs].TOP_VALUE >> 8);
                ICR1L = (uint8) (PWM_Array[TimerSpecs].TOP_VALUE);

                switch (PWM_Array[TimerSpecs].CHANNAL )
                {
                    case Channel_A:
                    OCR1AH = (uint8) (PWM_Array[TimerSpecs].COMP_REG >> 8);
                    OCR1AL = (uint8) (PWM_Array[TimerSpecs].COMP_REG);
                    switch(PWM_Array[TimerSpecs].COMP_PIN){
                        case Disconnect:
						TCCR1A &= (~(1<<COM1A0)) & (~(1<<COM1A1));
                        break;
                        case Inverted:
                        DDRD |= (1u << OC1A);
						TCCR1A |= (1u<<COM1A1) | (1u<<COM1A0);
                        break;
                        case Non_Inverted:
                        DDRD |= (1u << OC1A);
                        TCCR1A |= (1u<<COM1A1);
                        break;
                        default:
                        StateVar = PWM_NOK;
                        break;
                    }
                    break;
                    case Channel_B:
                    OCR1BH = (uint8) (PWM_Array[TimerSpecs].COMP_REG >> 8);
                    OCR1BL = (uint8) (PWM_Array[TimerSpecs].COMP_REG);


                    switch(PWM_Array[TimerSpecs].COMP_PIN){
                        case Disconnect:
						TCCR1A &= (~(1<<COM1B0)) & (~(1<<COM1B1));
                        break;
                        case Inverted:
                        DDRD |= (1u << OC1B);
						TCCR1A |= (1u<<COM1B1) | (1u<<COM1B0);
                        break;
                        case Non_Inverted:
                        DDRD |= (1u << OC1B);
                        TCCR1A |= (1u<<COM1B1);
                        break;
                        default:
                        StateVar = PWM_NOK;
                        break;
                    }
                    break;
                    default:
                    StateVar = PWM_NOK;
                    break;
                }
            }

            switch (PWM_Array[TimerSpecs].PRESCALER)
            {
            case No_Clock:
                TCCR1B &= (~(1u <<CS12)) & (~(1u <<CS11)) & (~(1u <<CS10));
                PWM_Array[TimerSpecs].STATE = Not_Running;
                break;
            case No_Prescaler:
				TCCR1B &= (~(1u <<CS12)) & (~(1u <<CS11)) & (~(1u <<CS10));
                TCCR1B |= (1u << CS10);
                PWM_Array[TimerSpecs].STATE = Running;
                break;
            case CLK_8:
                TCCR1B &= (~(1u <<CS12)) & (~(1u <<CS11)) & (~(1u <<CS10));
				TCCR1B |= (1u << CS11);
				PWM_Array[TimerSpecs].STATE = Running;
                break;
            case CLK_64:
                TCCR1B &= (~(1u <<CS12)) & (~(1u <<CS11)) & (~(1u <<CS10));
				TCCR1B |=(1u << CS10) | (1u << CS11);
				PWM_Array[TimerSpecs].STATE = Running;
                break;
            case CLK_256:
                TCCR1B &= (~(1u <<CS12)) & (~(1u <<CS11)) & (~(1u <<CS10));
				TCCR1B |=(1<<CS12);
				PWM_Array[TimerSpecs].STATE = Running;
                break;
            case CLK_1024:
                TCCR1B &= (~(1u <<CS12)) & (~(1u <<CS11)) & (~(1u <<CS10));
				TCCR1B |=(1<<CS10) | (1<<CS12);
				PWM_Array[TimerSpecs].STATE = Running;
                break;
            default:
				StateVar = PWM_NOK;
                break;
            }
        }

		/************************************************************************/
		          /*                     TIMER 2						     */
		/************************************************************************/

        else if (PWM_Array[TimerSpecs].TIMER == TIMER_2)
        {
           switch(PWM_Array[TimerSpecs].MODE)
            {
        /************************************************************************/
		        /*                    FAST PWM					  */
		/************************************************************************/
                case Fast_PWM:
                    TCCR2 = (1<<WGM21) | (1<<WGM20);
                    switch(PWM_Array[TimerSpecs].COMP_PIN)
                    {
                        case Disconnect:
                            TCCR2 &= (~(1<<COM20)) & (~(1<<COM21));
                            break;
                        case Non_Inverted:
                            TCCR2 &= (~(1<<COM20)) & (~(1<<COM21));
                            TCCR2 |= (1<<COM21);
							DDRD |= (1<<OC2);
                            break;
                        case Inverted:
                            TCCR2 &= (~(1<<COM20)) & (~(1<<COM21));
                            TCCR2 |= (1<<COM21) | (1<<COM20);
							DDRD |= (1<<OC2);
                            break;
                    }
					OCR2 = PWM_Array[TimerSpecs].COMP_REG;
					break;
        /************************************************************************/
		        /*                    Phase correct				  */
		/************************************************************************/
                case Phase_Correct:
                    TCCR2 = (1<<WGM20);
                    switch(PWM_Array[TimerSpecs].COMP_PIN)
                    {
                        case Disconnect:
                            TCCR2 &= (~(1<<COM20)) & (~(1<<COM21));
                            break;
                        case Non_Inverted:
                            TCCR2 &= (~(1<<COM20)) & (~(1<<COM21));
                            TCCR2 |= (1<<COM21);
                            DDRD |= (1u << OC2);
                            break;
                        case Inverted:
                            TCCR2 &= (~(1<<COM20)) & (~(1<<COM21));
                            TCCR2 |= (1<<COM21) | (1<<COM20);
                            DDRD |= (1u << OC2);
                            break;
                    }
					OCR2 = PWM_Array[TimerSpecs].COMP_REG;
					break;

                default:
                    StateVar = PWM_NOK;
                    break;
            }
            switch (PWM_Array[TimerSpecs].PRESCALER)
            {
            case No_Clock:
                TCCR2 &= (~(1<<CS20)) & (~(1<<CS21)) & (~(1<<CS22));
                PWM_Array[TimerSpecs].STATE = Not_Running;
                break;
            case No_Prescaler:
                TCCR2 &= (~(1<<CS20)) & (~(1<<CS21)) & (~(1<<CS22));
                TCCR2 |= (1<<CS20);
                PWM_Array[TimerSpecs].STATE = Running;
                break;
            case CLK_8:
                TCCR2 &= (~(1<<CS20)) & (~(1<<CS21)) & (~(1<<CS22));
                TCCR2 |=(1<<CS21);
                PWM_Array[TimerSpecs].STATE = Running;
                break;

            case CLK_32:
                TCCR2 &= (~(1<<CS20)) & (~(1<<CS21)) & (~(1<<CS22));
                TCCR2 |=(1<<CS20) | (1<<CS21);
                PWM_Array[TimerSpecs].STATE = Running;
                break;

			case CLK_64:
				 TCCR2 &= (~(1<<CS20)) & (~(1<<CS21)) & (~(1<<CS22));
				 TCCR2 |=(1<<CS22);
                PWM_Array[TimerSpecs].STATE = Running;
				 break;

            case CLK_256:
                TCCR2 &= (~(1<<CS20)) & (~(1<<CS21)) & (~(1<<CS22));
                TCCR2 |=(1<<CS22) | (1<<CS21);
                PWM_Array[TimerSpecs].STATE = Running;
                break;
            case CLK_1024:
                TCCR2 &= (~(1<<CS20)) & (~(1<<CS21)) & (~(1<<CS22));
                TCCR2 |=(1<<CS20) | (1<<CS22) | (1<<CS21);
                PWM_Array[TimerSpecs].STATE = Running;
                break;
            default:
            StateVar = PWM_NOK;
                break;
            }
        }

        else
        {
            // wrong info
            StateVar = PWM_NOK;
        }
    }
    else
    {
        StateVar = PWM_NOK;
    }
    return StateVar;
}

EnumPWMStatus_t PWM_Start (uint8 TimerName, uint8 Prescaler_Conf)
{
    uint8 LoopIndex ;
    EnumPWMStatus_t StateVar = PWM_OK;
    for(LoopIndex=0; LoopIndex<NUM_PWM_STATES; LoopIndex++)
    {
        if (PWM_Array[LoopIndex].TIMER == TimerName)
        {
            if (PWM_Array[LoopIndex].STATE != Running)
            {
                if (TimerName == TIMER_0)
                {
                    switch(Prescaler_Conf)
                    {
                        case No_Prescaler:
                        TCCR0 &= (~(1<<CS00)) & (~(1<<CS01)) & (~(1<<CS02));
                        TCCR0 |= (1<<CS00);
                        PWM_Array[LoopIndex].STATE = Running;
                        break;
                        case CLK_8:
                        TCCR0 &= (~(1<<CS00)) & (~(1<<CS01)) & (~(1<<CS02));
                        TCCR0 |=(1<<CS01);
                        PWM_Array[LoopIndex].STATE = Running;
                        break;
                        case CLK_64:
                        TCCR0 &= (~(1<<CS00)) & (~(1<<CS01)) & (~(1<<CS02));
                        TCCR0 |=(1<<CS00) | (1<<CS01);
                        PWM_Array[LoopIndex].STATE = Running;
                        break;
                        case CLK_256:
                        TCCR0 &= (~(1<<CS00)) & (~(1<<CS01)) & (~(1<<CS02));
                        TCCR0 |=(1<<CS02);
                        PWM_Array[LoopIndex].STATE = Running;
                        break;
                        case CLK_1024:
                        TCCR0 &= (~(1<<CS00)) & (~(1<<CS01)) & (~(1<<CS02));
                        TCCR0 |=(1<<CS00) | (1<<CS02);
                        PWM_Array[LoopIndex].STATE = Running;
                        break;
                        default:
                        StateVar = PWM_NOK;
                        break;
                    }
                }
                else if (TimerName == TIMER_1)
                {
                    switch (Prescaler_Conf)
                    {
                        case No_Prescaler:
                            TCCR1B &= (~(1u <<CS12)) & (~(1u <<CS11)) & (~(1u <<CS10));
                            TCCR1B |= (1u << CS10);
                            PWM_Array[LoopIndex].STATE = Running;
                            break;
                        case CLK_8:
                            TCCR1B &= (~(1u <<CS12)) & (~(1u <<CS11)) & (~(1u <<CS10));
                            TCCR1B |= (1u << CS11);
                            PWM_Array[LoopIndex].STATE = Running;
                            break;
                        case CLK_64:
                            TCCR1B &= (~(1u <<CS12)) & (~(1u <<CS11)) & (~(1u <<CS10));
                            TCCR1B |=(1u << CS10) | (1u << CS11);
                            PWM_Array[LoopIndex].STATE = Running;
                            break;
                        case CLK_256:
                            TCCR1B &= (~(1u <<CS12)) & (~(1u <<CS11)) & (~(1u <<CS10));
                            TCCR1B |=(1<<CS12);
                            PWM_Array[LoopIndex].STATE = Running;
                            break;
                        case CLK_1024:
                            TCCR1B &= (~(1u <<CS12)) & (~(1u <<CS11)) & (~(1u <<CS10));
                            TCCR1B |=(1<<CS10) | (1<<CS12);
                            PWM_Array[LoopIndex].STATE = Running;
                            break;
                        default:
                            StateVar = PWM_NOK;
                            break;
                        }
                }
                else if (TimerName == TIMER_2)
                {
                    switch(Prescaler_Conf)
                    {
                        case No_Prescaler:
                        TCCR2 &= (~(1<<CS20)) & (~(1<<CS21)) & (~(1<<CS22));
                        TCCR2 |= (1<<CS20);
                        PWM_Array[LoopIndex].STATE = Running;
                        break;
                        case CLK_8:
                        TCCR2 &= (~(1<<CS20)) & (~(1<<CS21)) & (~(1<<CS22));
                        TCCR2 |=(1<<CS21);
                        PWM_Array[LoopIndex].STATE = Running;
                        break;
                        case CLK_32:
                        TCCR2 &= (~(1<<CS20)) & (~(1<<CS21)) & (~(1<<CS22));
                        TCCR2 |=(1<<CS20) | (1<<CS21);
                        PWM_Array[LoopIndex].STATE = Running;
                        break;
                        case CLK_64:
                        TCCR2 &= (~(1<<CS20)) & (~(1<<CS21)) & (~(1<<CS22));
                        TCCR2 |=(1<<CS22);
                        PWM_Array[LoopIndex].STATE = Running;
                        break;
                        case CLK_256:
                        TCCR2 &= (~(1<<CS20)) & (~(1<<CS21)) & (~(1<<CS22));
                        TCCR2 |=(1<<CS22) | (1<<CS21);
                        PWM_Array[LoopIndex].STATE = Running;
                        break;
                        case CLK_1024:
                        TCCR2 &= (~(1<<CS20)) & (~(1<<CS21)) & (~(1<<CS22));
                        TCCR2 |=(1<<CS20) | (1<<CS22) | (1<<CS21);
                        PWM_Array[LoopIndex].STATE = Running;
                        break;
                        default:
                        StateVar = PWM_NOK;
                        break;
                    }
                }
            }
            else
            {
                StateVar = PWM_NOK;
            }
        }
    }
    return StateVar;
}

EnumPWMStatus_t PWM_Stop (uint8 TimerName)
{
    uint8 LoopIndex ;
    EnumPWMStatus_t StateVar = PWM_OK;
    for(LoopIndex=0; LoopIndex<NUM_PWM_STATES; LoopIndex++)
    {
        if (PWM_Array[LoopIndex].TIMER == TimerName)
        {
            if (PWM_Array[LoopIndex].STATE == Running)
            {
                if (TimerName == TIMER_0)
                {
                TCCR0 &= (~(1<<CS00)) & (~(1<<CS01)) & (~(1<<CS02));
                PWM_Array[LoopIndex].STATE = Not_Running;
                }
                else if (TimerName == TIMER_1)
                {
                TCCR1B &= (~(1u <<CS12)) & (~(1u <<CS11)) & (~(1u <<CS10));
                PWM_Array[LoopIndex].STATE = Not_Running;
                }
                else if (TimerName == TIMER_2)
                {
                TCCR2 &= (~(1<<CS20)) & (~(1<<CS21)) & (~(1<<CS22));
                PWM_Array[LoopIndex].STATE = Not_Running;
                }
            }
            else
            {
                StateVar = PWM_NOK;
            }
        }
    }
    return StateVar;
}

EnumPWMStatus_t PWM_ChangeDutyCycle (EnumPWMState_t TimerNumber, uint8 DutyCyclePercentage)
{
	EnumPWMStatus_t StateVar = PWM_OK;
	uint16 CompReg = 0;
	float CompReg2 = 0;
	uint8 Local_Iterator;
	for (Local_Iterator = 0; Local_Iterator<NUM_PWM_STATES; Local_Iterator++)
	{
		if (TimerNumber == PWM_Array[Local_Iterator].TIMER)
		{
			// check if it is running or not
			if (PWM_Array[Local_Iterator].STATE != Running)
			{
				// return error
				StateVar = PWM_NotRunning;
				break;
			}
			else
			{
				// change duty cycle
				switch(PWM_Array[Local_Iterator].TIMER)
				{
					case TIMER_0:
						// change the comp reg to a certain number
						CompReg2 = (DutyCyclePercentage * 0.01);
						OCR0 = (uint8)((CompReg2 * 256));
						break;
					case TIMER_1:
						// conf for one mode only when top = 0x3ff
						CompReg = ((DutyCyclePercentage/100) * 1024);

						switch(PWM_Array[Local_Iterator].CHANNAL)
						{
						case Channel_A:
		                    OCR1AH = (uint8) (CompReg >> 8);
		                    OCR1AL = (uint8) (CompReg);
							break;
						case Channel_B:
							OCR1BH = (uint8) (CompReg >> 8);
							OCR1BL = (uint8) (CompReg);
							break;
						default:
							StateVar = PWM_NOK;
							break;
						}
						break;
					case TIMER_2:
						CompReg2 = (DutyCyclePercentage * 0.01);
						OCR2 = (uint8)((CompReg2 * 256));
						break;
					default:
						break;
				}
			}
		}
		else
		{
			StateVar = PWM_NOK;
		}
	}

	return StateVar;
}


