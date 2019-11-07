#ifndef TIMER_H_
#define TIMER_H_

#include "STD_Types.h"
#include "avr_reg.h"
#include "timer_conf.h"

#define ISR(vector, ...)            \
    void vector (void) __attribute__ ((signal,__INTR_ATTRS)) __VA_ARGS__; \
    void vector (void)

#define SIGNAL(vector)					\
    void vector (void) __attribute__ ((signal, __INTR_ATTRS));		\
    void vector (void)

#define _VECTOR(N) __vector_ ## N


#define TIMER0_OV		_VECTOR(11)
#define	TIMER0_COMP		_VECTOR(10)
#define TIMER2_COMP		_VECTOR(4)
#define TIMER2_OV		_VECTOR(5)
#define TIMER1_OV		_VECTOR(9)
#define TIMER1_COMPB	_VECTOR(8)
#define TIMER1_COMPA	_VECTOR(7)



STD_Fun_t TIMER_Init (uint8 TimerSpecs);
STD_Fun_t TIMER_Start (uint8 TimerName, uint8 Prescaler_Conf);
STD_Fun_t TIMER_Stop (uint8 TimerName);

void TIMER0_SetOV(void (*Ptr_ISR) (void));
void TIMER0_SetCM(void (*Ptr_ISR) (void));

void TIMER2_SetOV(void (*Ptr_ISR) (void));
void TIMER2_SetCM(void (*Ptr_ISR) (void));

void TIMER1_SetOV(void (*Ptr_ISR) (void));
void TIMER1_SetCM(void (*Ptr_ISR) (void));


#endif /* TIMER_H_*/
