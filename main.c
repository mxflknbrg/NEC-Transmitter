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


	while(1)
	{
		__asm("NOP");
	}
		return 0;
}
