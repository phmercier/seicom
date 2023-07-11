/******************************************************************************
  sleep.h
  Copyright (c)Meshnetics.

  Description:
    Interface to control power save mode.

  History:
    29/06/07 E. Ivanov - Created
*******************************************************************************/
#ifndef _SLEEP_H
#define _SLEEP_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <avr/io.h>

/******************************************************************************
                   Types section
******************************************************************************/
//it is used for reliable wake up
typedef enum
{
  ACTIVE_MODE,
  SLEEP_MODE
} WakeupStation_t;

/******************************************************************************
                   Prototypes section
******************************************************************************/
/*******************************************************************************
  Disconnects TRSLEEP pin from comparator output.
*******************************************************************************/
void halPowerOn(void);

/*******************************************************************************
  Shutdown system.
  NOTES:
  the application should be sure the poweroff will not be 
  interrupted after the execution of the sleep().
*******************************************************************************/
void halPowerOff(void);

/******************************************************************************
  Prepares system for power-save, power-down.
  Power-down the mode is possible only when internal RC is used
  Parametres:
  none.
  Returns:
  -1 there is no possibility to power-down system.
******************************************************************************/
int HAL_Sleep(void);

/******************************************************************************
                   Inline static functions section 
******************************************************************************/
/*******************************************************************************
  Makes MCU enter Idle mode.
*******************************************************************************/
INLINE void HAL_IdleMode(void)
{
  SMCR = 0x1;
  asm volatile ("sleep");
  SMCR = 0;
}

#endif /* _SLEEP_H */
// eof sleep.h
