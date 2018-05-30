// Copyright (C) 2014 Diego Herranz

#define NO_BIT_DEFINES
// #include <pic16f628a.h>
#include <pic14regs.h>
#include <stdint.h>

#include "timer.h"
#include "hard.h"

// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN),
// disable watchdog,
// and disable low voltage programming.
// The rest of fuses are left as default.
__code uint16_t __at (_CONFIG) __configword = _INTRC_OSC_NOCLKOUT & _WDTE_OFF & _LVP_OFF;


/* External Variables ------------------------------*/
volatile unsigned short timer_standby = 0;
volatile unsigned short timer_led = 0;

/* Global Variables ------------------------------*/
unsigned short t1_time = 7000;
unsigned short t2_time = 1000;


/*--- Interrupt Prototypes must be in here -------------------------*/
extern void InterruptTimer0 (void) __interrupt 0;


// Module Functions ---------------//
void main(void)
{
    main_state_t main_state = INIT;
    
    TRISAbits.TRISA0 = 0;    //RA0 output
    TRISAbits.TRISA1 = 0;    //RA1 output
    TRISAbits.TRISA2 = 0;    //RA2 output

    CMCON = 0x07;

    EnableTimer0();

    ChangeLed(LED_STANDBY);
    while (1)
    {
        switch (main_state)
        {
        case INIT:
            LoadTimerStanby(10000);
            main_state++;
            break;

        case WAIT_FOR_START:
            if (!timer_standby)
            {
                LoadTimerStanby(t1_time); 
                RELAY_ON;
                main_state++;
                ChangeLed(LED_GENERATING);
            }                
            break;

        case T1:
            if (!timer_standby)
            {
                LoadTimerStanby(t2_time);
                RELAY_OFF;
                main_state++;
            }            
            break;

        case T2:
            if (!timer_standby)
            {
                LoadTimerStanby(t1_time); 
                RELAY_ON;
                main_state = T1;
            }                
            break;

        default:
            main_state = INIT;
            break;
        }

        //cosas que no tienen que ver con el estado del programa
        UpdateLed();
        
        
    }    //end while 1
}
