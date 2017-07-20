/*
 * File:   Timer0.h
 * Author: Asafe
 *
 * Created on 10 de Junho de 2017, 18:13
 */

#ifndef TIMER0_H
#define	TIMER0_H

#include <xc.h>

// Time overflow --> 200ms
#define TMR0_RESET 16
#define TMR0_COUNTER 13

void configTMR0();
void timer0Interrupt();


#endif	/* TIMER0_H */