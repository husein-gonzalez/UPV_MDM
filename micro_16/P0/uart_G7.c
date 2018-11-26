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
#define Fosc0 8000000 //Frecuencia oscilador CPU 8MHz
#define Fosc1 80000000 //Frecuencia oscilador CPU 80MHz
#define Fcy0 Fosc0/2 
#define Fcy1 Fosc1/2
#define BAUDRATE2 9600 // baudios (bits/sg) de transmision
#define BAUD_RATEREG_2_BRGH10 ((Fcy0/BAUDRATE2)/4)-1 // Para BRGH = 1, 8MHz
#define BAUD_RATEREG_2_BRGH00 ((Fcy0/BAUDRATE2)/16)-1 // Para BRGH = 0, 8MHz
#define BAUD_RATEREG_2_BRGH11 ((Fcy1/BAUDRATE2)/4)-1 // Para BRGH = 1 , 80MHz
#define BAUD_RATEREG_2_BRGH01 ((Fcy1/BAUDRATE2)/16)-1 // Para BRGH = 0, 80MHz
//===============================================================
// Reg/bits UART2 serial port: U2MODE y U2STA no definidos en P24FJ12GA010A.h
// U2MODE
#define _STSEL_U2 U2MODEbits.STSEL
#define _PDSEL0_U2 U2MODEbits.PDSEL0
#define _PDSEL1_U2 U2MODEbits.PDSEL1
#define _BRGH_U2 U2MODEbits.BRGH
#define _RXINV_U2 U2MODEbits.RXINV
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


//********************************************************************************
//  STEP 6:
//  Allocate two buffers for DMA transfers
//********************************************************************************/
unsigned int BufferA[16] __attribute__((space(dma)));
unsigned int BufferB[16] __attribute__((space(dma)));

char Texto_RX[16] ={"====  PC RX ===="};
int caracter_RX=0;

//========================================================
void Inic_RS232_2 (int freq ) //freq = 0 => 8MHz, freq= 1 => 80Mhz
{
    
    if(freq==0) //frecuencia de oscilador = 8MHz
    {
    // No requerido, lo hace el hardware
    // UART2_TX_TRIS = 0;
    // UART2_RX_TRIS = 1;
    // UART2_TX_LAT = 1;
    // UART2_RX_LAT = 1;
    // Inic_DMA_RS232_2 (); //

     U2MODE = 0x00; // 8bits, sin paridad, 1 stop, Uart parada
    // _UARTEN_U2 =; // Habilita UART
    // _USIDL_U2 =; // 0-> continua en modo Idle
    // _IREN_U2 =; // Habilita IrDA
    // _RTSMD_U2 =; // Modo pata U2RTS
    // _UEN_U2 = ; // Habilita U2TX, U2RX, U2CTS y U2RTS
    // _WAKE_U2 =; // Habilita Wake-up al detectar Start en Sleep
    // _LPBACK_U2 =; // Habilita modo Loopback
    // _ABAUD_U2 =; // Habilita Auto-Baud
    // _RXINV_U2 =; // Invierte polaridad para recepción
     _BRGH_U2 = 1; // BRGH 0 / 1
    // _PDSEL_U2 =; // Paridad: 00= 8 bits sin paridad
    // _STSEL_U2 =; // Duración bit Stop
     U2BRG = BAUD_RATEREG_2_BRGH10 ;
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
     _U2TXIP =4; // Prioridad en recepción
     _U2RXIP = 4; // Prioridad en recepción
     _U2RXIF = 0; // Borra flag int. RX
     _U2TXIF = 0; // Borra flag int. TX
     _U2EIF = 0; // Boorra flag de Error UART
     _U2TXIE = 0; // Habilita int. de transmisión
     _U2RXIE = 0;
     _U2EIE = 0; // Habilita Int_ de Error UART 
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
        }
    
    else //frecuencia de oscilador = 80MHz
    {
        U2MODE = 0x00; // 8bits, sin paridad, 1 stop, Uart parada
        _BRGH_U2 = 1; // BRGH 0 / 1
        U2BRG = BAUD_RATEREG_2_BRGH11 ;
        U2STA = 0;
        _U2TXIP =4; // Prioridad en recepción
        _U2RXIP = 4; // Prioridad en recepción
        _U2RXIF = 0; // Borra flag int. RX
        _U2TXIF = 0; // Borra flag int. TX
        _U2EIF = 0; // Boorra flag de Error UART
        _U2TXIE = 0; // Habilita int. de transmisión
        _U2RXIE = 0;
        _U2EIE = 0; // Habilita Int_ de Error UART 
         _OERR_U2=0; // Según versión corrige bugg
        _UARTEN_U2 = 1; // Habilita la UART_2
        _UTXEN_U2 = 1; //Habilita transmisión, Debe activarse despues habilitar UART
       Nop();
       Nop();
       Nop();
 
    }
} // FIN: Inic_RS232_2


