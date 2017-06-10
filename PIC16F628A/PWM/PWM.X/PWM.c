/*
 * File:   PWM.c
 * Author: Asafe
 *
 * Created on 9 de Junho de 2017, 23:07
 */


#include "hardware.h"
#include <xc.h>

#include "PWM.h"

void main(void) {
    
    // Set up registers for PWM generation (~23.44 KHz, PWM_DUTY range [0, 255])
    configPWM();

    while(1){
        __delay_ms(100);
        PWM_DUTY++;
    }   
    
    return;
}
