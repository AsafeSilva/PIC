/* 
 * File:   PWM.h
 * Author: Asafe
 *
 * Created on 9 de Junho de 2017, 21:34
 */

#ifndef PWM_H
#define	PWM_H

#define PWM_DUTY CCPR1L

void configPWM(){
    PR2 = 255;                                                                  // Set the PWM period (~15.6 KHz [16MHz CLK])
    PWM_DUTY = 0;                                                               // Set Duty Cycle  = 0    
    
    TRISC2 = 0;                                                                 // Set RC2 (CCP1 pin) as OUTPUT
    
    // T2CON Register
    T2CKPS0 = 0;                                                                // Set TMR2 Prescaler 1:1
    T2CKPS1 = 0;                                                                
    TMR2IP = 0;                                                                 // Sets low priority to Timer2-PR2 
    TMR2ON = 1;                                                                 // Enable TMR2
    
    
    // CCP1CON Register
    CCP1M3 = 1;                                                                 // Set CCP1 as PWM Mode
    CCP1M2 = 1;                                                                                                                               
    
//    ei();                                                                       // Enables Global Interrupts
}

void setDutyPWM(int duty){
    if(duty > 1023) duty = 1023;
    else if(duty < 0) duty = 0;
    
    CCP1CONbits.DC1B = duty & 0b00000011;
    CCPR1L = duty >> 2;
}

int getDutyPWM(){
    return (CCPR1L << 2) | CCP1CONbits.DC1B;
}

#endif	/* PWM_H */