//========= ENCUESTRA ====================================
void putRS232_2( char c) // Envía por encuesta un caracter
{
 while ( _UTXBF_U2 == 1); // Espera mientras buffer Tx está lleno
 //U2TXREG = 0x33; // Carga dato a transmitir
  U2TXREG = c; // Carga dato a transmitir
// return c;
} // FINputRS232_2

// Espera a recibir un caracter por la UART2
char getRS232_2( void)
{
 while ( !_URXDA_U2); // Espera a que llegue un dato
 return U2RXREG; // recoge el dato
} // FIN getRS232_2 

void guarda_uart_rx(void) //cada vez que se recibe un dato y salta la interrupcion de RX se guarda en el buffer, y cada 1s se carga en ventan
{
    if(caracter_RX<16)
    {
       Texto_RX[caracter_RX] = U2RXREG;
       caracter_RX++;
    }
    else
        caracter_RX=0;
    
    
    
}


// ====== Servicio INTERRUPCION TRANSMISION RS232_2 ==============
// Trasmite un dato, si hay, al final de transmisión del anterior
void _ISR_NO_PSV _U2TXInterrupt(void)
{
// ? = 'H'; // Envía dato 'H'
 _U2TXIF = 0;
} // FIN _U2RXInterruptt

// Recoge el dato recibido byte a byte
void _ISR_NO_PSV _U2RXInterrupt ( void)
{
    _U2RXIF = 0;
    LED_Toggle(LED_D4);
    guarda_uart_rx();
 
} // FIN _U2RXInterruptt

void __attribute__((interrupt, no_auto_psv)) _U2ErrInterrupt (void)
{
 Nop();
 Nop();
 _U2EIF = 0;
} 


// Configura UART2 por DMA
void cfgUart2_DMA(int freq)
{
    if(osc_8_80_F==0)
    {
        U2MODEbits.STSEL = 0;			// 1-stop bit
        U2MODEbits.PDSEL = 0;			// No Parity, 8-data bits
        U2MODEbits.ABAUD = 0;			// Autobaud Disabled
        
        _BRGH_U2 = 1; // BRGH 0 / 1

        U2BRG = BAUD_RATEREG_2_BRGH10 ;

        //********************************************************************************
        //  STEP 1:
        //  Configure UART for DMA transfers
        //********************************************************************************/
        U2STAbits.UTXISEL0 = 0;			// Interrupt after one Tx character is transmitted
        U2STAbits.UTXISEL1 = 0;			                            
        U2STAbits.URXISEL  = 0;			// Interrupt after one RX character is received


        //********************************************************************************
        //  STEP 2:
        //  Enable UART Rx and Tx
        //********************************************************************************/
        
        _U2RXIP = 4;                    //prioridad int RX uart
        _U2RXIF = 0;
        _U2RXIE = 1;                    //Enable UART RX interrupt
        U2MODEbits.UARTEN   = 1;		// Enable UART
        U2STAbits.UTXEN     = 1;		// Enable UART Tx



        IEC4bits.U2EIE = 0;
        //IEC1bits.U2RXIE = 1;
    }
    
          
}

