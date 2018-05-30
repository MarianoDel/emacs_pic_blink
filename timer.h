#ifndef __TIMER_H__
#define __TIMER_H__



/* Exported Functions -------------------------------------*/
void EnableTimer0 (void);
void InterruptTimer0(void) __interrupt;
void Wait_ms (unsigned short);
void LoadTimerStanby (unsigned short);
void LoadTimerLed (unsigned short);


#endif
