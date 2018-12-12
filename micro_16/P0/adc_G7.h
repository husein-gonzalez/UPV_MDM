/* 
 * File:   adc_G7.h
 * Author: 109229
 *
 * Created on 20 de noviembre de 2018, 15:38
 */

#ifndef ADC_G7_H
#define	ADC_G7_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "system_G7.h"
    
#define TAM_BUFF_ADC 16 
    
extern unsigned int ADCValue,ADCValue2,temp_poten_F,joystick_F;;
extern unsigned int CAD_1_BuffA [TAM_BUFF_ADC] __attribute__((space(dma)));
extern unsigned int CAD_2_BuffA[TAM_BUFF_ADC] __attribute__((space(dma)));



#ifdef	__cplusplus
}
#endif

#endif	/* ADC_G7_H */