// TX DMA0 configuration
void cfgDma0UartTx(void)
{
	//********************************************************************************
	//  STEP 3:
	//  Associate DMA Channel 0 with UART Tx
	//********************************************************************************/
	DMA0REQ = 0x001F;					// Select UART2 Transmitter
	DMA0PAD = (volatile unsigned int) &U2TXREG;
	
	//********************************************************************************
	//  STEP 5:
	//  Configure DMA Channel 0 to:
	//  Transfer data from RAM to UART
	//  One-Shot mode
	//  Register Indirect with Post-Increment
	//  Using single buffer
	//  8 transfers per buffer
	//  Transfer words
	//********************************************************************************/
	//DMA0CON = 0x2001;					// One-Shot, Post-Increment, RAM-to-Peripheral
	DMA0CONbits.AMODE = 0;
	DMA0CONbits.MODE  = 1;
	DMA0CONbits.DIR   = 1;
	DMA0CONbits.SIZE  = 0;
	DMA0CNT = 15;						// 16 DMA requests

	//********************************************************************************
	//  STEP 6:
	// Associate one buffer with Channel 0 for one-shot operation
	//********************************************************************************/
	DMA0STA = __builtin_dmaoffset(BufferA);

	//********************************************************************************
	//  STEP 8:
	//	Enable DMA Interrupts
	//********************************************************************************/
	IFS0bits.DMA0IF  = 0;			// Clear DMA Interrupt Flag
	IEC0bits.DMA0IE  = 1;			// Enable DMA interrupt
    
    DMA0CONbits.CHEN  = 1;			// enable DMA0 Channel

}

// DMA1 configuration
void cfgDma1UartRx(void)
{
	//********************************************************************************
	//  STEP 3:
	//  Associate DMA Channel 1 with UART Rx
	//********************************************************************************/
	DMA1REQ = 0x001E;					// Select UART2 Receiver
	DMA1PAD = (volatile unsigned int) &U2RXREG;

	//********************************************************************************
	//  STEP 4:
	//  Configure DMA Channel 1 to:
	//  Transfer data from UART to RAM Continuously
	//  Register Indirect with Post-Increment
	//  Using two ?ping-pong? buffers
	//  8 transfers per buffer
	//  Transfer words
	//********************************************************************************/
	//DMA1CON = 0x0002;					// Continuous, Ping-Pong, Post-Inc, Periph-RAM
	DMA1CONbits.AMODE = 0;
	DMA1CONbits.MODE  = 2;
	DMA1CONbits.DIR   = 0;
	DMA1CONbits.SIZE  = 0;
	DMA1CNT = 15;						// 8 DMA requests

	//********************************************************************************
	//  STEP 6:
	//  Associate two buffers with Channel 1 for ?Ping-Pong? operation
	//********************************************************************************/
	DMA1STA = __builtin_dmaoffset(BufferA);
	DMA1STB = __builtin_dmaoffset(BufferB);

	//********************************************************************************
	//  STEP 8:
	//	Enable DMA Interrupts
	//********************************************************************************/
	IFS0bits.DMA1IF  = 0;			// Clear DMA interrupt
	IEC0bits.DMA1IE  = 1;			// Enable DMA interrupt

	//********************************************************************************
	//  STEP 9:
	//  Enable DMA Channel 1 to receive UART data
	//********************************************************************************/
	DMA1CONbits.CHEN = 1;			// Enable DMA Channel
}




//********************************************************************************
//  STEP 7:
//	Setup DMA interrupt handlers
//	Force transmit after 8 words are received
//********************************************************************************/
void __attribute__((interrupt, no_auto_psv)) _DMA0Interrupt(void)
{
	IFS0bits.DMA0IF = 0;			// Clear the DMA0 Interrupt Flag;
}

//void __attribute__((interrupt, no_auto_psv)) _DMA1Interrupt(void)
//{
//	static unsigned int BufferCount = 0;  // Keep record of which buffer contains Rx Data
//
//	if(BufferCount == 0)
//	{
//		DMA0STA = __builtin_dmaoffset(BufferA); // Point DMA 0 to data to be transmitted
//	}
//	else
//	{
//		DMA0STA = __builtin_dmaoffset(BufferB); // Point DMA 0 to data to be transmitted
//	}
//
//	DMA0CONbits.CHEN  = 1;			// Re-enable DMA0 Channel
//	DMA0REQbits.FORCE = 1;			// Manual mode: Kick-start the first transfer
//
//	BufferCount ^= 1;				
//	IFS0bits.DMA1IF = 0;			// Clear the DMA1 Interrupt Flag
//}




//void __attribute__ ((interrupt, no_auto_psv)) _U2ErrInterrupt(void)
//{
//	IFS4bits.U2EIF = 0; // Clear the UART2 Error Interrupt Flag
//}