#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>


void Initialize()
{
	cli(); //disable interrupts
	
	// read if button pressed or released
	DDRB |= (1<<DDB5); // set output pin b5
	DDRB &= ~(1<<DDB0); // input pin b0 needs to detect pin change and call interrupt icp1

	//TCCR1B |= 0x05; // enable clock, 1024
	
	TCCR1B |= (1 << ICES1); // capture rising edge
	
	TIFR1 |= (1<<ICF1); // clear input capture flag
	TIMSK1 |= (1<<ICIE1); // enable interrupt here enables input capture on timer 1
	
	sei();
}


int main(void)
{
	Initialize();
	while(1);
}

ISR(TIMER1_CAPT_vect)
{
	TIFR1 |= (1<<ICF1); // clear input capture flag by storing 1 to icf1 bit
	PORTB ^= (1<<PORTB5); // toggle port
	// look for falling edge now
	TCCR1B ^= (1 << ICES1);
}
