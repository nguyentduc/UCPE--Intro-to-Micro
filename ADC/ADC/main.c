/*
 * ADC.c
 *
 * Created: 03.12.2018 9:34:55
 * Author : st57506
 * 
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h> 

volatile uint8_t digits[4] ={1,2,3,4};	//volatile = global variable

int main(void)
{
    uint16_t result;
	
	DDRC = 0b11111111;	//output

	TCCR0A = 0b00000010;	//CTC mode
	TCCR0B = 0b00000100;	//P=256
	OCR0A = 155;
	TIMSK0 = 0b00000010;	//CTC interrupt is enabled
	sei();					//IS is enabled

    ADMUX = 0b11000000;		//interval ref. voltage 2.56V, ADC0 channel
	ADCSRA = 0b10000111;	//P=128
	
	while (1) 
    {
		ADCSRA = ADCSRA|(1<<ADSC);	//ADSC =1 >> start of conversion

		while(ADCSRA&(1<<ADSC));	//waiting to end conversion

		result = ADC;				//storing of result

		digits[0] = result/1000;
		result = result%1000;
		digits[1] = result/100;
		result = result%100;
		digits[2] = result/10;
		result = result%10;
		digits[3] = result;
		//result = result;
    }

}

ISR(TIMER0_COMPA_vect)
{
	uint8_t orders[4] = {	0b11100000,	//thousandth position
							0b11010000,	//hundredth position
							0b10110000,	//tenth position
							0b01110000 };

	static uint8_t activeOrder = 0;
	PORTC = orders[activeOrder] + digits[activeOrder];	
	
	activeOrder++;
	if(activeOrder==4)
		activeOrder=0; 
}
