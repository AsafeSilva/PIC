/*
 * File:   main.c
 * Author: Asafe dos Santos - Técnico em Mecatrônica
 * 
 * Projeto de um "Medidor" de tensão, utilizando o PIC16F628A,
 * TLC549 (ADC Serial) e um display de 7 segmentos (3 dígitos)
 *
 * Created on 8 de Junho de 2016, 18:16
 */


#include <xc.h>

// CONFIG
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSC oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is digital input, MCLR internally tied to VDD)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// CONFIG DELAYS
#define CLOCK 4000000
#define delay_ms(x) _delay((unsigned long)x * CLOCK / 4000)
#define delay_us(x) _delay((unsigned long)x * CLOCK / 4000000)

#define pinCS    RA0
#define pinCLK   RA1
#define pinDATA  RA2
#define PORTDISP PORTB
#define dispUni  RA3
#define dispDez  RA6
#define dispCen  RA7

#define time 100

char uni, dez, cen;
char counter = 0;
char controle = 1;

// Protótipo das funções do ADC
char readSerial();
float averageADC(char qnt);
float readADC();

       
float value;

void interrupt Interrupt(){ 
    int number;
    int segments[10] = {
        0x3f,  //0 -> a,b,c,d,e,f
        0x06,  //1 -> b,c
        0x5b,  //2 -> a,b,d,e,g
        0x4f,  //3 -> a,b,c,d,g
        0x66,  //4 -> b,c,f,g
        0x6d,  //5 -> a,c,,d,f,g
        0x7d,  //6 -> a,c,d,e,f,g
        0x07,  //7 -> a,b,c
        0x7f,  //8 -> a,b,c,d,e,f,g
        0x67   //9 -> a,b,c,f,g
    };
    
    if(INTCONbits.T0IF){
        
//         overflow = ciclo de máquina * prescaler * contagem ( 256 - TMR0 )
//         overflow = 1us * 4 * 256 = 1.024ms
        if(counter == 3){
            counter = 0;
            
            if(value >= 10.0){
                number = (int)(value * 10.0);
                
                if(!dispUni && controle == 1){
                    controle = 2;
                    dispUni = dispDez = dispCen = 0;
                    PORTDISP = 0;
                    uni = (number % 10);
                    dispUni = 1;
                    PORTDISP = segments[uni];

                }else if(!dispDez && controle == 2){
                    controle = 3;
                    dispUni = dispDez = dispCen = 0;
                    PORTDISP = 0;
                    dez = (number % 100) / 10;
                    dispDez = 1;
                    PORTDISP = segments[dez] | (1<<7);  // com ponto

                }else if(!dispCen && controle == 3){
                    controle = 1;
                    dispUni = dispDez = dispCen = 0;
                    PORTDISP = 0; 
                    cen = (number / 100) - ((number % 100) / 100);
                    dispCen = 1;
                    PORTDISP = segments[cen];
                }                
            }else{
                number = (int)(value * 100.0);
                
                if(!dispUni && controle == 1){
                    controle = 2;
                    dispUni = dispDez = dispCen = 0;
                    PORTDISP = 0;
                    uni = (number % 10);
                    dispUni = 1;
                    PORTDISP = segments[uni];

                }else if(!dispDez && controle == 2){
                    controle = 3;
                    dispUni = dispDez = dispCen = 0;
                    PORTDISP = 0;
                    dez = (number % 100) / 10;
                    dispDez = 1;
                    PORTDISP = segments[dez];

                }else if(!dispCen && controle == 3){
                    controle = 1;
                    dispUni = dispDez = dispCen = 0;
                    PORTDISP = 0; 
                    cen = (number / 100) - ((number % 100) / 100);
                    dispCen = 1;
                    PORTDISP = segments[cen] | (1<<7); // com ponto
                }                
            }
        }  
        TMR0 = 0;
        INTCONbits.T0IF = 0;
        counter++;   
    }
}

void main(void) {
    
    CMCON = 0x07;   // desativa os comparadores do RA0-RA3   
    TRISB = 0x00;
    TRISA = 0b00110100;
    
    // CONFIG TIMER 0
    INTCONbits.GIE  = 1;        // Global Interrupt Enable bit
    INTCONbits.T0IE = 1;        // TMR0 Overflow Interrupt Enable bit
    INTCONbits.T0IF = 1;        // TMR0 Overflow Interrupt Flag bit
    OPTION_REGbits.T0CS = 0;    // TMR0 Clock Source Select bit (internal clock)
    OPTION_REGbits.PSA  = 0;    // Prescaler to the Timer0
    OPTION_REGbits.PS   = 1;    // Prescaler -> 1:4
    TMR0 = 0;
    
    value = 0.0;
    
    while(1){

//        float voltage = readADC();
//        float value = voltage - (0.2 - (0.017 * voltage));
        
        value = readADC();
//        delay_ms(100);        

//        displayWrite(voltage - (0.2 - (0.017 * voltage)));
    }
    
    return;
}

// ============= ADCSerial =============
char readSerial(){
    char valueADC = 0;
    
    pinCS = 1;
    delay_us(2);
    pinCS = 0;
    delay_us(2);
    
    for(int i = 7; i >= 0; i--){
        valueADC |= pinDATA << i;
        pinCLK = 1;
        delay_us(1);
        pinCLK = 0;
        delay_us(1);
    }
    
    return valueADC;    
}

float averageADC(char qnt){
    int readings = 0;
    for(char i = 0; i<qnt; i++)   readings += readSerial();
    return (float)readings / (float)qnt;
}

float readADC(){
//    return readSerial() * 15.0 / 255.0;
    return averageADC(100) * 15.0 / 255.0;
}
// ============= end ADCSerial =============

/*
// ============= Display =============
void displayWrite(float value){
    int number;
    int segments[10] = {
        0x3f,  //0 -> a,b,c,d,e,f
        0x06,  //1 -> b,c
        0x5b,  //2 -> a,b,d,e,g
        0x4f,  //3 -> a,b,c,d,g
        0x66,  //4 -> b,c,f,g
        0x6d,  //5 -> a,c,,d,f,g
        0x7d,  //6 -> a,c,d,e,f,g
        0x07,  //7 -> a,b,c
        0x7f,  //8 -> a,b,c,d,e,f,g
        0x67   //9 -> a,b,c,f,g
    };
    
    if(value >= 10.0){
        number = (int)(value * 10);
        
        uni = (number % 10);       
        PORTDISP = segments[uni];
        dispUni = 1;
        delay_us(time);
        dispUni = 0;
        
        dez = (number % 100) / 10;
        PORTDISP = segments[dez] | (1<<7); // com ponto
        dispDez = 1;
        delay_us(time);
        dispDez = 0;
                
        cen = (number / 100) - ((number % 100) / 100);
        PORTDISP = segments[cen];
        dispCen = 1;
        delay_us(time);
        dispCen = 0; 

    }else{
        number = (int)(value * 100);
        
        uni = (number % 10);
        PORTDISP = segments[uni];
        dispUni = 1;
        delay_us(time);
        dispUni = 0;
        
        dez = (number % 100) / 10;
        PORTDISP = segments[dez];
        dispDez = 1;
        delay_us(time);
        dispDez = 0;
        
        cen = (number / 100) - ((number % 100) / 100);
        PORTDISP = segments[cen] | (1<<7); // com ponto
        dispCen = 1;
        delay_us(time);
        dispCen = 0;        
    }
}
// ============= end Display =============
*/