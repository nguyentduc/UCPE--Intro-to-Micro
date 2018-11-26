/*
 * CounterCTCmode.c
 *
 * Created: 26.11.2018 9:35:15
 * Author : st57506
 */ 

//Blinking led any 0.5s using CTC mode counter. 

#include <avr/io.h>
#include <avr/interrupt.h>	
#include <stdint.h>


int main(void)
{
    DDRC = 0b11111111;		//port C as output
	PORTC = 0b11111111;		//All LED is off
	TCCR0A = 0b00000010;	//CTC mode counter
	TCCR0B = 0b00000011;	//CTC mode, P=64
	OCR0A = 249;			//OCRR0A = 249+1
	TIMSK0 = 0b00000010;	//CTC mode with OCR0A is enabled
	sei();					//I=1 (Interupt service is enabled)

    while (1) 
    {
    }
}

//Interupt Service routine
ISR(TIMER0_COMPA_vect)
{
	static uint16_t counter=625;
	counter--;

	if(counter==0)		//interval 500ms in measured
	{
		PORTC = PORTC^0b00000001; //negotaion of PC0
		counter = 625;
	}
}