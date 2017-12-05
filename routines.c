/*
 * routines.c
 *
 *  Created on: 05.12.2017
 *      Author: Max
 */


#include "routines.h"

void TIMER_carrierFreq_init(void)
{
	//Output Low
	PORTB &= ~(1 << PB7);
	DDRB |= (1 << PB7);

	cli();						//Disable all interrupts

	TCCR1B |= (1 << CS10);		//No prescaling
	//TCCR1B |= (1 << CS11); 	//8 - prescaler

	TCCR1A |= (1 << COM1C0);	//Toggle OC1A on compare match

	OCR1A = 210;				//Set TOP to 210

	TIMSK1 |= (1 << OCIE1A);	//Enable interrupt on Timer 1

	sei();						//Enable all interrupts
}


ISR(TIMER1_COMPA_vect)
{
	//PINB |= (1 << PB7);
	PORTB ^= (1 << PB7);
}
