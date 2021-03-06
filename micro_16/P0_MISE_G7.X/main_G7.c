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
//#include "Explorer16_G7_MISE_v0.h"
//#include "IO_G7_MISE_v0.h"
//#include "leds_G7.h"
//#include "lcd_G7.h"
//#include "buttons_G7.h"
#include "system_G7.h"
//#include "interrupts_G7.h"


extern void SYS_Initialize ( void ) ;
int Str_i, Str_j;
int EscrituraLCD;
int columnaLCD;
int cont_5s = 0;
int avance_display=0;
int filas;

//const char Texto_1[ ] = {"=== MISE G7 ===="     // 16 caracteres l�nea 1 
//                         "=== Pulsa S3 ==="};    // 16 caracteres l�nea 2 
//const char Texto_1[ ] = {"=== MISE G7 ===="     // 16 caracteres l�nea 1 
unsigned char Texto_1[ ] = {"== MISE G7 ="     // 16 caracteres l�nea 1 
                            "Medida 1:___"
                            "Medida 2:___"
                            "Medida 3:___"
                            "Medida 4:___"
                            "Medida 5:___"
                            "Medida 6:___"};    // 16 caracteres l�nea 2 



enum{
    INICIO,
    DATO,
    FILA1,
    FILA2,
    EVALUA
};


void Inicializacion_variables(void)
{

    Str_i = 0;
    Str_j = 0;
    EscrituraLCD = INICIO;
    columnaLCD = 0;
}

//=== Pasa un texto de FLASH a RAM y 
//void Mensaje_FLASH_Ventana_DATOS (unsigned char *texto) 
//{ 
//unsigned char i, j; 
//j= 0; 
//for(i=0; i<16; i++, j++) 
//      {      
//        Ventana_DATOS[0][i] = texto[j] ; 
//      }      
//      for(i=0;i<16;i++,j++)      
//      {      
//        Ventana_DATOS[1][i] = texto[j] ; 
//      }      
//} //FIN Mensaje_FLASH_Ventana_DATOS


//=== Pasa un texto de FLASH a RAM y 
void Mensaje_FLASH_Ventana_DATOS_mejorado (unsigned char *texto, int avance) 
{ 
//unsigned char i, j; 
unsigned char i; 
int j;
j= avance * long_linea_txt;

      for(i=0; i<long_linea_txt; i++, j++) 
      {      
        Ventana_DATOS[0][i] = texto[j] ; 
      }      
      for(i=0;i<long_linea_txt;i++,j++)      
      {      
        Ventana_DATOS[1][i] = texto[j] ; 
      }   
    Nop();
    Nop();
} //FIN Mensaje_FLASH_Ventana_DATOS




void avanzarPantalla (void)
{

   // Mensaje_FLASH_Ventana_DATOS_mejorado(Texto_1,avance_display);
//    avance_display++;
//    EscrituraLCD = DATO;

}



/*
uint8_t valor = 0x35;

void escribelcd (void)
{


    //lcd_cmd(0x80);  //FIXME usa defines


    lcd_data(valor++);
    // lcd_cmd(0xc0);  //FIXME usa defines


   // lcd_data(0x35);
    
    delay_ms(5);

}
*/
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

void escribir_UART_DMA(char* txtPrintable)
{
    int i=0;
    
    for(i=0;i<16;i++)
    {
        BufferA[i]=txtPrintable[i];
        //delay_ms(1);
    }    
   // putRS232_2(0x0D);
  //  putRS232_2(0x0A);
}

