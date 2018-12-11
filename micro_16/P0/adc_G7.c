/*
Proyecto: MISE Micros 16bits 
Fichero: 

Grupo: G7    Autor: Susana & Husein
v0.0	Fecha: 2017-12-11
*/

#include "p24hj256gp610A.h"
#include "adc_G7.h"




//#define _ISR_NO_PSV __attribute__((interrupt, no_auto_psv))

unsigned int CAD_1_BuffA [32] __attribute__((space(dma)));
unsigned int CAD_1_BuffB[32] __attribute__((space(dma)));

unsigned int ADCValue;

//===============================================================
void Inic_CAD (void)	// ENCUESTA / INTERRUPCION
{
//CONFIGURAMOS EL ADC1 PARA MUESTREAR AN4,AN5, x, y,por canal CH0

AD1CON1= 0;	// 0x00E0
//_ADON= 0;	// CAD OFF
//_ADSIDL = 0;	//1=Se para en modo Idle / 0=Continua en modo Idle
//_ADDMABM = 0;	//1=bufer DMA en orden de conversi?n
                // 0=bufer DMA en modo Scatter/Gather
//_AD12B = 0; 	//1=Modo operacion de 12 bits / 0=Modo operacion de 10 bits 
//_FORM = 0; 	//Formato datos salida: 00=Integer (0000 00dd dddd dddd)
                                     // 01=Signed integer (ssss sssd dddd dddd)
_SSRC = 0b111; 	//FIXME Termina muestreo y comienca conversion del CAD
				//111=Auto-coonvert / 101 = TMR3 ADC1 y TMR5 ADC2 /
                // 010=TMR3  ADC1 y TMR5 ADC2
                // 001=INT0 / 000= hay que borrar SAMP
//_SIMSAM = 0; 	//1=Muestrea simultaneamente
                // 0=Muestrea canales individuales sequencialmente
//_ASAM = 1; 	//1=Muestreo comienza seguido de la conversion
                // 0=comienza cuando SAMP=1
//_SAMP     // Comienza muestreo
//_DONE     // Estado conversi?n

AD1CON2= 0;	// 
//_VCFG = 0;	//Vref+- 000=ACdd y AVss / 001=Vref+ y AVss
                // 010=AVdd y Vref- / 011=Vref+ y Vref-
//_CSCNA = 0;	//1=Escaneo canal cero / 0= no escaneo
//_CHPS = 0; 	//Canales utilizados:00=CH0 /01=CH0 y CH1 /1x= CH0,CH1,CH2 y CH3
//_BUFS	es solo de lectura: con BUFM=1-> 1=activa 2? mitad de buffer
                // 0= activa 1? mitad
//_SMPI = 0;	//Incrementos dir DMA +1 o
                // sin DMA genera una interrupci?n cada cada SMPI+1
//_BUFM = 0; 	//1= 2 medios Buffers de 8 / 0= 1 buffer de 16
//_ALTS = 0;	//Modo de muestreo: 1= Alternado / 0= Siempre canal A

AD1CON3 = 0;
_ADRC = 0; 		//1= reloj RC / 0= Reloj CPU
_SAMC = 31;		//Tiempo auto muestreo0 n?de Tad (de 0 a 31Tad)
_ADCS = 0x3f; 		//Tad= >75ns = Tcy(ADCS+1) -> a 80MHz Tcy= 25ns 

AD1CON4= 0;
//_DMABL = 3; 	//Cada buffer contiene 8 palabras 

AD1CHS123= 0;	// reg. seleccion de entrada canal 1,2 y 3 
//_CH123NA= 0;	//Selecci?n entrada negativa Canales 1, 2, y 3 pata Sample A 
		//0x= CH1=CH2=CH3-> Vref- / 10= CH1=AN6,CH2=AN7,CH3=AN8
                // 11= CH1=AN9,CH2=AN10,CH3=AN11
//_CH123SA=	0; //Selecci?n entrada positiva Canales 1, 2, y 3 para Sample A
		//1= AN3-AN4-AN5	/ 0= AN0-AN1-AN2
//_CH123NB = 0;
//_CH123SB = 0;

AD1CHS0= 0;	// registro de seleccion de entrada canal 0
//_CH0NA = 0; 	//Entrada negativa 1=  AN1 / 0 = Vref-
_CH0SA = 5;	//SELECIONA entrada positiva canal 0 Sample A (0=AN0 ... 31=AN31)
//_CH0SB = 3;
//_CH0NB = 0; 

AD1CSSH = 0x0000;	//Selecci?n entradas escaneo de la 16 a la 31
AD1CSSL = 0x0000; 	//Selecci?n entradas escaneo de 0 a 15. 

AD1PCFGH = 0xFFFF;	//Configura entradas: 1= digital	0= Analog
AD1PCFGL = 0xFFFF;
_PCFG4 = 0;		// AN4 -> RB4 -> Sensor Temperatura
_TRISB4 = 1;    // RB4 de entrada
_PCFG5 = 0;		// AN5 -> RB5 -> Potenci?metro
_TRISB5 = 1;	// RB5 de entrada

//valorCAD= 0;		// Valor del CAD leido

//IFS0
_AD1IF = 0; //Flag a cero del A/D interrrupt.
//IEC0
_AD1IE = 0; // Habilita la interrupcion A/D. 

//Inic_Timer_CAD();	// Si se quiere dispara el CAD desde un Timer

//AD1CON1bits
_ADON = 1; 	//Activa el modulo
//_SAMP= 1;	// Lanza muestreo (CONVERSION). Se puede hacer aqui o en otro sitio 

} // Fin Inic_CAD

