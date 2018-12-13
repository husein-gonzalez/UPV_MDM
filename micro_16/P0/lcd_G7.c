
#include "p24HJ256GP610A.h"


#include "lcd_G7.h"






unsigned char Ventana_DATOS [num_lineas+1][long_linea] __attribute__((space(dma)));             



//========= Envio de COMANDO =========
void lcd_cmd( char cmd ) //
{
 DATA &= 0xFF00; // prepare RD0 - RD7
 DATA |= cmd; // command byte to lcd
 RW = 0;
 RS = 0;
 E = 1; // toggle E line
 Nop();
 Nop();
 Nop();

 E = 0;
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
 Nop();
 Nop();
 E = 0; // toggle E signal
 RS = 0; //

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
                lcd_cmd(0x01);//susana fixme
                delay_ms(1);
                lcd_cmd(0x02);
                delay_ms(1);
              
 //lcd_data(0x33);
 
 //Inic_Timer_LCD_Int ();
}
//======= Interrupción LCD ===============
//#define _LCD_Interrpt _T1Interrupt
/* //susana hacer interrupcion aqui??
void _ISR_NO_PSV _LCD_Interrpt (void) //
{
 //Escribe un programa (máquina de estados) que envíe un dato o comando cada vez
 _T1IF= 0;
} // === FIN _T4Interrupt ===
 * */
void Secuencia_LCD (unsigned int fila, unsigned int Num_Ventana) ;
