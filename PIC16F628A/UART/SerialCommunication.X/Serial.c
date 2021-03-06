/* 
 * File:   Serial.c
 * Author: Asafe
 *
 * Created on 24 de Junho de 2017, 22:00
 */

#include <stdlib.h>
#include <stdbool.h>

#include "Serial.h"
#include <xc.h>

void SerialBegin(){
    // Sets up USART (8 bits, none parity, 1 stop bit, ~38400 baud rate, asynchronous mode)  
    SPBRG = 25;            // ~38400 Baud Rate 
    
    TXSTAbits.BRGH = 1;     // High Baud Rate
    TXSTAbits.SYNC = 0;     // UART in asynchronous mode
    TXSTAbits.TXEN = 1;     // Enables trasmition
    
    RCSTAbits.SPEN = 1;     // Enables Serial Port
    RCSTAbits.CREN = 1;     // Enables continuous receive
    
    INTCONbits.PEIE = 1;    // Enables Peripheral Interrupts
    
    PIR1bits.RCIF = 0;      // Clear receive interrupt flag 
    PIE1bits.RCIE = 1;      // Enables the USART receive interrupt
    
    TRISBbits.TRISB1 = 1;   // Sets RX pin as INPUT
    TRISBbits.TRISB2 = 0;   // Sets TX pin as OUTPUT
    
    ei();                   // Enables Global Interrupts
}

void print_string(char word[]){
    for(int i = 0; word[i] != '\0' ; i++){
        TXREG = word[i];
        while(!TXSTAbits.TRMT);
    } 
}

void println_string(char word[]){
    for(int i = 0; word[i] != '\0' ; i++){
        TXREG = word[i];
        while(!TXSTAbits.TRMT);
    } 
    TXREG = '\r';
    while(!TXSTAbits.TRMT);
    TXREG = '\n';
    while(!TXSTAbits.TRMT);
}

void print_char(char word){
    TXREG = word;
    while(!TXSTAbits.TRMT);
}

void println_char(char word){
    TXREG = word;
    while(!TXSTAbits.TRMT);
    TXREG = '\r';
    while(!TXSTAbits.TRMT);
    TXREG = '\n';
    while(!TXSTAbits.TRMT);
}

bool SerialRead(char* receive){
    if(RCSTAbits.FERR || RCSTAbits.OERR){                                       // Checks if any errors ocurred
            RCSTAbits.CREN = 0;
            RCSTAbits.CREN = 1;
            
            return false;
    }
    
    *receive = RCREG;
    
    return true;
}
