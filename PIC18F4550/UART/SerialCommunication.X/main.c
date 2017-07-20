/*
 * File:   main.c
 * Author: Asafe
 *
 * Created on 20 de Julho de 2017, 00:24
 */

#include "_config.h"
#include <xc.h>

#include "Serial.h"

void main(void) {
    
    ADCON1 = 0x0F;                                                              // Configures ANx pins as digital
    
    // == Set up Serial Communication with ~38400 baud rate == //
    SerialBegin();
    
    // Enables Global Interrupts 
    INTCONbits.GIE = 1;
    
    
    println_string("Testando USART!");
    
    while(1){
    }
    
    return;
}

void interrupt Interrupt(){
    
    // Checks USART Receive
    if(PIR1bits.RCIF){
        PIR1bits.RCIF = 0;    

        char receive;
        if(SerialRead(&receive)){
            print_char(receive); 
        }
    }
    
}
