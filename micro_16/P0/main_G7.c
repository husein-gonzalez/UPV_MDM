/*
Proyecto: PRACTICA MISE Micros 16bits
Fichero: Main_IO_G0_MISE_v0.c

Grupo: G7    Autor: Susana & Husein
v0.1	Fecha: 15-X-2018

Descripci?n:
 * Inicializa led D3 y pulsadpr S4
 * Mientras el pulsador S4 est? presionado se enciende el led D3
 
 * Requiere fichero: IO_G0_v0.c y IO_G0_v0.h
 */

#include "p24HJ256GP610A.h"
#include "system_G7.h"


#define ROWS 7
#define COLUMNS 16


extern void SYS_Initialize ( void ) ;
int Str_i, Str_j;
int EscrituraLCD;
int EscrituraUART;
int columnaLCD;
int columnaUART;
int cont_5s = 0;
int avance_display=0;
int filas;
int filasUART;
unsigned int Medidas1 = 1234;
unsigned int Medidas2 = 0000;
unsigned int Medidas3 = 0000;
unsigned int Medidas4 = 0000;
unsigned int Medidas5 = 0000;
unsigned int Medidas6 = 0000;
unsigned int Medidas7 = 0000;
//unsigned int Medidas3;
//unsigned int Medidas4;
//unsigned int Medidas5;
//unsigned int Medidas6;
//fixme provisional hacer array
//Medidas1 = 111;
//Medidas2 = 222;
//Medidas3 = 333;
//Medidas4 = 444;
//Medidas5 = 555;
//Medidas6 = 666;


unsigned char Texto_1[ ] = {"== MISE G7 ="     // 16 caracteres l�nea 1 
                            "Temperatura:"
                            "Resistencia:"
                            "TMR:       _"
                            "Medida 4:___"
                            "Medida 5:___"
                            "Medida 6:___"};  // 16 caracteres l�nea 2 

char borra_pantalla[]= {"         \x1b[2J"}; // Borra pantalla 0x1b, '[','2','J'
char cursor_inicio[]=  {"          \x1b[H"};// Cursor inicio

enum{
    INICIO,
    DATO,
    FILA1,
    FILA2,
    EVALUA
};
enum{
    INICIO_UART,
    CURSOR_INICIO,
    SALTO_DE_CARRO,
    ESCRIBE_LINEA
};


void Inicializacion_variables(void)
{

    Str_i = 0;
    Str_j = 0;
    EscrituraLCD = INICIO;
    EscrituraUART = INICIO_UART;
    columnaLCD = 0;
    columnaUART = 0;
    filasUART = 0;
}


void ConvierteMedida(int n_medida, unsigned char *ValorMed)
{
   // int valor = Medidas1 ;//fixme cargar la variable que si es
    int valor; //fixme cargar la variable que si es
    int valor1 = 0;//fixme cargar la variable que si es
    int i;
   
    switch(n_medida)
    {
            case 0:
                valor = Medidas1;
                break;
            case 1:
                valor = Medidas1;
                break;
            case 2:
                valor = Medidas3;
                break;
            case 3:
                valor = Medidas4;
                break;
            case 4:
                valor = Medidas5;
                break;
            case 5:
                valor = Medidas6;
                break;
            case 6:
                valor = Medidas7;
                break;
    }
//    for (i=0; i < 4; i++)
//    {
        //ValorMed[3] = ((valor%1000)+ '0');
        valor1 = valor/1000;
        ValorMed[0] = valor1+'0';
        valor = (valor%1000);
        valor1 = valor/100;
        ValorMed[1] = (valor1+'0');
        valor = valor%100;
        valor1 = valor/10;
        ValorMed[2] = valor1+'0';
        valor = valor%10;
        valor1 = valor;
        ValorMed[3] = (valor1+'0');
//        valor = valor/10;
//    }
    
   
    





}



