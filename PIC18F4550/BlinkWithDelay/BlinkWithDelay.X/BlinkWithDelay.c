/*
 * File:   main.c
 * Author: Asafe
 *
 * Created on 5 de Julho de 2017, 14:03
 */


#include "_config.h"
#include <xc.h>

void main(void) {
    
    ADCON1 = 0x0F;                              // Configures ANx pins as digital
    
    TRISDbits.TRISD7 = 0;                       // RD7 as OUTPUT
    RD7 = 0;                                    // Begin RD7 in LOW
    
    while(1){
        RD7 = ~RD7;
        __delay_ms(500);
    }
    
    return;
}
