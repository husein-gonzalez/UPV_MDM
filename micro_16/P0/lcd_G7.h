/* 
 * File:   lcd_G7.h
 * Author: 109229
 *
 * Created on November 18, 2018, 9:58 PM
 */

#ifndef LCD_G7_H
#define	LCD_G7_H

#ifdef	__cplusplus
extern "C" {
#endif

#define long_linea 16
#define num_lineas 2
extern unsigned char Ventana_DATOS [num_lineas][long_linea] __attribute__((space(dma)));             

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_G7_H */

