
/*
* 
* Fichero: Interrupciones_TRAP_v0.c
*
* Grupo: G0    Autor: Luis
* v1.0	Fecha: 2017-II-2
*
* Define las funciones de Int. TRAP 
 * 
*/

#include "p24hj256gp610A.h"
/#define _ISR_NO_PSV __attribute__((interrupt, no_auto_psv))

//void _ISR _OscillatorFail(void)
void _ISR_NO_PSV _OscillatorFail(void)
{
    Nop();
    Nop();
    while (1);
    Nop();
    Nop(); 
}   // === Fin Inic_Oscilador ===

//void _ISR _AddressError(void)
void _ISR_NO_PSV _AddressError(void)
{
    Nop();
    Nop();
    while (1);
    Nop();
    Nop(); 
} 

//void _ISR _StackError (void)
void _ISR_NO_PSV _StackError (void)
{
    Nop();
    Nop();
    while (1);
    Nop();
    Nop(); 
} 

//void _ISR _MathError(void)
void _ISR_NO_PSV _MathError (void)
{
    Nop();
    Nop();
    while (1);
    Nop();
    Nop(); 
} 


//void _ISR _DefaultInterrupt(void)
void _ISR_NO_PSV _DefaultInterrupt (void)
{
    Nop();
    Nop();
    while (1);
    Nop();
    Nop();  
} 