//======= CAD1 ENCUESTA ==================================
unsigned int ADCValue;
void CAD1_encuesta ()
{
    AD1CON1bits.SAMP = 1;		// Comienza el muestreo y al de 31Tad empieza la conversi?n
	while (!AD1CON1bits.DONE);	// ?Se ha realizado la conversi?n?

	ADCValue = ADC1BUF0; 	//  Si, deja el valor en la variable ADCValue y repite
   
}

//=======================================================
void _ISR_NO_PSV _ADC1Interrupt (void)	// para interrumpir cada conversi?n
{
Nop();
Nop();
	_AD1IF = 0; //Flag a cero del A/D interrrupt.
} // FIN ADC1Interrupt

//================================================================
//========== CAD 1 DMA ORDER MODE ============
//inicializa CAD para DMA con Direc. Indirec. Reg. (ORDER MODE))
//CONFIGURAMOS EL ADC1 PARA MUESTREAR AN4,AN5, por canal CH0
void Inic_CAD_1_DMA(void) 
{
AD1CON1= 0; // 0x00E0
//_ADON= 0; // CAD OFF
//_ADSIDL = 0; //1=Se para en modo Idle / 0=Continua en modo Idle
//_ADDMABM = 0; //1=bufer DMA en orden de conversi?n***
// 0=bufer DMA en modo Scatter/Gather
//_AD12B = 0; //1=Modo operacion de 12 bits / 0=Modo operacion de 10 bits
//_FORM = 0; //Formato datos salida: 00=Integer (0000 00dd dddd dddd)
// 01=Signed integer (ssss sssd dddd dddd)
_SSRC = 0b111; //Termina muestreo y comienca conversion del CAD
//111=Auto-coonvert
// 010=TMR3 ADC1 y TMR5 ADC2
// 001=INT0 / 000= hay que borrar SAMP
//_SIMSAM = 0; //1=Muestrea simultaneamente
// 0=Muestrea canales individuales sequencialmente
_ASAM = 1; //1=Muestreo comienza seguido de la conversion
// 0=comienza cuando SAMP=1
//_SAMP
//_DONE
AD1CON2= 0; // 0x00E0
//_VCFG = 0; //Vref+- 000=ACdd y AVss / 001=Vref+ y AVss
// 010=AVdd y Vref- / 011=Vref+ y Vref-
_CSCNA = 1; //1=Escaneo canal cero / 0= no escaneo
//_CHPS = 0; //Canales utilizados:00=CH0 /01=CH0 y CH1 /1x= CH0,CH1,CH2 y CH3
//_BUFS es solo de lectura: con BUFM=1-> 1=activa 2? mitad de buffer
// 0= activa 1? mitad
_SMPI = 3; //Incrementos dir DMA +1 o
//_SMPI = 0; //Incrementos dir DMA +1 o
// sin DMA genera una interrupci?n cada cada SMPI+1
//_BUFM = 0; //1= 2 medios Buffers de 8 / 0= 1 buffer de 16
//_ALTS = 0; //Modo de muestreo: 1= Alternado / 0= Siempre canal A
AD1CON3 = 0;
//_ADRC = 0; //1= reloj RC / 0= Reloj CPU
_SAMC = 31; //Tiempo auto muestreo0 n?de Tad (de 0 a 31Tad)
_ADCS = 3; //Tad= >75ns = Tcy(ADCS+1) -> a 80MHz Tcy= 25ns
// Tad = (3+1)Tcy
AD1CON4= 0;
//_DMABL = --; //Cada buffer contiene 8 palabras
AD1CHS123= 0; // reg. seleccion de entrada canal 1,2 y 3
//_CH123NA= 0; //Selecci?n entrada negativa Canales 1, 2, y 3 pata Sample A
//0x= CH1=CH2=CH3-> Vref-
// 10= CH1=AN6,CH2=AN7,CH3=AN8
// 11= CH1=AN9,CH2=AN10,CH3=AN11
//_CH123SA= 0; //Selecci?n entrada positiva Canales 1, 2, y 3 para Sample A
//1= AN3-AN4-AN5 / 0= AN0-AN1-AN2
//_CH123NB = 0;
//_CH123SB = 0;
AD1CHS0= 0; // Seleccion de entrada canal 0
//_CH0NA = 0; //Entrada negativa 1= AN1 / 0 = Vref-
//_CH0SA = 5; //Entrada positiva = canal(CH0SA)
//_CH0SA = 4;
//_CH0SB = 3;
//_CH0NB = 0;
AD1CSSH = 0x0000; //Selecci?n entradas escaneo de la 16 a la 31
AD1CSSL = 0x0030; //Selecci?n entradas escaneo de 0 a 15. Activa pines 4 5 8 9 
//AD1CSSLbits.CSS2 =1;

AD1PCFGH = 0xFFFF; //Configura entradas: 1= digital 0= Analog
AD1PCFGL = 0xFFFF;
//_PCFG0= // AN0
_PCFG4 = 0; // AN4 -> RB4 -> Sensor Temperatura
_PCFG5 = 0; // AN5 -> RB5 -> Potenci?metro

_AD1IF = 0; //IFS0
_AD1IE = 0; //IEC0
// Bits DMA 
AD1CON1bits.ADDMABM = 0; // 1=bufer DMA en modo ORDER
                         // 0=bufer DMA en modo Scatter/Gather
//AD1CON2bits.SMPI = 2-1; //N?de puertos analog. conectados al CAD
//AD1CON4bits.DMABL = 2; 	//N? datos por entrada (0->1,1->2,2->4,3->8,...,7->128 
						// INDIFERENTE EN ESTE MODO

						AD1CON1bits.ADON = 1; //Habilita convertidor
//_SAMP= 1; //Lanza conversion
//------------------------------------------------------------------
DMA6CON = 0;
// CHEN CANAL habilitado / deshabilitado

/*fixme

DMA6CONbits.SIZE = ?; // 1=Byte / 0=Word
DMA6CONbits.DIR = ?; // 1=lee de RAM y escribe a perif?rico
// 0=lee de perif?rico y escribe en RAM
// HALF interrupcion a mitad / al final
// NULLW Escribe nulos / operacion normal
DMA6CONbits.AMODE = 0;    // 00 Indir.Reg con Post-Incr
                        //10: Direc.Indirect,Perif / 01 Indir.Reg sin Post-incr
                     
DMA6CONbits.MODE = ?; 	// 11:One PP / 10:Continuo + PP
						// 01: One / 00: Continuo
 * 
 */
// DMA0REQ
DMA6REQbits.FORCE = 0; // manual / autom?tico
// IRQSEL
// 0x00 INT0
// 0x01 IC1
// 0x02 OC1
// 0x05 IC2
// 0x06 OC2
// 0x07 TMR2
// 0x08 TMR3
// 0x0A SPI1
// 0x0B UART1RX
// 0x0C UART1TX
DMA6REQbits.IRQSEL = 0x0D; // ADC1 //DMA_IRQ_ADC1 //FIXME usar el ADC2
// 0x15 ADC2
// 0x1E UART2RX
// DMA2REQbits.IRQSEL = 0x1F; // UART2TX
// 0x21 SPI2
// 0x22 ECAN1-RX
// 0x37 ECAN2-RX
// 0x46 ECAN1-TX
// 0x47 ECAN2-TX
DMA6STA = __builtin_dmaoffset(CAD_1_BuffA); // Inicio dir. offset
//DMA2STB = __builtin_dmaoffset(CAD_BuffB); // Inicio dir. offset

DMA6PAD = (volatile unsigned int)&ADC1BUF0;
/*fixme
DMA6CNT = ?-1; // N? de trasnsferencias -1

DMACS0 = 0; // Borra Colisiones
_DMA6IP = ?;// prioridad Int.
IFS4bits.DMA6IF = ?; //Borra flag Int.
IEC4bits.DMA6IE = ?; //permite interrupciones DMA
DMA6CONbits.CHEN = ?; // Activa canal 2 DMA

*/
} // Fin Inic_CAD DMA
// -------------------------------------------------------------------

void _ISR_NO_PSV _DMA6Interrupt(void) {
    Nop();
    Nop();

    _DMA6IF = 0;
}
