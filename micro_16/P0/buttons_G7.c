

#include "p24HJ256GP610A.h"
#include "buttons_G7.h"
//#include "system_G7.h"


int S5_entrada; //flagf que se pone a 1 cuando el pulsador esta configurado como entrada y a 0 como salida


void Inic_Pulsadores ()// Inicializa pulsadores  S3,S4,S5,S6 como entrada

{

 pulsador_S3_TRIS =1; 
 pulsador_S6_TRIS =1; 
 pulsador_S5_TRIS =1; 
 S5_entrada = 1;
 pulsador_S4_TRIS =1; 
}
