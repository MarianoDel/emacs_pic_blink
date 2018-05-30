#include "timer.h"
#include "pic16f628a.h"
#include "hard.h"


/* External Variables --------------------------------------*/
extern volatile unsigned short timer_standby;
extern volatile unsigned short timer_led;


/* Global Variables --------------------------------------*/
volatile unsigned short wait_ms_counter = 0;

/* Exported Functions -------------------------------------*/

void EnableTimer0 (void)
{
    T0CS = 0;	// Clear to enable timer mode.
    PSA = 0;	// Clear to assign prescaler to Timer 0.

 /*
    This nice explanation and chart from 
    http://code.google.com/p/picrobotcode/source/browse/trunk/cylon_basic.c?r=4

    The TMR0 interupt will occur when TMR0 overflows from 0xFF to
    0x00.  Without a prescaler, TMR0 will increment every clock
    cycle resulting in an interrupt every 256 cycles.  However, 
    using a prescaler, we can force that interrupt to occure at
    less frequent intervals.
    
    Each clock cycle is 1/4 the external clock.  Using that, and
    knowing the prescaler, we can determine the time interval for
    our interrupt.  
    
    PS2 PS1 PS0 Ratio   Cycles  4MHz        10MHz
    0   0   0   1:2     512      512.0 uS    204.8 uS    
    0   0   1   1:4     1024     1.024 mS    409.6 uS
    0   1   0   1:8     2048     2.048 mS    819.2 uS
    0   1   1   1:16    4096     4.096 mS    1.638 mS
    1   0   0   1:32    8192     8.192 mS    3.276 mS
    1   0   1   1:64    16384   16.384 mS    6.553 mS
    1   1   0   1:128   32768   32.768 mS   13.107 mS
    1   1   1   1:256   65536   65.536 mS   26.214 mS 
    */

    PS2 = 0;	// Set up prescaler to 1:256.  
    PS1 = 0;
    PS0 = 1;

    INTCON = 0;	// Clear interrupt flag bits.
    GIE = 1;	// Enable all interrupts.

    T0IE = 1;	// Enable peripheral interrupts.
    TMR0 = 0;	// Set Timer 0 to 0.  
}

// este micro tiene una sola interrupcion
// peripheral int
// TMR0 int
// RB0 int
// portB int
void InterruptTimer0(void) __interrupt
{
    //reviso int en el timer0
    if (T0IF)
    {
        T0IF = 0;	// Clear the Timer 0 interrupt.

        if (wait_ms_counter)
            wait_ms_counter--;

        if (timer_standby)
            timer_standby--;

        if (timer_led)
            timer_led--;
    }

//	GIE=1;		// Globally enable interrupts.
            /** We don't need to do this ourselves since
             *  the compiler ALWAYS ADDS THIS FOR US
             *  in interrupt functions!
             *  If you try and DISable interrupts in an
             *  interrupt function it WON'T WORK since
             *  the compiler ALWAYS turns them back ON!
             */
}

void Wait_ms (unsigned short a)
{
    DisableGlobalInt;
    wait_ms_counter = a;
    EnableGlobalInt;
    while (wait_ms_counter);
}

void LoadTimerStanby (unsigned short a)
{
    DisableGlobalInt;
    timer_standby = a;
    EnableGlobalInt;
}

void LoadTimerLed (unsigned short a)
{
    DisableGlobalInt;
    timer_led = a;
    EnableGlobalInt;
}
