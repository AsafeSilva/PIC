/*
 * File:   main.c
 * Author: Marcos
 *
 * Created on 20 de Julho de 2017, 00:52
 */

#include "_config.h"
#include <xc.h>

#include "PWM.h"

void main(void) {
    
    // == Set up registers for PWM generation (PWM_DUTY range [0, 255]) == //
    configPWM();
    
    ADCON1 = 0x0F; 
    
    while(1){
        __delay_ms(100);
        PWM_DUTY++;
    }
    return;
}