void EnvioDatosLCD(unsigned char* txtPrintable)
{
//    char c;
    
    
    if (milis_F2)
    {     

        char c= "1";
        switch(EscrituraLCD)
        {
            
            case INICIO:
                filas = 1;
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
                if(columnaLCD <= long_linea_txt)
                {
                    lcd_data(Ventana_DATOS[0][columnaLCD]);
                    columnaLCD++;
                }
                else 
                {
                    if(columnaLCD <=long_linea)
                    {
                        lcd_data(c);
                        columnaLCD++;
                    }
                    else
                    {
                        columnaLCD =0;     
                        c = "2";
//                        lcd_cmd(0x01);
//                        delay_ms(5);
                        lcd_cmd(0xC0);
                        delay_ms(5);
                        EscrituraLCD = FILA2;
                    }
                }                                                                           
            break;
            case FILA2:
                    if(columnaLCD==0)
                    {
                       lcd_cmd(0xC0);
                        delay_ms(1);
                    }
                    //c=lcd_data(Ventana_DATOS[1][columnaLCD]);
                    if (columnaLCD <= long_linea_txt)//fixme usar define                        
                    {
                        lcd_data(Ventana_DATOS[1][columnaLCD]);                        
                        columnaLCD++;
                    }    
                    else
                    {
                        if (columnaLCD <= long_linea)
                        {
                         lcd_data(c);                        
                         columnaLCD++;
                        }
                        else
                       EscrituraLCD = EVALUA;                                      
                    }
            break;                    
            case EVALUA:
//                    delay_ms(1000);                 
//                    if(filas < n_lineas-1)
//                    {
//                        filas++;
//                        EscrituraLCD = DATO;
//                        columnaLCD =0;  
//                       // avance_display++;
//                    }
//                    else
//                    {
//                        EscrituraLCD = INICIO;
//
//                    }
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

//char caracter='a';
char osc_freq=0;

// Inicializaciones 

SYS_Initialize();
Inicializacion_variables();
escribir_UART_DMA(Texto_1);


        /*
   // Inic_Oscilador ();
    Inic_Timer_X ('1', '1', 4000);
    configura_CN_int();
    Inic_Leds ();          // Inicializa led D3 de la EXPLORER 16
    Inic_Pulsadores ();    // Inicializa pulsador S4 de la EXPLORER 16
    Init_LCD();
  */  
// ========================
// Bucle Principal
    while(1)
    {
        
    delay_ms (5);
    Nop();
    Nop();


    tiempo_exec=time_diff(0);  //0 empieza el contador, 1 devuelve tiempo transcurrido
    delay_ms(5);
    tiempo_exec=time_diff(1);  //0 empieza el contador, 1 devuelve tiempo transcurrido

    EnvioDatosLCD(Texto_1);

    //escribelcd();
    //FIXME: sacar tiempo transcurrido por LCD o UART

    if (flag_1s ==1)
    {

      //  Led_D3=!Led_D3;
        LED_Toggle(LED_D3);
        flag_1s=0;
        //escribir_UART(Texto_1);
      //  DMA0CONbits.CHEN  = 1;			// Rehabilitar Canal 0, necesario cada env�o
      //  DMA0REQbits.FORCE = 1;			// forzar transmision
	cont_5s++;



    //    if(caracter<0x7a)
    //    {
    //        caracter++;
    //       
    //    }
    //    else
    //        caracter=0x41;

    }
    if (S3_F==1)
    {
        S3_F=0;
        LED_Sweep_Left();
        toggle_osc_8_80();        
        osc_freq=OSCCONbits.COSC;        
        Texto_1[40]= osc_freq;                
    }
    
        if (S6_F==1)
    {
        S6_F=0;
        LED_Sweep_Right();
        
    }
    if(S4_F==1)
    {
    
                    if(filas < num_lineas_txt-1)
                    {
                        filas++;
                        EscrituraLCD = DATO;
                        columnaLCD =0;  
                        avance_display++;
                    }
                    else
                    {
                        avance_display=0;
                        EscrituraLCD = INICIO;
                        //filas =0;
                    }
                    S4_F=0;
    }

/*
    if (pulsador_S4 == pulsador_OFF)
    {
        Led_D3= ON;

        
    }
Nop();
Nop();
    if (pulsador_S4 == pulsador_ON)
    {
        Led_D3= OFF;

    }
*/
  } // Fin while(1)
} //Fin main


