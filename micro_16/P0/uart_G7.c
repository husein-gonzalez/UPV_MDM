/*
* Fichero: .c
*
* Grupo: G0 Autor: Luis
* v1.0 Fecha:
 *
*/
#include "p24hj256gp610A.h"
#include "system_G7.h"



//#define _ISR_NO_PSV __attribute__((interrupt, no_auto_psv))
//================================================================
// Cálculos de tiempos y baudios
#define Fosc 8000000 //Frecuencia oscilador CPU
#define Fcy Fosc/2
#define BAUDRATE2 9600 // baudios (bits/sg) de transmision
#define BAUD_RATEREG_2_BRGH1 ((Fcy/BAUDRATE2)/4)-1 // Para BRGH = 1
#define BAUD_RATEREG_2_BRGH0 ((Fcy/BAUDRATE2)/16)-1 // Para BRGH = 0
//===============================================================
// Reg/bits UART2 serial port: U2MODE y U2STA no definidos en P24FJ12GA010A.h
// U2MODE
#define _STSEL_U2 U2MODEbits.STSEL
#define _PDSEL0_U2 U2MODEbits.PDSEL0
#define _PDSEL1_U2 U2MODEbits.PDSEL1
#define _BRGH_U2 U2MODEbits.BRGH
#define _RXINV_U2 U2MODEbits.URXINV
#define _ABAUD_U2 U2MODEbits.ABAUD
#define _LPBACK_U2 U2MODEbits.LPBACK
#define _WAKE_U2 U2MODEbits.WAKE
#define _UEN0_U2 U2MODEbits.UEN0
#define _UEN1_U2 U2MODEbits.UEN1
#define _RTSMD_U2 U2MODEbits.RTSMD
#define _IREN_U2 U2MODEbits.IREN
#define _USIDL_U2 U2MODEbits.USIDL
#define _UARTEN_U2 U2MODEbits.UARTEN
#define _PDSEL_U2 U2MODEbits.PDSEL
#define _UEN_U2 U2MODEbits.UEN 

// U2STA
#define _URXDA_U2 U2STAbits.URXDA
#define _OERR_U2 U2STAbits.OERR
#define _FERR_U2 U2STAbits.FERR
#define _PERR_U2 U2STAbits.PERR
#define _RIDLE_U2 U2STAbits.RIDLE
#define _ADDEN_U2 U2STAbits.ADDEN
#define _URXISEL0_U2 U2STAbits.URXISEL0
#define _URXISEL1_U2 U2STAbits.URXISEL1
#define _TRMT_U2 U2STAbits.TRMT
#define _UTXBF_U2 U2STAbits.UTXBF
#define _UTXEN_U2 U2STAbits.UTXEN
#define _UTXBRK_U2 U2STAbits.UTXBRK
#define _UTXISEL0_U2 U2STAbits.UTXISEL0
#define _UTXINV_U2 U2STAbits.UTXINV
#define _UTXISEL1_U2 U2STAbits.UTXISEL1
#define _URXISEL_U2 U2STAbits.URXISEL
//#define UART2_TX_TRIS TRISFbits.TRISF5
//#define UART2_RX_TRIS TRISFbits.TRISF4
//#define UART2_TX_LAT LATFbits.LATF5
//#define UART2_RX_LAT LATFbits.LATF4 

