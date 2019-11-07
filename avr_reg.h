/*
 * avr_reg.h
 *
 *  Created on: Sep 20, 2019
 *      Author: abdelqader
 */

#ifndef AVR_REG_H_
#define AVR_REG_H_

#define NULL ((void *)0)


/* Group A Registers */
#define PORTA  *((volatile uint8*)0x3B)
#define DDRA   *((volatile uint8*)0x3A)
#define PINA   *((volatile uint8*)0x39)

/* Group B Registers */
#define PORTB  *((volatile uint8*)0x38)
#define DDRB   *((volatile uint8*)0x37)
#define PINB   *((volatile uint8*)0x36)

/* Group C Registers */
#define PORTC *((volatile uint8*)0x35)
#define DDRC   *((volatile uint8*)0x34)
#define PINC  *((volatile uint8*)0x33)

/* Group D Registers */
#define PORTD *((volatile uint8*)0x32)
#define DDRD  *((volatile uint8*)0x31)
#define PIND  *((volatile uint8*)0x30)

/* SREG Register */
#define SREG  *((volatile uint8*)0x5F)

//Timer control Register address for timer 1 channel A
#define TCCR1A (*(( volatile uint8*)0x4F))
//Timer control Register address for timer 1 channel B
#define TCCR1B (*(( volatile uint8*)0x4E))
//Timer1 registers address Timer/Counter1 – TCNT1H and TCNT1L
#define TCNT1L (*(( volatile uint16*)0x4C))
//Output Compare Register 1 A – OCR1AH and OCR1AL
#define OCR1AL (*(( volatile uint16*)0x4A))
//Output Compare Register 1 B– OCR1BH and OCR1BL
#define OCR1BL (*(( volatile uint16*)0x48))
//Input Capture Register 1 –ICR1H and ICR1L
#define ICR1L (*(( volatile uint16*)0x46))
//Timer control Register address for timer 0
#define TCCR0 (*(( volatile uint8*)0x53))
//Timer registers address
#define TCNT0 (*(( volatile uint8*)0x52))
//Output Compare Register address
#define OCR0 (*(( volatile uint8*)0x5C))
//Timer/Counter Interrupt Mask Register – TIMSK
#define TIMSK (*(( volatile uint8*)0x59))
//Timer/Counter Interrupt Flag Register – TIFR
#define TIFR (*(( volatile uint8*)0x58))
//Timer control Register address for timer 2
#define TCCR2 (*(( volatile uint8*)0x45))
//Timer registers address
#define TCNT2 (*(( volatile uint8*)0x44))
//Output Compare Register address
#define OCR2 (*(( volatile uint8*)0x43))
//to enable the Global Interrupt Flag pin
#define SREG_I 7

//ADDRESS OF GICR "GLOBAL INTERRUPT CONTROL REGISTER"
#define GICR_ADDRESS 0x5B
#define GICR (*(volatile uint8 *) GICR_ADDRESS)

//ADDRESS OF MCUCR "MCU CONTROL REGISTER"
#define MCUCR_ADDRESS 0x55
#define MCUCR (*(volatile uint8 *) MCUCR_ADDRESS)

//ADDRESS OF MCUCSR "MCU CONTROL SENSE REGISTER"
#define MCUCSR_ADDRESS 0x54
#define MCUCSR (*(volatile uint8 *) MCUCSR_ADDRESS)

#endif /* AVR_REG_H_ */
