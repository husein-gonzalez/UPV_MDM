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
#include "leds_G7.h"
#include "lcd_G7.h"
#include "buttons_G7.h"
#include "system_G7.h"
#include "interrupts_G7.h"


extern void SYS_Initialize ( void ) ;
int Str_i, Str_j;
int EscrituraLCD;
int columnaLCD;

const char Texto_1[ ] = {"=== MISE G7 ===="     // 16 caracteres línea 1 
                         "=== Pulsa S3 ==="};    // 16 caracteres línea 2 

enum{
    DATO,
    FILA1,
    FILA2
};


void Inicializacion_variables(void)
{

    Str_i = 0;
    Str_j = 0;
    EscrituraLCD = DATO;
    columnaLCD = 0;
}


void configura_CN_int(void)
{
    
    _CNIP=4;
    _CNIF=0;
    IE_PULSADOR_S4=1;
    _CNIE=1;
    
       
    
}
/*
uint8_t valor = 0x35;

void escribelcd (void)
{

////=== Pasa un texto de FLASH a RAM y
//void Mensaje_FLASH_Ventana_DATOS (unsigned char *texto)
//{
//    unsigned char i, j;
//    j= 0;
//    for(i=0; i<16; i++, j++)
//    {
//       Ventana_DATOS[0][i] = texto[j] ;
//    }
//    for(i=0;i<16;i++,j++)
//    {
//       Ventana_DATOS[1][i] = texto[j] ;
//    }
//} //FIN Mensaje_FLASH_Ventana_DATOS

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



void EnvioDatosLCD(char* txtPrintable)
{
    char c;
    
    if (milis_F2)
    {     

        char c;
        switch(EscrituraLCD)
        {
            
            case DATO:
                Mensaje_FLASH_Ventana_DATOS(txtPrintable);
                EscrituraLCD = FILA1;
                lcd_cmd(0x01);
                delay_ms(5);
                lcd_cmd(0x02);
                delay_ms(5);
            case FILA1:
               // c=lcd_data(Ventana_DATOS[0][columnaLCD]);
                    c=lcd_data(Ventana_DATOS[0][columnaLCD]);
                    columnaLCD++;
                    if (columnaLCD ==16)//fixme usar define                        
                    {
                        columnaLCD =0;
                        EscrituraLCD = FILA2;
                        //lcd_cmd(0xC0);
                        //delay_ms(5);
                    }
            break;
            case FILA2:
                    if(columnaLCD==0)
                    {
                       lcd_cmd(0xC0);
                        delay_ms(1);
                    }
                    //c=lcd_data(Ventana_DATOS[1][columnaLCD]);
                    if (columnaLCD < 16)//fixme usar define                        
                    {
                        c=lcd_data(Ventana_DATOS[1][columnaLCD]);
                        columnaLCD++;
                       // columnaLCD =0;
                        //EscrituraLCD = FILA2;
                    }    
                    else
                        Nop();
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

char caracter='a';

// Inicializaciones 

SYS_Initialize();
Inicializacion_variables();


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
        putRS232_2(caracter);


    //    if(caracter<0x7a)
    //    {
    //        caracter++;
    //       
    //    }
    //    else
    //        caracter=0x41;

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


