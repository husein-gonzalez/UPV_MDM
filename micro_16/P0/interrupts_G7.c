
#include "system_G7.h"
#include "interrupts_G7.h"



int contador_1ms=0, flag_1s=0;



void _ISR _CNInterrupt(void)
{
   Nop();
   Nop();
   if (pulsador_S4 == pulsador_ON)
   {
       LED_On(LED_D3);
       
   }
   
      if (pulsador_S4 == pulsador_OFF)
   {
       LED_Off(LED_D3);
       
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