//=== Pasa un texto de FLASH a RAM y 
void Mensaje_FLASH_Ventana_DATOS_mejorado (unsigned char *texto, int avance) 
{ 
//unsigned char i, j; 
//unsigned char i; 
unsigned int i; 
unsigned char ValorMed[4]; 
int j,k;
j= avance * long_linea_txt;

      for(i=0; i<long_linea_txt; i++, j++) 
      {      
        Ventana_DATOS[0][i] = texto[j] ; 
      } 
        k=j;
      ConvierteMedida(avance+1, ValorMed);
	  for(i=long_linea_txt; i<long_linea; i++, j++) 
      {    
          
        Ventana_DATOS[0][i] = ValorMed[i-long_linea_txt];//caracter "1" 
      } 
        j=k;
      for(i=0;i<long_linea_txt;i++,j++)      
      {      
        Ventana_DATOS[1][i] = texto[j] ; 
      }
        ConvierteMedida(avance+2, ValorMed);
 		for(i=long_linea_txt; i<long_linea; i++, j++) 
      {      
         Ventana_DATOS[1][i] = ValorMed[i-long_linea_txt];//caracter "5" 
      }      

    Nop();
    Nop();
} //FIN Mensaje_FLASH_Ventana_DATOS



//=== Pasa un texto de FLASH a RAM y 
void Mensaje_FLASH_Ventana_DATOS (unsigned char *texto) 
{ 
unsigned char i, j; 
j= 0; 
for(i=0; i<16; i++, j++) 
      {      
        Ventana_DATOS[0][i] = texto[j] ; 
      }      
      for(i=0;i<16;i++,j++)      
      {      
        Ventana_DATOS[1][i] = texto[j] ; 
      }      
} //FIN Mensaje_FLASH_Ventana_DATOS

void escribir_UART(char* txtPrintable)
{
    int i=0;
    
    for(i=0;i<16;i++)
    {
        putRS232_2(txtPrintable[i]);
        delay_ms(1);
    }
    
    putRS232_2(0x0D);
    putRS232_2(0x0A);
    
        for(i=16;i<32;i++)
    {
        putRS232_2(txtPrintable[i]);
        delay_ms(1);
    }    
    
    putRS232_2(0x0D);
    putRS232_2(0x0A);
    
    for(i=32;i<48;i++)
    {
        putRS232_2(txtPrintable[i]);
        delay_ms(1);
    }    
    
    putRS232_2(0x0D);
    putRS232_2(0x0A);
}


//void escribir_RX(char *txtPrintable)
//{
//    int i=0;
//    
//    for(i=0;i<16;i++)
//    {
//        Texto_1[5][i]=txtPrintable[i];
//    }
//}
/*
void escribir_UART_DMA(char *txtPrintable)
{
    int i=0,j=0,k=0,l=0;
    
        delay_ms(50);
        Nop();
        Nop();
        for(l=0;l<16;l++)    //borra pantalla teraterm
        {
          BufferA[l]=borra_pantalla[l];
        }
        delay_ms(50);
        Nop();
        Nop();
//        DMA0CONbits.CHEN  = 1;			// Rehabilitar Canal 0, necesario cada env�o
//        DMA0REQbits.FORCE = 1;			// forzar transmision
        Nop();
        Nop();
        delay_ms(50);
        
        for(k=0;k<16;k++)    //pone teraterm al inicio de pantalla
        {
          BufferA[k]=cursor_inicio[k];
        }
        Nop();
        Nop();
        delay_ms(50);
        DMA0CONbits.CHEN  = 1;			// Rehabilitar Canal 0, necesario cada env�o
//        DMA0REQbits.FORCE = 1;			// forzar transmision
        Nop();
        Nop();
        delay_ms(50);
    

    
    
    for(j=0;j<ROWS;j++)
    {        
        for(i=0;i<COLUMNS;i++)
        {
           // BufferA[i]=txtPrintable[j][i];
            BufferA[i]= Ventana_DATOS[j][i];
            //delay_ms(50);
        } 
        DMA0CONbits.CHEN  = 1;			// Rehabilitar Canal 0, necesario cada env�o
//        DMA0REQbits.FORCE = 1;			// forzar transmision
        Nop();
        Nop();
        delay_ms(50);
//        BufferA[0]=0x0D;
//        BufferA[1]=0x0A;
        Nop();
        Nop();
        delay_ms(50);
        DMA0CONbits.CHEN  = 1;			// Rehabilitar Canal 0, necesario cada env�o
        DMA0REQbits.FORCE = 1;			// forzar transmision
        Nop();
        Nop();
        delay_ms(50);
        
    }
   // putRS232_2(0x0D);
  //  putRS232_2(0x0A);
}
*/

