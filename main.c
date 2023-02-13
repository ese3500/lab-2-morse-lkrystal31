
#define F_CPU 16000000UL
#define BAUD_RATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)
#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>

#include "inc/uart.h"

volatile int pulse_width;
volatile int prior_width;
volatile int spaces;
volatile int morse_length;

volatile int time1 = 0;
volatile int time2 = 0;
char String[25];
char Print[25];

void Initialize()
{
	cli();
	UART_init(BAUD_PRESCALER);
	// prescale tccr1b and timer overflow interrupt for timsk1
	
	DDRB |= (1<<DDB1); // set output pins
	DDRB |= (1<<DDB2);
	DDRB &= ~(1<<DDB0); // input pin b0 needs to detect pin change and call interrupt icp1
	DDRB &= ~(1<<PORTB1) // set output pin b5 to low
	DDRB &= ~(1<<PORTB2)
	
	TCCR1B |= (1 <<ICES1); // capture rising edge
	TIMSK1 |= (1<<ICIE1); // enable interrupt here enables input capture on timer 1)
	TIMSK1 |= (1<<OCIE1A); //enable overflow interrupt
	
	TCCR1B &= ~(1<<CS10); //set prescalar 256
	TCCR1B &= ~(1<<CS11);
	TCCR1B |= (1<<CS12);
	//30 -200, 200-400, >400
	
	
	TIFR1 |= (1<<ICF1); // clear input capture flag
	sei() // enable global interrupts
}

int main void() {
	Initialize();
	while(1) {
		if (pulse_width != prior_width) {
			if (pulse_width >= 1875 && pulse_width < 12500) { // 16e16 / 256 * 0.03 or 0.2 or .4
				PORTB |= (1<<PORTB1);
				_delay_ms(200);
				PORTB &= ~(1<<PORTB1);
				String[morse_length] = '.';
				morse_length++;
			}
			else if(pulse_width >= 12500 && pulse_width < 25000) {
				PORTB |= (1<<PORTB2);
				_delay_ms(200);
				PORTB &= ~(1<<PORTB2);
				String[morse_length]='-';
				morse_length++;
			}
			prior_width = pulse_width;
			count=0;
		}
		if (TCNT1 - time2 >= 62500 && count==0) {
			count =1;
			morse_to_char();
		}
	}
}

ISR(TIMER1_CAPT_vect) {
	if (TCCR1B & (1<<ICES1)) { //rising edge (button pressed)
		time1 = TCNT1;
	}
	else {
		time2 = TCNT1;
		if (time2>=time1) {
			pulse_width = time2 - time1;
			} else {
			pulse_width = time2 - time1 + 65536;
		}
	}
	TIFR1 |= (1<<ICF1); // clear input capture flag
	TCCR1B ^= (1<<ICES1); // toggle port
}

void morse_to_char() {

	if (strcmp(String, "._") == 0) {
		sprintf(Print,"A");
		UART_putstring(Print);
	}
	else if (strcmp(String, "_...") == 0) {
		sprintf(Print, "B");
		UART_putstring(Print);
	}
	else if (strcmp(String, "_._.") == 0) {
		sprintf(Print, "C");
		UART_putstring(Print);
	}
	else if (strcmp(String, "_..") == 0) {
		sprintf(Print, "D");
		UART_putstring(Print);
	}
	else if (strcmp(String, ".") == 0) {
		sprintf(Print, "E");
		UART_putstring(Print);
	}
	else if (strcmp(String, ".._.") == 0) {
		sprintf(Print, "F");
		UART_putstring(Print);
	}
	else if (strcmp(String, "__.") == 0) {
		sprintf(Print, "G");
		UART_putstring(Print);
	}
	else if (strcmp(String, "....") == 0) {
		sprintf(Print, "H");
		UART_putstring(Print);
	}
	else if (strcmp(String, "..") == 0) {
		sprintf(Print, "I");
		UART_putstring(Print);
	}
	else if (strcmp(String, ".___") == 0) {
		sprintf(Print, "J");
		UART_putstring(Print);
	}
	else if (strcmp(String, "_._") == 0) {
		sprintf(Print, "K");
		UART_putstring(Print);
	}
	else if (strcmp(String, "._..") == 0) {
		sprintf(Print, "L");
		UART_putstring(Print);
	}
	else if (strcmp(String, "__") == 0) {
		sprintf(Print, "M");
		UART_putstring(Print);
	}
	else if (strcmp(String, "_.") == 0) {
		sprintf(Print, "N");
		UART_putstring(Print);
	}
	else if (strcmp(String, "___") == 0) {
		sprintf(Print, "O");
		UART_putstring(Print);
	}
	else if (strcmp(String, ".__.") == 0) {
		sprintf(Print, "P");
		UART_putstring(Print);
	}
	else if (strcmp(String, "__._") == 0) {
		sprintf(Print, "Q");
		UART_putstring(Print);
	}
	else if (strcmp(String, "._.") == 0) {
		sprintf(Print, "R");
		UART_putstring(Print);
	}
	else if (strcmp(String, "...") == 0) {
		sprintf(Print, "S");
		UART_putstring(Print);
	}
	else if (strcmp(String, "_") == 0) {
		sprintf(Print, "T");
		UART_putstring(Print);
	}
	else if (strcmp(String, ".._") == 0) {
		sprintf(Print, "U");
		UART_putstring(Print);
	}
	else if (strcmp(String, "..._") == 0) {
		sprintf(Print, "V");
		UART_putstring(Print);
	}
	else if (strcmp(String, ".__") == 0) {
		sprintf(Print, "W");
		UART_putstring(Print);
	}
	else if (strcmp(String, "_.._") == 0) {
		sprintf(Print, "X");
		UART_putstring(Print);
	}
	else if (strcmp(String, "_.__") == 0) {
		sprintf(Print, "Y");
		UART_putstring(Print);
	}
	else if (strcmp(String, "__..") == 0) {
		sprintf(Print, "Z");
		UART_putstring(Print);
	}
	else if (strcmp(String, ".____") == 0) {
		sprintf(Print, "1");
		UART_putstring(Print);
	}
	else if (strcmp(String, "..___") == 0) {
		sprintf(Print, "2");
		UART_putstring(Print);
	}
	else if (strcmp(String, "...__") == 0) {
		sprintf(Print, "3");
		UART_putstring(Print);
	}
	else if (strcmp(String, "...._") == 0) {
		sprintf(Print, "4");
		UART_putstring(Print);
	}
	else if (strcmp(String, ".....") == 0) {
		sprintf(Print, "5");
		UART_putstring(Print);
	}
	else if (strcmp(String, "_....") == 0) {
		sprintf(Print, "6");
		UART_putstring(Print);
	}
	else if (strcmp(String, "__...") == 0) {
		sprintf(Print, "7");
		UART_putstring(Print);
	}
	else if (strcmp(String, "___..") == 0) {
		sprintf(Print, "8");
		UART_putstring(Print);
	}
	else if (strcmp(String, "____.") == 0) {
		sprintf(Print, "9");
		UART_putstring(Print);
	}
	else if (strcmp(String, "_____") == 0) {
		sprintf(Print, "0");
		UART_putstring(Print);
	}
	for (int i = 0; i < 25; i++) {
		String[i] = '\0';
		morse_length = 0;
	}

}
//ISR(TIMER1_OVF_vect) {
//overflow++;
//TCCR1B ^= (1<<ICES1); //clear input capture
//}