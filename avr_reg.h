#ifndef AVR_REG_H_
#define AVR_REG_H_

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



#endif /* AVR_REG_H_ */