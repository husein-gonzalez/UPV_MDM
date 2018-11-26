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

#include "system_G7.h"   
    
    
/***** LCD COMANDOS *****/
#define function_set 0x38 // 40us
#define display_on 0x0C // 40us
#define entry_mode 0x06 // 40us
#define line_1 0x80 // 40us, DDRAM 0x00
#define line_2 0xC0 // 40us, DDRAM 0x40
#define fila_1 0x80; 
//ATC-UPV/EHU (L.G.) Micros 16bits - Práctica: LCD 3
#define fila_2 0xC0;
// Define Pines asociados al LCD en la EXPLORER16
#define RW _LATD5 // LCD R/W signal
#define RS _LATB15 // LCD RS signal
#define E _LATD4 // LCD E signal
#define RW_TRIS _TRISD5
#define RS_TRIS _TRISB15
#define E_TRIS _TRISD4
#define DATA LATE // Port for LCD data
#define DATAPORT PORTE
#define TRISDATA TRISE // I/O setup for data Port
    
#define long_linea 16
#define long_linea_txt 12
#define num_lineas_txt 7
#define num_lineas 2
extern unsigned char Ventana_DATOS [num_lineas][long_linea_txt] __attribute__((space(dma)));             

//CABECERAS DE FUNCIONES DE LIBRERIA
void lcd_cmd( char cmd );
void lcd_data( char data );
void Init_LCD (void );


#ifdef	__cplusplus
}
#endif

#endif	/* LCD_G7_H */

