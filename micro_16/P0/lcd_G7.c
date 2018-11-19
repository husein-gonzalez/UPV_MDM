
#include "p24HJ256GP610A.h"
#include "Explorer16_G7_MISE_v0.h"
#include "system_G7.h"


/***** LCD COMANDOS *****/
#define function_set 0x38 // 40us
#define display_on 0x0C // 40us
#define entry_mode 0x06 // 40us
#define line_1 0x80 // 40us, DDRAM 0x00
#define line_2 0xC0 // 40us, DDRAM 0x40
//#define fila_1 0x80; 
//ATC-UPV/EHU (L.G.) Micros 16bits - Práctica: LCD 3
//#define fila_2 0xC0;
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


//========= Envio de COMANDO =========
void lcd_cmd( char cmd ) //
{
 RW = 0; // ensure RW is 0
 RS = 0;
 DATA &= 0xFF00; // prepare RD0 - RD7
 DATA |= cmd; // command byte to lcd
 E = 1; // toggle E line
 Nop();
 //- - - CALCULA CUANTOS NOPs SON NECESARIOS - - -
 Nop();
 E = 0;
 RW = 1;
}


//======= Envio de DATO ===============
void lcd_data( char data ) //
{
 RW = 0; // ensure RW is 0
 RS = 1; // assert register select to 1
 DATA &= 0xFF00; // prepare RD0 - RD7
 DATA |= data; // data byte to lcd
 E = 1;
 Nop();
// - - - CALCULA CUANTOS NOPs SON NECESARIOS - - -
 Nop();
 E = 0; // toggle E signal
 RW = 1;
} 


//====================
// Genera la secuencia de comandos de inicialización del LCD display
void Init_LCD (void )
{
//? Inic_Timer_LCD ( ?,?,?);
 delay_ms( 15 ); //espera 15ms a quel a alimentación del LCD se estabilice

// Inicialización de pines
 LATE &= 0xFF00;
 RW = 0; // R/W state set low
 RS = 0; // RS state set low
 E = 0; // E state set low
 /* set data and control pins to outputs */
 TRISE &= 0xFF00; 
 
 RW_TRIS = 0; // RW pin set as output
 RS_TRIS = 0; // RS pin set as output
 E_TRIS = 0; // E pin set as output
 lcd_cmd(function_set); // Primer Comando
 delay_ms( 5 ); //Bucle de 5 ms bloqueante
 lcd_cmd(function_set); // Repite comando
 delay_ms( 1 ); //Bucle de 40us bloqueante
 lcd_cmd(function_set); // Repite comando
 delay_ms( 1 ); //Bucle de 15 ms bloqueante
 lcd_cmd(function_set); // Repite comand
 delay_ms( 1 ); //Bucle de 40us bloqueante
 lcd_cmd(display_on); // Display on/off control, cursor blink off (0x0C)
 delay_ms( 1 ); //Bucle de 40us bloqueante
 lcd_cmd(entry_mode); // entry mode set (0x06)
 delay_ms( 1 ); //Bucle de 40us bloqueante
 lcd_data(0x33);
 
 //Inic_Timer_LCD_Int ();
}
//======= Interrupción LCD ===============
//#define _LCD_Interrpt _T1Interrupt
void _ISR_NO_PSV _LCD_Interrpt (void) //
{
 //Escribe un programa (máquina de estados) que envíe un dato o comando cada vez
 _T1IF= 0;
} // === FIN _T4Interrupt ===
void Secuencia_LCD (unsigned int fila, unsigned int Num_Ventana) ;