void escribir_UART_DMA(char *txtPrintable)
{
//    int i=0,j=0,k=0,l=0;
    
    
    switch(EscrituraUART)
    {
        case INICIO_UART:
          
              if (columnaUART > 16)//fixme usar define                        
            {          
                 //// delay_ms(50);
                     DMA0CONbits.CHEN  = 1;	
                     DMA0REQbits.FORCE = 1;	
                     delay_ms(50);
                    columnaUART = 0;
                    EscrituraUART = CURSOR_INICIO;
                    filasUART = 0;
            }
            else
            {

                  BufferA[columnaUART]=borra_pantalla[columnaUART];
                  columnaUART++;
           }               
            break;
        case CURSOR_INICIO:
          
              if (columnaUART > 16)//fixme usar define                        
            {          
                     delay_ms(50);
                     DMA0CONbits.CHEN  = 1;	
                     DMA0REQbits.FORCE = 1;	
                     delay_ms(50);
                    columnaUART = 0;
                    EscrituraUART = SALTO_DE_CARRO;
                    filasUART = 0;
            }
            else
            {

                  BufferA[columnaUART]=cursor_inicio[columnaUART];
                  columnaUART++;
            }               
            break;
            
        case SALTO_DE_CARRO:
            if (columnaUART < 14 )//fixme usar define                        
            {       
                 BufferA[columnaUART]=0x20;
                 columnaUART++;
               
            }
            else
            {
                 if (columnaUART < 15 )
                 {
                    BufferA[columnaUART]=0x0A;
                    columnaUART++;
                    BufferA[columnaUART]=0x0D;
                    columnaUART++;
                 }
                 else
                 {
                     delay_ms(50);
                     DMA0CONbits.CHEN  = 1;	
                     DMA0REQbits.FORCE = 1;	
                     delay_ms(50);
                 columnaUART = 0;
                 EscrituraUART = ESCRIBE_LINEA;
                 }
            }
               
            break;
        case ESCRIBE_LINEA:
            if(columnaUART ==0)
            {
                 Mensaje_FLASH_Ventana_DATOS_mejorado(txtPrintable,filasUART);                  
            
            
            }
            if (columnaUART == 16)//fixme usar define                        
            {          
                filasUART++;
                if(filasUART == ROWS)
                    EscrituraUART = INICIO_UART;
                else
                    EscrituraUART = SALTO_DE_CARRO;
                columnaUART = 0;
               // EscrituraUART = SALTO_DE_CARRO;
                delay_ms(50);
                DMA0CONbits.CHEN  = 1;	
                DMA0REQbits.FORCE = 1;	
                delay_ms(50);
            }
            else
            {
                //BufferA[columnaUART] = 0x41;
                BufferA[columnaUART] = Ventana_DATOS[0][columnaUART];
                columnaUART++;
            }
            break;      
    }
   
}
        
//        
//        
//    }
//        delay_ms(50);
//        Nop();
//        Nop();
//        for(l=0;l<16;l++)    //borra pantalla teraterm
//        {
//          BufferA[l]=borra_pantalla[l];
//        }
//        delay_ms(50);
//        Nop();
//        Nop();
////        DMA0CONbits.CHEN  = 1;			// Rehabilitar Canal 0, necesario cada env�o
////        DMA0REQbits.FORCE = 1;			// forzar transmision
//        Nop();
//        Nop();
//        delay_ms(50);
//        
//        for(k=0;k<16;k++)    //pone teraterm al inicio de pantalla
//        {
//          BufferA[k]=cursor_inicio[k];
//        }
//        Nop();
//        Nop();
//        delay_ms(50);
//        DMA0CONbits.CHEN  = 1;			// Rehabilitar Canal 0, necesario cada env�o
////        DMA0REQbits.FORCE = 1;			// forzar transmision
//        Nop();
//        Nop();
//        delay_ms(50);
//    

    
    
//    for(j=0;j<ROWS;j++)
//    {        
//        for(i=0;i<COLUMNS;i++)
//        {
//           // BufferA[i]=txtPrintable[j][i];
//            BufferA[i]= Ventana_DATOS[j][i];
//            //delay_ms(50);
//        } 
//        DMA0CONbits.CHEN  = 1;			// Rehabilitar Canal 0, necesario cada env�o
////        DMA0REQbits.FORCE = 1;			// forzar transmision
//        Nop();
//        Nop();
//        delay_ms(50);
////        BufferA[0]=0x0D;
////        BufferA[1]=0x0A;
//        Nop();
//        Nop();
//        delay_ms(50);
//        DMA0CONbits.CHEN  = 1;			// Rehabilitar Canal 0, necesario cada env�o
//        DMA0REQbits.FORCE = 1;			// forzar transmision
//        Nop();
//        Nop();
//        delay_ms(50);
//        
//    }

