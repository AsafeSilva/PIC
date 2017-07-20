/* 
 * File:   Timer0.c
 * Author: Asafe
 *
 * Created on 10 de Junho de 2017, 18:16
 */

#include "Timer0.h"

short timer0Counter = 0;

void configTMR0(){

    // INTCON Register        
    TMR0IE = 1;                                                                 // Enables the TMR0 overflow interrupt
    
    // INTCON2 Register
    TMR0IP = 0;                                                                 // Sets Low Priority in Timer0
    
    // T0CON Register
    TMR0ON = 0;                                                                 // Stops Timer0
    T08BIT = 1;                                                                 // Timer0 is configured as 8-bit timer/counter
    T0CS = 0;                                                                   // Internal instrucion cycle clock (Clock Source)               
    PSA = 0;                                                                    // Prescaler assigned to the Timer0 module
    T0PS2 = 1;                                                                  // Prescaler -> 1:256
    T0PS1 = 1;
    T0PS0 = 1;
    TMR0L = TMR0_RESET;                                                         // Load value in TMR0L
    TMR0ON = 1;                                                                 // Start Timer0    
    
//    ei();                                                                       // Enables Global Interrupts
}

void timer0Interrupt(){
    if(TMR0IF){
        // overflow = (4 * TMR0_prescaler * (256 - TMR0)) / Fosc
        
        if(timer0Counter == TMR0_COUNTER){
            timer0Counter = 0;
            
            // Code Here!
            RD7 = ~RD7;
        }
        
        TMR0L = TMR0_RESET;                                                     // Load value in TMR0L
        TMR0IF = 0;
        timer0Counter++;
    }

    
}