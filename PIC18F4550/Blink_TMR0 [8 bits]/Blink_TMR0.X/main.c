/*
 * File:   main.c
 * Author: Asafe
 *
 * Created on 20 de Julho de 2017, 00:59
 */

#include "_config.h"
#include <xc.h>

#include "Timer0.h"

void main(void) {
    
    // == Set up registers for Timer0 interrupt == //
    configTMR0();
    
    // ======= Pin configuration ======= //
    ADCON1 = 0x0F;                                                              // Configures ANx pins as digital
    
    TRISD7 = 0;                                                                 // RD7 as OUTPUT (Test Timer0)
    RD7 = 0;                                                                    // Begin RD7 in LOW
    // ======= End Pin configuration ======= //
    
    // Enables Global Interrupts 
    INTCONbits.GIE = 1;
    
    while(1){}
    
    return;
}

void interrupt Interrupt(){
    // Check Timer0 interrupt
    timer0Interrupt();
}
