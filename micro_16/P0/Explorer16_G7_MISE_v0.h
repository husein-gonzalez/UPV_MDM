/*
Proyecto: MISE Micros 16bits 
Fichero: EXPLORER16_G0_MISE_v0.h

Grupo: G0    Autor: Luis
v0.0	Fecha: 15-X-2018
 * 
 * 
 */


#include "p24HJ256GP610A.h"


#define _ISR_NO_PSV __attribute__((interrupt, no_auto_psv))
//
#define ON 1
#define OFF 0

#define  pulsador_ON 0
#define  pulsador_OFF 1
/*
#define  Led_D3 LATAbits.LATA0
#define  Led_D4 LATAbits.LATA1
#define  Led_D5 LATAbits.LATA2
#define  Led_D6 LATAbits.LATA3
#define  Led_D7 LATAbits.LATA4
#define  Led_D8 LATAbits.LATA5
#define  Led_D9 LATAbits.LATA6
#define  Led_D10 LATAbits.LATA7
  */

#define  pulsador_S4 PORTDbits.RD13

//#define TRIS_PULSADOR_S4 _TRISD6
#define IE_PULSADOR_S4 _CN19IE