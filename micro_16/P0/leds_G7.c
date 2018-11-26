
/*
Proyecto: MISE Micros 16bits 
Fichero: leds_G7.c

Grupo: G7    Autor: Susana & Husein
v0.0	Fecha: 15-X-2018

 Descripcion
 * 
 * 
 * 
 * Requiere fichero: 
 */

#include "p24HJ256GP610A.h"
//#include "Explorer16_G7_MISE_v0.h"
//#include "IO_G0_MISE_v0.h"

#include "leds_G7.h"
#include <stdbool.h>


#define LED_D3_LAT      LATAbits.LATA0
#define LED_D4_LAT      LATAbits.LATA1
#define LED_D5_LAT      LATAbits.LATA2
#define LED_D6_LAT      LATAbits.LATA3
#define LED_D7_LAT      LATAbits.LATA4
#define LED_D8_LAT      LATAbits.LATA5
#define LED_D9_LAT      LATAbits.LATA6
#define LED_D10_LAT     LATAbits.LATA7      //solapa con S5

#define LED_D3_TRIS     TRISAbits.TRISA0
#define LED_D4_TRIS     TRISAbits.TRISA1
#define LED_D5_TRIS     TRISAbits.TRISA2
#define LED_D6_TRIS     TRISAbits.TRISA3
#define LED_D7_TRIS     TRISAbits.TRISA4
#define LED_D8_TRIS     TRISAbits.TRISA5
#define LED_D9_TRIS     TRISAbits.TRISA6
#define LED_D10_TRIS    TRISAbits.TRISA7    //solapa con S5




#define LED_ON  1
#define LED_OFF 0


//Enciende LED
void LED_On(LED led)
{
    switch(led)
    {
        case LED_D3:
            LED_D3_LAT = LED_ON ;
            break ;

        case LED_D4:
            LED_D4_LAT = LED_ON ;
            break ;

        case LED_D5:
            LED_D5_LAT = LED_ON;
            break;

        case LED_D6:
            LED_D6_LAT = LED_ON;
            break;

        case LED_D7:
            LED_D7_LAT = LED_ON;
            break;

        case LED_D8:
            LED_D8_LAT = LED_ON;
            break;

        case LED_D9:
            LED_D9_LAT = LED_ON ;
            break ;

        case LED_D10:
            LED_D10_LAT = LED_ON ;
            break ;

        default:
            break;
    }
}

//Apaga LED
void LED_Off(LED led)
{
    switch(led)
    {
        case LED_D3:
            LED_D3_LAT = LED_OFF ;
            break ;

        case LED_D4:
            LED_D4_LAT = LED_OFF ;
            break ;

        case LED_D5:
            LED_D5_LAT = LED_OFF;
            break;

        case LED_D6:
            LED_D6_LAT = LED_OFF;
            break;

        case LED_D7:
            LED_D7_LAT = LED_OFF;
            break;

        case LED_D8:
            LED_D8_LAT = LED_OFF;
            break;

        case LED_D9:
            LED_D9_LAT = LED_OFF ;
            break ;

        case LED_D10:
            LED_D10_LAT = LED_OFF ;
            break ;

        default:
            break;
    }
}

//conmuta LED
void LED_Toggle(LED led)
{
    switch(led)
    {
        case LED_D3:
            LED_D3_LAT ^= 1;
            break;

        case LED_D4:
            LED_D4_LAT ^= 1;
            break;

        case LED_D5:
            LED_D5_LAT ^= 1;
            break;

        case LED_D6:
            LED_D6_LAT ^= 1;
            break;

        case LED_D7:
            LED_D7_LAT ^= 1;
            break;

        case LED_D8:
            LED_D8_LAT ^= 1;
            break;

        case LED_D9:
            LED_D9_LAT ^= 1;
            break;

        case LED_D10:
            LED_D10_LAT ^= 1;
            break;

        default:
            break;
    }
}


void LED_Sweep_Left(void)
{
    int i=0;
    
    for(i=1;i<=LED_COUNT;i++)
    {
        LED_On(i);
        delay_ms(100);
        LED_Off(i);
        delay_ms(100);
    }
}



void LED_Sweep_Right(void)
{
    int i=0;
    
    for(i=LED_COUNT+1;i>0;i--)
    {
        LED_On(i);
        delay_ms(100);
        LED_Off(i);
        delay_ms(100);
    }
}



// ============================================
void Inic_Leds ()// Inicializa LEDS  Explorer16: RA0, ..., RA7
// Inicializa las patas de los leds de salida y el valor inicial
{
// 
    TRISA = 0x0000; //Todos los LEDs de salida
    

// Los leds est?n conectados a tierra ->
// -> Un '1' en la salida del PIC lo enciende // -> Un '0' lo Apaga
    LATA=0x0000; //todos los LEDs apagados
  
} // Fin Inic_Leds