// Códigos Control para TeraTerm
#define CR 0x0D //
#define LF 0x0A
//
#define clrscr "\x1b[2J" // Borra pantalla 0x1b, '[','2','J'
#define home "\x1b[H" // Cursor inicio
//========================================================
void Inic_RS232_2 (void )
{
// No requerido, lo hace el hardware
// UART2_TX_TRIS = 0;
// UART2_RX_TRIS = 1;
// UART2_TX_LAT = 1;
// UART2_RX_LAT = 1;
// Inic_DMA_RS232_2 (); //

// U2MODE = ?; // 8bits, sin paridad, 1 stop, Uart parada
 _UARTEN_U2 =0; // Habilita UART
 _USIDL_U2 =0; // 0-> continua en modo Idle
 _IREN_U2 =0; // Habilita IrDA
 _RTSMD_U2 =0; // Modo pata U2RTS
 _UEN_U2 = 0; // Habilita U2TX, U2RX, U2CTS y U2RTS
 _WAKE_U2 =0; // Habilita Wake-up al detectar Start en Sleep
 _LPBACK_U2 =0; // Habilita modo Loopback
 _ABAUD_U2 =0; // Habilita Auto-Baud
 _RXINV_U2 =0; // Invierte polaridad para recepción
 _BRGH_U2 = 1; // BRGH 0 / 1
// _PDSEL_U2 =; // Paridad: 00= 8 bits sin paridad
// _STSEL_U2 =; // Duración bit Stop 
 
 U2BRG = 0x67 ;//103
 U2STA = 0;
// _UTXISEL1_U2 =; // Tipo Interrupción Transmisión
// _UTXINV_U2 =; // Invierte polaridad pata transmisión
// _UTXISEL0_U2 =; // Tipo Interrupción Transmisión
// _UTXBRK_U2 =; // Bit Breal
// _UTXEN_U2 =; // Habilita Transmisión
// _UTXBF_U2 =; // Estado Buffer transmisión (solo lectura)
// _TRMT_U2 =; // Estado Reg.Desplazamiento (solo lectura)
// _URXISEL_U2 =; // Tipo interrupción en recepción
 // 0x= interrupción con cada dato que llega
 // 10= interrupción a 3/4 del buffer
 // 11= interrupción cuando buffer lleno
// _ADDEN_U2 =; // Detección bit de dirección en 9 bits
// _RIDLE_U2 =; // Estado de la recepción (solo lectura)
// _PERR_U2 =; // Error de paridad /solo lectura)
// _FERR_U2 =; // Error de trama (solo lectura)
// _OERR_U2 =; // Error ocerrun (borrable/ solo lectura)
// _URXDA_U2 =; // 0=buffer vacío, 1= al menos un dato
 /* FIXME
 _U2TXIP =?; // Prioridad en recepción
 _U2RXIP = ?; // Prioridad en recepción
 _U2RXIF = ?; // Borra flag int. RX
 _U2TXIF = ?; // Borra flag int. TX
 _U2EIF = ?; // Boorra flag de Error UART
 _U2TXIE = ?; // Habilita int. de transmisión
 _U2RXIE = ?;
 _U2EIE = ?; // Habilita Int_ de Error UART 
 */
 _OERR_U2=0; // Según versión corrige bugg
 
 _UARTEN_U2 = 1; // Habilita la UART_2
 _UTXEN_U2 = 1; //Habilita transmisión, Debe activarse despues habilitar UART
  
Nop();
Nop();
Nop();
// ESCRIBE UNA FUNCION que ESPERA LA DURACION DE UN BIT ANTES DE
// empezar a transmitir
 //U2TXREG = 0; // Transmite caracter 0x00 (nulo))

 //DMA0CONbits.CHEN = 1; //Inicia DMA
} // FIN: Inic_RS232_2
//========= ENCUESTRA ====================================
void putRS232_2( char c) // Envía por encuesta un caracter
{
 while ( _UTXBF_U2 == 1); // Espera mientras buffer Tx está lleno
 U2TXREG = 0x33; // Carga dato a transmitir
// return c;
} // FINputRS232_2
// Espera a recibir un caracter por la UART2
char getRS232_2( void)
{
 while ( !_URXDA_U2); // Espera a que llegue un dato
 return U2RXREG; // recoge el dato
} // FIN getRS232_2 


// ====== Servicio INTERRUPCION TRANSMISION RS232_2 ==============
// Trasmite un dato, si hay, al final de transmisión del anterior
void _ISR_NO_PSV _U2TXInterrupt(void)
{
 //FIXME ? = 'H'; // Envía dato 'H'
 _U2TXIF = 0;
} // FIN _U2RXInterruptt
// Recoge el dato recibido byte a byte
void _ISR_NO_PSV _U2RXInterrupt ( void)
{
 //FIXME ?????
 _U2RXIF = 0;
} // FIN _U2RXInterruptt
void __attribute__((interrupt, no_auto_psv)) _U2ErrInterrupt (void)
{
 Nop();
 Nop();
 _U2EIF = 0;
} 
