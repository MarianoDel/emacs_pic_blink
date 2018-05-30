#ifndef __HARD_H_
#define __HARD_H_

// #include "pic16f628a.h"

/*--- Global Defines ---------------------------------*/
#define DisableGlobalInt    GIE = 0
#define EnableGlobalInt     GIE = 1

//ESTADOS DEL PROGRAMA PRINCIPAL
typedef enum {
    INIT = 0,
    WAIT_FOR_START,
    T1,
    T2
} main_state_t;

//ESTADOS DEL LED
typedef enum
{    
    START_BLINKING = 0,
    WAIT_TO_OFF,
    WAIT_TO_ON,
    WAIT_NEW_CYCLE
} led_state_t;


//Estados Externos de LED BLINKING
#define LED_NO_BLINKING               0
#define LED_STANDBY                   1
#define LED_GENERATING                2
#define LED_LOW_VOLTAGE               3
#define LED_PROTECTED                 4
#define LED_VIN_ERROR                 5
#define LED_OVERCURRENT_ERROR         6

/*--- Pins Defines ------------------------------------*/
#define LED_RED (PORTAbits.RA0)
#define LED_RED_ON    PORTAbits.RA0 = 1
#define LED_RED_OFF   PORTAbits.RA0 = 0

#define LED_GREEN (PORTAbits.RA1)
#define LED_GREEN_ON    PORTAbits.RA1 = 1
#define LED_GREEN_OFF   PORTAbits.RA1 = 0

#define RELAY (PORTAbits.RA2)
#define RELAY_ON    PORTAbits.RA2 = 1
#define RELAY_OFF   PORTAbits.RA2 = 0


/* Module Exported Functions ------------------------------*/
void ChangeLed (unsigned char);
void UpdateLed (void);

#endif
