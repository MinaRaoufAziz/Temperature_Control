#include "ExtInter.h"


void (*Ptr_INT0) (void) = NULL;
void (*Ptr_INT1) (void) = NULL;
void (*Ptr_INT2) (void) = NULL;

//ISR DEFINITION AND ATTRIBUTE
#define ISR(vector, ...)            \
    void vector (void) __attribute__ ((signal,__INTR_ATTRS)) __VA_ARGS__; \
    void vector (void)

//VECTOR NAMING
#define _VECTOR(N) __vector_ ## N

#define INT0_vect	_VECTOR(1)
#define INT1_vect	_VECTOR(2)
#define INT2_vect	_VECTOR(3)



STD_Fun_t INTP_vidInit(void)
{
    uint8 Local_Loop;
    STD_Fun_t StateVar = OK;
    if ( Num_Of_Interrupt <= 3){

        for(Local_Loop=0; Local_Loop<Num_Of_Interrupt; Local_Loop++){

            if (Interrupt_Array[Local_Loop].Name == INT0){
                // Pull Up Resistor
                DDRD &= ~(1<<INT0_PIN);
				//PORTD |= (1<<INT0_PIN);
                // Configuration
                switch(Interrupt_Array[Local_Loop].Trigger_Mode){
                    case INT0_LowLevel:
                    MCUCR &= (~(1<<ISC00)) & (~(1<<ISC01));
                    break;
                    case INT0_LogicalChange:
                    MCUCR |= (1<<ISC00); 
                    break;
                    case INT0_FallingEdge:
                    MCUCR |= (1<<ISC01);
                    break;
                    case INT0_RisingEdge:
                    MCUCR |= (1<<ISC01);
                    MCUCR |= (1<<ISC00);
                    break;
                    default:
                    StateVar = NOK;
                    break;
                }
                // Enable Interrupt
                switch(Interrupt_Array[Local_Loop].State){
                    case Active:
                    GICR |= (1<<INT0_GICRBIT);
                    SREG |= (1<<SREG_I); 
                    break;
                    case In_Active:

                    break;
                    default:
                    StateVar = NOK;
                    break;
                }
            }
            else if (Interrupt_Array[Local_Loop].Name == INT1){
                // Pull Up Resistor
                PORTD |= (1<<INT1_PIN);
                // Configuration
                switch(Interrupt_Array[Local_Loop].Trigger_Mode){
                    case INT1_LowLevel:
                    MCUCR &= (~(1<<ISC10)) & (~(1<<ISC11));
                    break;
                    case INT1_LogicalChange:
                    MCUCR |= (1<<ISC10); 
                    break;
                    case INT1_FallingEdge:
                    MCUCR |= (1<<ISC11);
                    break;
                    case INT1_RisingEdge:
                    MCUCR |= (1<<ISC11);
                    MCUCR |= (1<<ISC10);
                    break;
                    default:
                    StateVar = NOK;
                    break;
                }
                // Enable Interrupt
                switch(Interrupt_Array[Local_Loop].State){
                    case Active:
                    GICR |= (1<<INT1_GICRBIT); 
                    SREG |= (1<<SREG_I); 
                    break;
                    case In_Active:

                    break;
                    default:
                    StateVar = NOK;
                    break;
                }
            }
            else if (Interrupt_Array[Local_Loop].Name == INT2) {
                // Pull Up Resistor
                PORTB |= (1<<INT2_PIN);
                // Configuration
                switch(Interrupt_Array[Local_Loop].Trigger_Mode){
                    case INT2_FallingEdge:
                    MCUCR &= (~(1<<ISC2));
                    break;
                    case INT2_RisingEdge:
                    MCUCR |= (1<<ISC2);
                    break;
                    default:
                    StateVar = NOK;
                    break;
                }
                // Enable Interrupt
                switch(Interrupt_Array[Local_Loop].State){
                    case Active:
                    GICR |= (1<<INT2_GICRBIT);
                    SREG |= (1<<SREG_I); 
                    break;
                    case In_Active:

                    break;
                    default:
                    StateVar = NOK;
                    break;
                }
            }
        }
    }

    else {
        StateVar = NOK;
    }

    return StateVar;
}


void INTP0_vidEnabled(void){
    uint8 Local_loop;
    for(Local_loop=0; Local_loop<Num_Of_Interrupt; Local_loop++){
        if (Interrupt_Array[Local_loop].Name == INT0){
            Interrupt_Array[Local_loop].State = Active;
        }
    }
    // Enable Global Interrupt control register and global interrupt
    GICR |= (1<<INT0_GICRBIT);
    SREG |= (1<<SREG_I); 
}

void INTP1_vidEnabled(void){
    uint8 Local_loop;
    for(Local_loop=0; Local_loop<Num_Of_Interrupt; Local_loop++){
        if (Interrupt_Array[Local_loop].Name == INT1){
            Interrupt_Array[Local_loop].State = Active;
        }
    }
    // Enable Global Interrupt control register and global interrupt
    GICR |= (1<<INT1_GICRBIT);
    SREG |= (1<<SREG_I); 
}

