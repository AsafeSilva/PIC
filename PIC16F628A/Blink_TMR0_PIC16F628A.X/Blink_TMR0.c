/*
 * File:   Blink_TMR0.c
 * Author: Asafe
 *
 * Created on 5 de Junho de 2017, 00:02
 */

#include <xc.h>
#include "hardware.h"


char counter = 0;

void interrupt Interrupt(){
    
//    overflow = ciclo de máquina * prescaler * contagem ( 256 - TMR0 )
//    overflow = 0.25us * 256 * 256 = 0,016384s
    
    if(INTCONbits.T0IF){
        
        // Change RB0 state every 0.5 seconds (32 * overflow) (~1 Hz)
        if(counter == 32){
            counter = 0;
            RB0 = ~RB0;
        }
        
        TMR0 = 0;
        INTCONbits.T0IF = 0;
        counter++;
    }
    
}

void main() {
    
    // CONFIG TIMER 0
    INTCONbits.GIE  = 1;        // Global Interrupt Enable bit
    INTCONbits.T0IE = 1;        // TMR0 Overflow Interrupt Enable bit
    INTCONbits.T0IF = 1;        // TMR0 Overflow Interrupt Flag bit
    OPTION_REGbits.T0CS = 0;    // TMR0 Clock Source Select bit (internal clock)
    OPTION_REGbits.PSA  = 0;    // Prescaler to the Timer0
    OPTION_REGbits.PS   = 7;    // Prescaler -> 1:256
    TMR0 = 0;
    
    TRISBbits.TRISB0 = 0x00;
    RB0 = 0x00;   
    
    while(1){
    }
    
}
