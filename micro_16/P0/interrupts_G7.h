/* 
 * File:   interrupts_G7.h
 * Author: 109229
 *
 * Created on 19 de noviembre de 2018, 16:27
 */

#ifndef INTERRUPTS_G7_H
#define	INTERRUPTS_G7_H

#ifdef	__cplusplus
extern "C" {
#endif


    
extern int contador_1ms,flag_1s, S3_F , S4_F,S5_F, S6_F;
    
void configura_CN_int(void);


#ifdef	__cplusplus
}
#endif

#endif	/* INTERRUPTS_G7_H */