void INTP2_vidEnabled(void){
    uint8 Local_loop;
    for(Local_loop=0; Local_loop<Num_Of_Interrupt; Local_loop++){
        if (Interrupt_Array[Local_loop].Name == INT2){
            Interrupt_Array[Local_loop].State = Active;
        }
    }
    // Enable Global Interrupt control register and global interrupt
    GICR |= (1<<INT2_GICRBIT);
    SREG |= (1<<SREG_I); 
}

void INTP0_vidDisabled(void){
    uint8 Local_loop;
    for(Local_loop=0; Local_loop<Num_Of_Interrupt; Local_loop++){
        if (Interrupt_Array[Local_loop].Name == INT0){
            Interrupt_Array[Local_loop].State = In_Active;
        }
    }
    // Enable Global Interrupt control register and global interrupt
    GICR &= (~(1<<INT0_GICRBIT));
}
void INTP1_vidDisabled(void){
    uint8 Local_loop;
    for(Local_loop=0; Local_loop<Num_Of_Interrupt; Local_loop++){
        if (Interrupt_Array[Local_loop].Name == INT1){
            Interrupt_Array[Local_loop].State = In_Active;
        }
    }
    // Enable Global Interrupt control register and global interrupt
    GICR &= (~(1<<INT1_GICRBIT));
}
void INTP2_vidDisabled(void){
    uint8 Local_loop;
    for(Local_loop=0; Local_loop<Num_Of_Interrupt; Local_loop++){
        if (Interrupt_Array[Local_loop].Name == INT2){
            Interrupt_Array[Local_loop].State = In_Active;
        }
    }
    // Enable Global Interrupt control register and global interrupt
    GICR &= (~(1<<INT2_GICRBIT));
}

void INTP_VidDisableGlobal(void){
    SREG &= (~(1<<SREG_I));
}


void INTP0_VidSelectEvent(uint8 COPY_uint8EventState){
    uint8 Local_loop;
    for(Local_loop=0; Local_loop<Num_Of_Interrupt; Local_loop++){
        if (Interrupt_Array[Local_loop].Name == INT0){
            switch(COPY_uint8EventState){
                    case INT0_LowLevel:
                    MCUCR &= (~(1<<ISC00)) & (~(1<<ISC01));
                    break;
                    case INT0_LogicalChange:
					MCUCR &= (~(1<<ISC00)) & (~(1<<ISC01));
                    MCUCR |= (1<<ISC00); 
                    break;
                    case INT0_FallingEdge:
					MCUCR &= (~(1<<ISC00)) & (~(1<<ISC01));
                    MCUCR |= (1<<ISC01);
                    break;
                    case INT0_RisingEdge:
					MCUCR &= (~(1<<ISC00)) & (~(1<<ISC01));
                    MCUCR |= (1<<ISC01);
                    MCUCR |= (1<<ISC00);
                    break;
                    default:
                    break;
                }
        }
    }
}
void INTP1_VidSelectEvent(uint8 COPY_uint8EventState){
    uint8 Local_loop;
    for(Local_loop=0; Local_loop<Num_Of_Interrupt; Local_loop++){
        if (Interrupt_Array[Local_loop].Name == INT1){

            switch(COPY_uint8EventState){
                    case INT1_LowLevel:
                    MCUCR &= (~(1<<ISC10)) & (~(1<<ISC11));
                    break;
                    case INT1_LogicalChange:
                    MCUCR |= (1<<ISC10); 
                    break;
                    case INT1_FallingEdge:
                    MCUCR |= (1<<ISC11);
                    break;
                    case INT1_RisingEdge:
                    MCUCR |= (1<<ISC11);
                    MCUCR |= (1<<ISC10);
                    break;
                    default:
                    break;
            }
        }
    }
}

void INTP2_VidSelectEvent(uint8 COPY_uint8EventState){
    uint8 Local_loop;
    for(Local_loop=0; Local_loop<Num_Of_Interrupt; Local_loop++){
        if (Interrupt_Array[Local_loop].Name == INT2){
            switch(COPY_uint8EventState){
                    case INT2_FallingEdge:
                    MCUCR &= (~(1<<ISC2));
                    break;
                    case INT2_RisingEdge:
                    MCUCR |= (1<<ISC2);
                    break;
                    default:
                    break;
                }
        }
    }
}

void INTP0_vidSetCallBack(void(*COPY_pvidCallBackFunction)(void))
{  
    Ptr_INT0 = COPY_pvidCallBackFunction;
}
void INTP1_vidSetCallBack(void(*COPY_pvidCallBackFunction)(void))
{
    Ptr_INT1 = COPY_pvidCallBackFunction;
}
void INTP2_vidSetCallBack(void(*COPY_pvidCallBackFunction)(void))
{
    Ptr_INT2 = COPY_pvidCallBackFunction;
}

ISR(INT0_vect){
    Ptr_INT0();
}

ISR(INT1_vect){
    Ptr_INT1();
}

ISR(INT2_vect){
    Ptr_INT2();
}