void EnvioDatosLCD(unsigned char* txtPrintable)
{
//    char c;
    
    
    if (milis_F2)
    {     

        char c= "1";
        switch(EscrituraLCD)
        {
            
            case INICIO:
                filas = 0;
                columnaLCD =0;  
                avance_display = 0;
                EscrituraLCD = DATO;
            case DATO:               
                Mensaje_FLASH_Ventana_DATOS_mejorado(txtPrintable,avance_display);                  
                lcd_cmd(0x01);
                delay_ms(5);
                lcd_cmd(0x02);
                delay_ms(5);
                lcd_cmd(0x80);
                delay_ms(5);
                EscrituraLCD = FILA1;
            case FILA1:
  					lcd_data(Ventana_DATOS[0][columnaLCD]);
                    columnaLCD++;
                    if (columnaLCD ==16)//fixme usar define                        
                    {
                        columnaLCD =0;                                               
                        lcd_cmd(0x01);
                        delay_ms(5);
                        lcd_cmd(0xC0);
                        delay_ms(5);
                        EscrituraLCD = FILA2;
                    }                                                                   
            break;
            case FILA2:
  					if (columnaLCD < 16)//fixme usar define                        
                    {
                        lcd_data(Ventana_DATOS[1][columnaLCD]);
                        columnaLCD++;
                    }    
                    else
                    {
                       EscrituraLCD = EVALUA;                                      
                    }
            break;                    
            case EVALUA:

                break;
           
        }
        
        
        
        
        
        //Mensaje_FLASH_Ventana_DATOS
        milis_F2 = 0;
        
    }


}


int main(void)
{
    
uint64_t tiempo_exec;
Nop();
Nop();


char osc_freq=0;

// Inicializaciones 

SYS_Initialize();

Inicializacion_variables();
//escribir_UART_DMA(Texto_1);

//parpadea todos los leds
//LATA=0xffff;
LED_On(ALL);
delay_ms(500);
LED_Off(ALL);
////LATA=0x0000;

// ========================
// Bucle Principal
    while(1)
    {
        
    delay_ms (5);
    Nop();
    Nop();


//    tiempo_exec=time_diff(0);  //0 empieza el contador, 1 devuelve tiempo transcurrido
//    delay_ms(5);
//    tiempo_exec=time_diff(1);  //0 empieza el contador, 1 devuelve tiempo transcurrido

    EnvioDatosLCD(Texto_1);
     escribir_UART_DMA(Texto_1);

    //FIXME: sacar tiempo transcurrido por LCD o UART

    if (flag_1s ==1)
    {

      //  Led_D3=!Led_D3;
        LED_Toggle(LED_D3);
        flag_1s=0;
       // escribir_UART_DMA(Texto_1);
   //     escribir_RX(Texto_RX);

       // escribir_UART(Texto_1);
       // DMA0CONbits.CHEN  = 1;			// Rehabilitar Canal 0, necesario cada env�o
     //   DMA0REQbits.FORCE = 1;			// forzar transmision
	cont_5s++;


    }
    if (S3_F==1)
    {
        S3_F=0;
        LED_Sweep_Left();
        toggle_osc_8_80();        
        osc_freq=OSCCONbits.COSC;        
//        Texto_1[40]= osc_freq;
        
        
    }
    
    if (S6_F==1)
    {
        S6_F=0;
        LED_Sweep_Right();        
    }
    
    if(S4_F==1)
    {
    
                    if(filas < num_lineas_txt-2)
                    {
                        filas++;
                        EscrituraLCD = DATO;
                        columnaLCD = 0;  
                        avance_display++;
                    }
                    S4_F=0;
    }
 if(S5_F==1)
    {
    
                    if(filas > 0)
                    {
                        filas--;
                        EscrituraLCD = DATO;
                        columnaLCD = 0;  
                        avance_display--;
                    }
                    S5_F=0;
    }


  } // Fin while(1)
} //Fin main


