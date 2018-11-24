
#ifndef LEDS_H
#define LEDS_H

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
    LED_D10
} LED;

#define LED_COUNT 8

void LED_On(LED led);

void LED_Off(LED led);

void LED_Toggle(LED led);

void LED_Sweep_Left(void);

void LED_Sweep_Right(void);

#endif //LEDS_H
