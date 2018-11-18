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

int contador_5ms=0, flag_1s=0,milis_F;





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

void _ISR _T1Interrupt(void)
{
    
    milis_F=1;
    if (contador_5ms <800)
    {
        contador_5ms++;
    }
    
    else
    {
        flag_1s=1;
        contador_5ms=0;
    }
    
    
    _T1IF=0;
}