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
    PR2 = 255;                                                                  // Set the PWM period (~23.44 KHz)
    CCPR1L = CCP1X = CCP1Y = 0;                                                 // Set Duty Cycle  = 0    
    TRISBbits.TRISB3 = 0;                                                       // Set as OUTPUT
    T2CONbits.T2CKPS = 0;                                                       // Set TMR2 Prescaler 1:1
    T2CONbits.TMR2ON = 1;                                                       // Enable TMR2
    CCP1CONbits.CCP1M = 12;                                                     // Set CCP1 as PWM Mode
}

#endif	/* PWM_H */

