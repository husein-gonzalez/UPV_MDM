
#ifndef LEDS_H
#define LEDS_H
#include "system_G7.h"

typedef enum
{
    LED_NONE,
    LED_D3,
    LED_D4,
    LED_D5,
    LED_D6,
    LED_D7,
    LED_D8,
    LED_D9,
    LED_D10,
    ALL
} LED;

#define LED_COUNT 8

void LED_On(LED led);

void LED_Off(LED led);

void LED_Toggle(LED led);

void LED_Sweep_Left(void);

void LED_Sweep_Right(void);

void Inic_Leds (void);

#endif //LEDS_H
