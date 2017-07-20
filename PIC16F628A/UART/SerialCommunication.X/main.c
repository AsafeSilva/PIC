/*
 * File:   main.c
 * Author: Asafe
 *
 * Created on 16 de Junho de 2017, 20:57
 */

#include "hardware.h"
#include <xc.h>

#include "Serial.h"

void main(void) {
    
    SerialBegin();
    
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
