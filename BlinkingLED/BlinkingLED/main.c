/*
 * BlinkingLED.c
 *
 * Created: 05.11.2018 9:16:25
 * Author : st57506
 */

 #define F_CPU 20000000UL
 #include <avr/io.h>
 #include <util/delay.h>


 int main(void)
 {
	 DDRC  = 0b11111111;		//port C as output
	 PORTC = 0b11111110;		//LED 0 is ON
	 while (1)
	 {
		_delay_ms(100);		//delay 100ms
		PORTC = PORTC^0b00000001;	//negate 0, XOR PORTC, blinking the led 0
	 }
 }


