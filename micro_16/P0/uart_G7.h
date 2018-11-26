/* 
 * File:   uart_G7.h
 * Author: 109229
 *
 * Created on 19 de noviembre de 2018, 17:03
 */

#ifndef UART_G7_H
#define	UART_G7_H

#ifdef	__cplusplus
extern "C" {
#endif
    
extern unsigned int BufferA[16] __attribute__((space(dma)));
extern unsigned int BufferB[16] __attribute__((space(dma)));
extern char Texto_RX[16];    

void Inic_RS232_2 (int freq );    
void putRS232_2( char c);    
char getRS232_2( void);
void cfgUart2(int freq);    
void cfgDma0UartTx(void);
void guarda_uart_rx();


#ifdef	__cplusplus
}
#endif

#endif	/* UART_G7_H */

