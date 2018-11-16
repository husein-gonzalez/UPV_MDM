/*
Proyecto: PRACTICA MISE Micros 16bits
Fichero: Main_IO_G0_MISE_v0.c

Grupo: G0    Autor: Luis
v0.1	Fecha: 15-X-2018

Descripci?n:
 * Inicializa led D3 y pulsadpr S4
 * Mientras el pulsador S4 est? presionado se enciende el led D3
 
 * Requiere fichero: IO_G0_v0.c y IO_G0_v0.h
 */

#include "p24HJ256GP610A.h"
#include "Explorer16_G7_MISE_v0.h"
#include "IO_G7_MISE_v0.h"





void configura_CN_int(void)
{
    
    _CNIP=4;
    _CNIF=0;
    IE_PULSADOR_S4=1;
    _CNIE=1;
    
    
    
    
    
}




int main(void)
{
Nop();
Nop();
//Inic_Oscilador ();	//Configura Frecuencia del Oscilador Principal a 80Mhz 
//
    AD1PCFGL= 0xFFFF;   // Pone todas las patas anal?gicas de I/O digital
    AD1PCFGH= 0xFFFF;   // Por defecto las patas anal?gicas est?n habilitadas

    // ========================
// Inicializaciones 
Nop();
Nop();
    configura_CN_int();
    Inic_Leds ();          // Inicializa led D3 de la EXPLORER 16
    Inic_Pulsadores ();    // Inicializa pulsador S4 de la EXPLORER 16
    
// ========================
// Bucle Principal
    while(1)
    {
Nop();
Nop();
   /* if (pulsador_S4 == pulsador_OFF)
    {
        Led_D3= ON;
        Led_D4= ON;
        Led_D5= ON;
        Led_D6= ON;
        Led_D7= ON;
        Led_D8= ON;
        Led_D9= ON;
        Led_D10= ON;
        
    }
Nop();
Nop();
    if (pulsador_S4 == pulsador_ON)
    {
        Led_D3= OFF;
        Led_D4= OFF;
        Led_D5= OFF;
        Led_D6= OFF;
        Led_D7= OFF;
        Led_D8= OFF;
        Led_D9= OFF;
        Led_D10= OFF;
    }
*/
  } // Fin while(1)
} //Fin main


