#include "p24HJ256GP610A.h"
#include "system_G7.h"
#include "interrupts_G7.h"



int contador_1ms=0, flag_1s=0, S3_F=0 ,S4_F=0, S6_F=0;


void configura_CN_int(void)
{
    
    _CNIP=4;
    _CNIF=0;
    IE_PULSADOR_S3=1;
    IE_PULSADOR_S4=1;
    IE_PULSADOR_S6=1;
    _CNIE=1;     
    
}



void _ISR _CNInterrupt(void)
{
   Nop();
   Nop();
   if (pulsador_S3 == pulsador_ON)
   {
       //LED_On(LED_D3);
       S3_F=1;       
   }
   if (pulsador_S4 == pulsador_ON)
   {
       //LED_On(LED_D3);
       S4_F=1;       
   }
   if (pulsador_S6 == pulsador_ON)
   {
       //LED_On(LED_D3);
       S6_F=1;       
   }
   
   
   _CNIF=0;
    
}

void _ISR _T1Interrupt(void)
{
    
    milis_F=1; //flag de 1ms
    milis_F2=1; //flag de 1ms
    
    if (contador_1ms <1000)
    {
        contador_1ms++;
    }
    
    else
    {
        flag_1s=1;
        contador_1ms=0;
    }
    
    
    _T1IF=0;
}

void _ISR _T7Interrupt(void)
{
    
    t67_contador++; //flag de 1ms
        
    _T1IF=0;
}
