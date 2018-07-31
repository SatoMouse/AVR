#define F_CPU 1600000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define OFF_POS 8
#define ON_POS 10
//-90°  4
// 90° 10

ISR(PCINT0_vect){
	OCR0B = ON_POS;
	_delay_ms(600);
	GIFR |= 0<<5;
	OCR0B = OFF_POS;
	_delay_ms(600);
	OCR0B = 0;
}

int main(void)
{
	DDRB |= (0 << PINB4) | (1 << PINB1);
	
	GIMSK |= (1 << 5);
	PCMSK = 0x10;

	TCCR0A |= 1<<WGM01 | 1<<WGM00 | 1<<COM0B1;
	TCCR0B |= 1<<WGM02 | 1<<CS02;// 分周比256
	OCR0A = 93; // 1.2MHz/50Hz/256-1=94 - 1 = 93
	
	OCR0B = OFF_POS;
	_delay_ms(600);
	OCR0B = 0;
	
	sei();

	while (1){}
}

