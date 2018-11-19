/* 
 * File:   timers_G7.h
 * Author: 109229
 *
 * Created on 16 de noviembre de 2018, 16:23
 */

#ifndef TIMERS_GX_MISE_V0_H
#define	TIMERS_GX_MISE_V0_H

#ifdef	__cplusplus
extern "C" {
#endif

//cabeceras
    
    #include "system_G7.h"

    extern int milis_F;
    void Inic_Timer_X (unsigned char timer, unsigned char unidades, unsigned int tiempo);
    void delay_ms (int milis); //milisegundos

#ifdef	__cplusplus
}
#endif

#endif	/* TIMERS_GX_MISE_V0_H */

