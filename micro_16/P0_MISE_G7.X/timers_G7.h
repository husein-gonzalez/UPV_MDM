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


    
#include "system_G7.h"
#include "stdint.h"
    
//cabeceras

    extern int milis_F;
    extern int milis_F2;
    extern uint64_t t67_contador;
    void Inic_Timer_X (unsigned char timer, unsigned char unidades, unsigned int tiempo);
    void delay_ms (int milis); //milisegundos
    uint64_t time_diff(int opcion);
#ifdef	__cplusplus
}
#endif

#endif	/* TIMERS_GX_MISE_V0_H */

