/*
Proyecto: PRACTICA MISE Micros 16bits
Fichero: Main_IO_G0_MISE_v0.c

Grupo: G0    Autor: Susana & Husein
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
   // Inic_Oscilador ();
    Inic_Timer_X ('1', '1', 4000);
    configura_CN_int();
    Inic_Leds ();          // Inicializa led D3 de la EXPLORER 16
    Inic_Pulsadores ();    // Inicializa pulsador S4 de la EXPLORER 16
    Init_LCD();
    
// ========================
// Bucle Principal
    while(1)
    {
Nop();
Nop();

if (flag_1s ==1)
{
    
    Led_D3=!Led_D3;
    flag_1s=0;
}
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


