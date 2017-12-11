/*
 * main.c
 *
 *  Created on: 05.12.2017
 *      Author: Max
 */


#include "routines.h"

int main(void)
{
	TIMER_carrierFreq_init();

	cli();
	PORTB &= ~(1 << PB7);
	_delay_ms(2000);
	PORTB |= (1 << PB7);
	_delay_ms(1000);
	sei();

	NEC_out(0x41);

	cli();
	PORTB &= ~(1 << PB7);
	_delay_ms(2000);
	PORTB |= (1 << PB7);
	_delay_ms(1000);
	sei();


	while(1)
	{
		__asm("NOP");
	}
	return 0;
}
