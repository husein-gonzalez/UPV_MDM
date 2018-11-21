/* 
 * File:   system_G7.h
 * Author: 109229
 *
 * Created on 19 de noviembre de 2018, 15:50
 */

#ifndef SYSTEM_G7_H
#define	SYSTEM_G7_H

#ifdef	__cplusplus
extern "C" {
#endif

    
#define _ISR_NO_PSV __attribute__((interrupt, no_auto_psv))
    
    
#include "p24HJ256GP610A.h"
//#include "Explorer16_G7_MISE_v0.h"
#include "IO_G7_MISE_v0.h"
#include "leds_G7.h"
#include "lcd_G7.h"
#include "buttons_G7.h"
#include "timers_G7.h"
#include "interrupts_G7.h"
#include "uart_G7.h"
#include "adc_G7.h"
    
    
 
    
    


#ifdef	__cplusplus
}
#endif

#endif	/* SYSTEM_G7_H */

