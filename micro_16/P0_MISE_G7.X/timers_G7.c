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
//#include "Explorer16_G7_MISE_v0.h"
//#include "Timers_G7_MISE_v0.h"
#include "system_G7.h"

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
#elif (Timer_X == 2)
    #define TMR_X TMR2
    #define _T_Crono_TON T2CONbits.TON // Pone en marcha el Timer
    #define _TcronoS10 T2CONbits.TCKPS //prescaler
    #define PR_X PR2
    #define TxCON T2CON
    #define _TMR_X_TON T2CONbits.TON  //otro TON??
    #define _TCKP_X T2CONbits.TCKPS
    #define _TMR_X_Interrupt _T2Interrupt
    #define _TxIP _T2IP //
    #define _TxIF _T2IF //
    #define _TxIE _T2IE //
    #define _TMR_X_Interrupt _T2Interrupt
#elif (Timer_X == 3)
    #define TMR_X TMR3
    #define _T_Crono_TON T3CONbits.TON // Pone en marcha el Timer
    #define _TcronoS10 T3CONbits.TCKPS //prescaler
    #define PR_X PR3
    #define TxCON T3CON
    #define _TMR_X_TON T3CONbits.TON  //otro TON??
    #define _TCKP_X T3CONbits.TCKPS
    #define _TMR_X_Interrupt _T3Interrupt
    #define _TxIP _T3IP //
    #define _TxIF _T3IF //
    #define _TxIE _T3IE //
    #define _TMR_X_Interrupt _T3Interrupt
#elif (Timer_X == 4)
    #define TMR_X TMR4
    #define _T_Crono_TON T4CONbits.TON // Pone en marcha el Timer
    #define _TcronoS10 T4CONbits.TCKPS //prescaler
    #define PR_X PR4
    #define TxCON T4CON
    #define _TMR_X_TON T4CONbits.TON  //otro TON??
    #define _TCKP_X T4CONbits.TCKPS
    #define _TMR_X_Interrupt _T4Interrupt
    #define _TxIP _T4IP //
    #define _TxIF _T4IF //
    #define _TxIE _T4IE //
    #define _TMR_X_Interrupt _T4Interrupt
#elif (Timer_X == 5)
    #define TMR_X TMR5
    #define _T_Crono_TON T5CONbits.TON // Pone en marcha el Timer
    #define _TcronoS10 T5CONbits.TCKPS //prescaler
    #define PR_X PR5
    #define TxCON T5CON
    #define _TMR_X_TON T5CONbits.TON  //otro TON??
    #define _TCKP_X T5CONbits.TCKPS
    #define _TMR_X_Interrupt _T5Interrupt
    #define _TxIP _T5IP //
    #define _TxIF _T5IF //
    #define _TxIE _T5IE //
    #define _TMR_X_Interrupt _T5Interrupt
// ----
#elif(Timer_X == 0 || Timer_X > 5)
#error ("TIMER NO DEFINIDO")
#endif

unsigned char Tx_flag;
int milis_F=0;
int milis_F2=0;
uint64_t t67_contador=0;


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

 TMR6 = 0; // Borra valor del timer
 PR6 = 4000-1; // periodo=1ms si osc=8MHz  FIXME poner configuracoin variable
 T6CON=0x0008; //t6 forma un timer de 32 bits con t7
 T6CONbits.TCKPS = 0; // Prescaler 1:1
 T6CONbits.TON  = 1; //Pone en marcha el Timer_x
// Inicializa interrupción Timer 6_7
 _T7IP = 5; // Prioridad por defecto (1 minima - 6 máxima)
 _T7IF = 0; // Borra flag de interrupción
 _T7IE = 1; // Habilita Interrupción del Timer 1
    
    
} 


void delay_ms (int milis) //milisegundos
{
    int cnt=0;
    
    while(cnt<milis)
    {
        if (milis_F ==1)
        {
            cnt++;  
            milis_F=0;
            
        }
               
    }
    
    
    
}

uint64_t time_diff(int opcion)  //0 empieza el contador, 1 devuelve tiempo transcurrido
{
    uint64_t tiempo=0;
    
    switch(opcion)
    {
            case 0:
                
                t67_contador=tiempo;
                
                
                break;
                                        
            case 1:
                tiempo=t67_contador;
                break;
                
            default:
                   tiempo=0xFFFFFFFF ;    
                break;
                
                                      
    }
    
    return tiempo;
}