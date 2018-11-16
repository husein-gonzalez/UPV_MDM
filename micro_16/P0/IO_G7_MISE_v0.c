/*
Proyecto: MISE Micros 16bits 
Fichero: IO_G0__MISE_v0.c

Grupo: G0    Autor: Luis
v0.0	Fecha: 15-X-2018

 Descripci?n
 * Inicializa la pata asociada al led D3 y lo deja apagado
 * 
 * Inicializa la pata asociada al pulsadpr S4
 * Requiere fichero: IO_G0_v0.h
 */

#include "p24HJ256GP610A.h"
#include "Explorer16_G7_MISE_v0.h"
//#include "IO_G0_MISE_v0.h"


// ============================================
void Inic_Leds ()// Inicializa LEDS  Explorer16: RA0, ..., RA7
// Inicializa las patas de los leds de salida y el valor inicial
{
// 
    TRISA = 0x0000;
    /*
    TRISAbits.TRISA0= 0;     // Led_3,  '0' -> Salida (Output) / '1' -> Entrada (Input)
    TRISAbits.TRISA1= 0;     // Led_3,  '0' -> Salida (Output) / '1' -> Entrada (Input)
    TRISAbits.TRISA2= 0;     // Led_3,  '0' -> Salida (Output) / '1' -> Entrada (Input)
    TRISAbits.TRISA3= 0;     // Led_3,  '0' -> Salida (Output) / '1' -> Entrada (Input)
    TRISAbits.TRISA4= 0;     // Led_3,  '0' -> Salida (Output) / '1' -> Entrada (Input)
    TRISAbits.TRISA5= 0;     // Led_3,  '0' -> Salida (Output) / '1' -> Entrada (Input)
    TRISAbits.TRISA6= 0;     // Led_3,  '0' -> Salida (Output) / '1' -> Entrada (Input)
    TRISAbits.TRISA7= 0;     // Led_3,  '0' -> Salida (Output) / '1' -> Entrada (Input)
     */
//    _TRISA0= 0;     // equivale a la instrucci?n anterior 
                    // Led_4
                    // Led_5,
                    // Led_6,
                    // Led_7,
                    // Led_8,
                    // Led_9,
                    // Led_10,

// Los leds est?n conectados a tierra ->
// -> Un '1' en la salida del PIC lo enciende // -> Un '0' lo Apaga
    LATA=0x0000;
    /*
    LATAbits.LATA0= 0;  // Valor de inicio LED_3 -> Apagado
    LATAbits.LATA1= 0;  // Valor de inicio LED_3 -> Apagado
    LATAbits.LATA2= 0;  // Valor de inicio LED_3 -> Apagado
    LATAbits.LATA3= 0;  // Valor de inicio LED_3 -> Apagado
    LATAbits.LATA4= 0;  // Valor de inicio LED_3 -> Apagado
    LATAbits.LATA5= 0;  // Valor de inicio LED_3 -> Apagado
    LATAbits.LATA6= 0;  // Valor de inicio LED_3 -> Apagado
    LATAbits.LATA7= 0;  // Valor de inicio LED_3 -> Apagado
    */
//  LATA = LATA | 0b0000000000000001;
//  _LATA0= 0;    // Valor de inicio LED_3 -> Apagado
//  Led_D3= OFF;
                    // Valor de inicio LED_4
                    // Valor de inicio LED_5
                    // ....   
} // Fin Inic_Leds

// 
void Inic_Pulsadores ()// Inicializa pulsadores Explorer16: S3,S4,S5,S6

{
    _TRISD13 = 1;
 //   TRISDbits.TRISD13= 1;   // 1-> Entrada / 0 -> Salida
}

void _ISR _CNInterrupt(void)
{
   Nop();
   Nop();
   if (pulsador_S4 == pulsador_ON)
   {
       Led_D3=ON;
       
   }
   
      if (pulsador_S4 == pulsador_OFF)
   {
       Led_D3=OFF;
       
   }
   _CNIF=0;
    
}