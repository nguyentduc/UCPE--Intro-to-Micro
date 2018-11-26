/*
 * 7segment_led.c
 *
 * Created: 12.11.2018 9:08:05
 * Author : st57506
 */ 
 // Diplay 0 to F on 7 segment LED
 
#define F_CPU 20000000UL // 2Mhz
#include <util/delay.h>
#include <avr/io.h>
#include <stdint.h>

void display_led(uint8_t input) //unsigned 8bit integer 
{
	const uint8_t led[16]={
		0b00000011,	//0
		0b10011111,	//1
		0b00100101,	//2
		0b00001101,	//3
		0b10011001,	//4
		0b01001001,	//5
		0b01000001,	//6
		0b00011111,	//7
		0b00000001,	//8
		0b00001001,	//9
		0b00010001,	//a
		0b11000001,	//b
		0b01100011,	//c
		0b10000101,	//d
		0b01100001,	//e
		0b01110001,	//f
	};

	PORTC = led[input];
}

void init()
{
	DDRC = 0b11111111;	// all pin PORTC is output
	PORTC =0b11111111;	//	all LED off
}
int main(void)
{
	uint8_t count;
	init();
	while(1)
	{
		for(count=0; count<16; count++)
		{
			display_led(count);
			_delay_ms(500);
		}
	}   
}

