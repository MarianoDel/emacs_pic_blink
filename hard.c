#include "hard.h"
#include "timer.h"
#define NO_BIT_DEFINES
#include "pic16f628a.h"



/* Externals variables ---------------------------------------------------------*/
extern volatile unsigned short timer_led;


/* Global variables ------------------------------------------------------------*/
//para el led
led_state_t led_state = START_BLINKING;
unsigned char blink = 0;
unsigned char how_many_blinks = 0;


/* Module Functions ------------------------------------------------------------*/

//cambia configuracion de bips del LED
void ChangeLed (unsigned char how_many)
{
    how_many_blinks = how_many;
    led_state = START_BLINKING;
}

//mueve el LED segun el estado del Pote
void UpdateLed (void)
{
    switch (led_state)
    {
        case START_BLINKING:
            blink = how_many_blinks;
            
            if (blink)
            {
                LED_GREEN_ON;
                LoadTimerLed(200);
                led_state++;
                blink--;
            }
            break;

        case WAIT_TO_OFF:
            if (!timer_led)
            {
                LED_GREEN_OFF;
                LoadTimerLed(200);
                led_state++;
            }
            break;

        case WAIT_TO_ON:
            if (!timer_led)
            {
                if (blink)
                {
                    blink--;
                    LoadTimerLed(200);
                    led_state = WAIT_TO_OFF;
                    LED_GREEN_ON;
                }
                else
                {
                    led_state = WAIT_NEW_CYCLE;
                    LoadTimerLed(2000);
                }
            }
            break;

        case WAIT_NEW_CYCLE:
            if (!timer_led)
                led_state = START_BLINKING;

            break;

        default:
            led_state = START_BLINKING;
            break;
    }
}



//---- end of file ----//
