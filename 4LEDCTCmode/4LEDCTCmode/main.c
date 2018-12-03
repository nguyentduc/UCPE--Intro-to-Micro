/*
 * 4LEDCTCmode.c
 *
 * Created: 03.12.2018 9:11:53
 * Author : st57506
 * Display 1234 on the 4 7segmentLED using CTC mode interrupt
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h> 

volatile uint8_t digits[4] ={1,2,3,4};	//volatile = global variable

int main(void)
{
    DDRC = 0b11111111;	//output

	TCCR0A = 0b00000010;	//CTC mode
	TCCR0B = 0b00000100;	//P=256
	OCR0A = 155;
	TIMSK0 = 0b00000010;	//CTC interrupt is enabled
	sei();					//IS is enabled

    while (1) 
    {
    }

}

ISR(TIMER0_COMPA_vect)
{
	uint8_t orders[4] = {	0b11100000,	//thousandth position
							0b11010000,	// hundredth position
							0b10110000,	//tenth position
							0b01110000 };

	static uint8_t activeOrder = 0;
	PORTC = orders[activeOrder] + digits[activeOrder];	//OR
	
	activeOrder++;
	if(activeOrder==4)
		activeOrder=0; 
}
