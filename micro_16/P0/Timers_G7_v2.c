/*
Proyecto: MISE Micros 16bits
Fichero: Timers_G0_v2.c
Grupo: G0 Autor: Luis
v2.0 Fecha: 15-X-2018
 Descripción
 * Inicializa el timer x (1-5)
 * Inicializa timer 6_7 (32 bits
 *
 *
 * Requiere fichero: Timers_G0_MISE_v2.h
 */
#include "p24HJ256GP610A.h"
#include "Explorer16_G7_MISE_v0.h"
#include "Timers_G7_MISE_v0.h"
//#define _ISR_NO_PSV __attribute__((interrupt, no_auto_psv))
#define Timer_X 1 // Timer 16 bits a utilizar
#if (Timer_X == 1)
#define _T_Crono_TON T1CONbits.TON // Pone en marcha el Timer
#define _TcronoS10 T1CONbits.TCKPS //prescaler
#define TMR_X TMR1
#define PR_X PR1
#define TxCON T1CON
#define _TMR_X_TON T1CONbits.TON  //otro TON??
#define _TCKP_X T1CONbits.TCKPS
#define _TMR_X_Interrupt _T1Interrupt
#define _TxIP _T1IP //
#define _TxIF _T1IF //
#define _TxIE _T1IE //
#define _TMR_X_Interrupt _T1Interrupt
//#elif (Timer_X == 2)
//#define TMR_X TMR2
// ----
#elif(Timer_X == 0 || Timer_X > 5)
#error ("TIMER NO DEFINIDO")
#endif
unsigned char Tx_flag;
//=======================================
void Inic_Timer_X (unsigned char timer, unsigned char unidades, unsigned int tiempo)
 // Timer-> 1 a 6, Tiempo, unidades-> 0= microsegundos, 1= milisegundos
{
// Falta calcular el valor de tiempo dependiendo Oscilador y Prescaler
// Unidades = 1 -> milisegundos a 80MHz
 TMR_X = 0; // Borra valor del timer
 PR_X = tiempo-1; // Define periodo

 TxCON = 0x0000; // Habilitado, prescaler 1:1, CK interno
 _TCKP_X = 0; // Prescaler 1:1
 _TMR_X_TON = 1; //Pone en marcha el Timer_x
// Inicializa interrupción Timer 1
 _TxIP = 1; // Prioridad por defecto (1 minima - 6 máxima)
 _TxIF = 0; // Borra flag de interrupción
 _TxIE = 1; // Habilita Interrupción del Timer 1

 Tx_flag = 0;
} // Fin Inic_Timer_X
void Inic_Timer_67 () //
{

} 
