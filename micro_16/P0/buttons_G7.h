/* 
 * File:   buttons_G7.h
 * Author: 109229
 *
 * Created on November 18, 2018, 9:59 PM
 */

#ifndef BUTTONS_G7_H
#define	BUTTONS_G7_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "system_G7.h"


#define IE_PULSADOR_S3 _CN15IE
#define IE_PULSADOR_S4 _CN19IE
#define IE_PULSADOR_S5 _CN23IE
#define IE_PULSADOR_S6 _CN16IE
   
#define pulsador_S3  PORTDbits.RD6
#define pulsador_S6  PORTDbits.RD7
#define pulsador_S5  PORTAbits.RA7       //solapa con D10
#define pulsador_S4  PORTDbits.RD13

#define pulsador_S3_TRIS  TRISDbits.TRISD6
#define pulsador_S6_TRIS  TRISDbits.TRISD7
#define pulsador_S5_TRIS  TRISAbits.TRISA7
#define pulsador_S4_TRIS  TRISDbits.TRISD13

#define BUTTON_PRESSED      0
#define BUTTON_NOT_PRESSED  1

#define PIN_INPUT           1
#define PIN_OUTPUT          0
    
#define  pulsador_ON 0
#define  pulsador_OFF 1

extern int S5_entrada; //flagf que se pone a 1 cuando el pulsador esta configurado como entrada y a 0 como salida    
    
    
void Inic_Pulsadores (void);
    
    
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* BUTTONS_G7_H */

