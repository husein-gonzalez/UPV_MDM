


#include "buttons_G7.h"

/*** Button Definitions *********************************************/
//      S1  is MCLR button

#define pulsasor_S3  PORTDbits.RD6
#define pulsasor_S6  PORTDbits.RD7
#define pulsasor_S5  PORTAbits.RA7       //Overlaps with D10
#define pulsasor_S4  PORTDbits.RD13

#define pulsasor_S3_TRIS  TRISDbits.TRISD6
#define pulsasor_S6_TRIS  TRISDbits.TRISD7
#define pulsasor_S5_TRIS  TRISAbits.TRISA7
#define pulsasor_S4_TRIS  TRISDbits.TRISD13

#define BUTTON_PRESSED      0
#define BUTTON_NOT_PRESSED  1

#define PIN_INPUT           1
#define PIN_OUTPUT          0




void Inic_Pulsadores ()// Inicializa pulsadores  S3,S4,S5,S6 como salida

{

 pulsasor_S3_TRIS =1; 
 pulsasor_S6_TRIS =1; 
 pulsasor_S5_TRIS =1; 
 pulsasor_S4_TRIS =1; 
}