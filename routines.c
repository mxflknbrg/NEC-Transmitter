/*
 * routines.c
 *
 *  Created on: 05.12.2017
 *      Author: Max
 */


#include "routines.h"



static volatile uint8_t flag_pulse = 0;
static volatile uint8_t flag_pause = 0;
static volatile uint8_t cnt_pulse = 0;
static volatile uint8_t cnt_pause = 0;

void TIMER_carrierFreq_init(void)
{
	//Output Low
	PORTB &= ~(1 << PB7);
	DDRB |= (1 << PB7);

	cli();						//Disable all interrupts

#if (PRESCALER == 0)
	TCCR1B |= (1 << CS10);						//No prescaling
#elif (PRESCALER == 8)
	TCCR1B |= (1 << CS11);						//8 - prescaler
#elif (PRESCALER == 64)
	TCCR1B |= (1 << CS11) | (1 << CS10); 		//64 - prescaler
#elif (PRESCALER == 256)
	TCCR1B |= (1 << CS12);						//256 - prescaler
#elif (PRESCALER == 1024)
	TCCR1B |= (1 << CS12) | (1 << CS10);		//1024 - prescaler
#else
#warning "No prescaler selected"
#endif

	TCCR1B |= (1 << WGM12);		//CTC mode, TOP_val -> OCR

	OCR1A = OCR_VAL;			//Set OCR

	TIMSK1 |= (1 << OCIE1A);	//Enable interrupt on Timer 1

	sei();						//Enable all interrupts
}


ISR(TIMER1_COMPA_vect)
{
	//PINB |= (1 << PB7);


	if(flag_pulse)
	{
		PINB |= (1 << PB7);
		//PORTB ^= (1 << PB7);
		cnt_pulse++;
		flag_pulse = 0;
	}
	if(flag_pause)
	{
		PORTB &= ~(1 << PB7);
		cnt_pause++;
		flag_pause = 0;
	}

}


static inline void generate_one()
{
	while(cnt_pulse < TICKS_PULSE)
	{
		flag_pulse = 1;
	}
	while(cnt_pause < TICKS_1_PAUSE)
	{
		flag_pause = 1;
	}
}

static inline void generate_zero()
{
	while(cnt_pulse < TICKS_PULSE)
	{
		flag_pulse = 1;
	}
	while(cnt_pause < TICKS_0_PAUSE)
	{
		flag_pause = 1;
	}
}


void command_hex(uint8_t command)
{
	uint8_t val = 0x80;
	for(uint8_t i = 0; i < 8; i ++)
	{
		if(command & val)
		{
			generate_one();
		}
		else
		{
			generate_zero();
		}
		val = val >> 1;
	}
}
