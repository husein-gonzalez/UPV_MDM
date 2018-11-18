/*
* Fichero: system_G7.c
*
* Grupo: G7    Autor: Susana & Husein


* Programa el PLL para la frecuencia del Oscilador Principal a 80MHz
* Inicializa el sistema
*/

#include "p24hj256gp610A.h"

/*
**	Oscillator Mode: Register FOSCSEL
**     FNOSC_FRC            Internal Fast RC (FRC)
**     FNOSC_FRCPLL         Internal Fast RC (FRC) con PLL
**     FNOSC_PRI            Primary Oscillator (XT, HS, EC)
**     FNOSC_PRIPLL         Primary Oscillator (XT, HS, EC) con PLL
**     FNOSC_SOSC           Secondary Oscillator (SOSC)
**     FNOSC_LPRC           Low Power RC Oscillator (LPRC)
**     FNOSC_FRCDIV16       Internal Fast RC (FRC) divide by 16
**     FNOSC_LPRCDIVN       Internal Fast RC (FRC) with divide by N
**
**	Two-speed Oscillator Start-Up Enable:
**     IESO_OFF             Start up with user-selected oscillator
**     IESO_ON              Start up with FRC, then switch
**
**	Primary Oscillator Source: Register FOSC
**     POSCMD_EC            EC Oscillator Mode
**     POSCMD_XT            XT Oscillator Mode
**     POSCMD_HS            HS Oscillator Mode
**     POSCMD_NONE          Primary Oscillator Disabled
**
**   OSC2 Pin Function:
**     OSCIOFNC_ON          OSC2 pin has digital I/O function
**     OSCIOFNC_OFF         OSC2 pin has clock out function
**
**   Clock Switching and Monitor:
**     FCKSM_CSECME         Both Clock Switching and Fail-Safe Clock Monitor are enabled
**     FCKSM_CSECMD         Clock switching is enabled, Fail-Safe Clock Monitor is disabled
**     FCKSM_CSDCMD         Both Clock Switching and Fail-Safe Clock Monitor are disabled
**
** Solo una referencia de FOSSCEL, FOSC, FWDT debe aparecer en un proyecto
** al inicio de un fichero .C, fuera de ninguna funcion
** Para ver configuraci?n -> (ir a: Window -> PIC Memory Views -> Configuration Bits
*/

//=========================================================================
// 
#pragma config FNOSC = PRIPLL  	// Oscillator Primario (XT, HS, EC) con PPL
#pragma config FCKSM = CSECMD   // Only clock switching enabled
#pragma config OSCIOFNC = OFF   // OSC2 is clock O/P
#pragma config POSCMD = XT      // XT oscillator                           
#pragma config FWDTEN = OFF     // Watchdog Timer: Disabled
// Estas PRAGMA se ejecutan al grabar el programa

//===========================================================================
void Inic_Oscilador (void)
{
	RCONbits.SWDTEN = 0;	// Disable Watch Dog Timer (No tiene que ver con Oscilador)

// Configura el Oscilador para operar a x MHz
// Fosc= Fin*M(N1*N2),  Fcy=Fosc/2
// Fosc= 8M*40/(2*2)= 80MHz for 8M input clock
// M=40 --> 80 MHz Instruccion 25ns
// M=20 --> 40 MHz Instruccion 50ns
// M=10 --> 20 MHz Instruccion 100ns

	PLLFBD = 40-2;          // M
	CLKDIVbits.PLLPOST = 0; // N2
	CLKDIVbits.PLLPRE = 0;  // N1
//	OSCTUN = 0;             // TUNE FRC oscillator, if FRC is used

// Funciones pre-compiladas: MPLAB C30 -DS51284G- apendice B
// Clock switch to incorporate PLL

	__builtin_write_OSCCONH(0x03);		// Initiate Clock Switch to Primary
										// Oscillator with PLL (NOSC=0b011)
	__builtin_write_OSCCONL(0x01);		// Start clock switching
	while (OSCCONbits.COSC != 0b011);	// Wait fot Clock switch to occur

// Wait for PLL to lock
	while(OSCCONbits.LOCK !=1) {}
}   // === Fin Inic_Oscilador ===



void SYS_Initialize ( void )
{
    //Inic_Oscilador ();
    AD1PCFGL= 0xFFFF;   // Pone todas las patas anal?gicas de I/O digital
    AD1PCFGH= 0xFFFF;   // Por defecto las patas anal?gicas est?n habilitadas
    Inic_Timer_X ('1', '1', 4000);// timer 1 a 1ms
    configura_CN_int();
    Inic_Leds ();          // Inicializa led D3 de la EXPLORER 16
    Inic_Pulsadores ();    // Inicializa pulsador S4 de la EXPLORER 16
    Init_LCD();
}

