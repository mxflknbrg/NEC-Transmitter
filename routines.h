/*
 * routines.h
 *
 *  Created on: 05.12.2017
 *      Author: Max
 */

#ifndef ROUTINES_H_
#define ROUTINES_H_

#include "stdio.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>


#define PRESCALER 		1024			//				f_cpu
										//	f = ----------------------
#define OCR_VAL			3125			//			OCR   *   p

#define COMP_OUT_MODE	0				//	0 = normal, 1 = toggle


#define TICKS_PULSE			21
#define TICKS_1_PAUSE		64
#define TICKS_0_PAUSE		21




void TIMER_carrierFreq_init(void);

void NEC_out(uint8_t command_hex);

#endif /* ROUTINES_H_ */
