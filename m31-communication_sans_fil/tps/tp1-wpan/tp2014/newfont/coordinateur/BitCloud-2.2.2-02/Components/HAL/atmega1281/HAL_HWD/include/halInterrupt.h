/******************************************************************************
  halInterrupt.h
  Copyright (c)Meshnetics.

  Description:
   Macroses to manipulate global interrupts.
          
  History:
    29/05/07 E. Ivanov - Created
******************************************************************************/

#ifndef HALINTERRUPT_H_
#define HALINTERRUPT_H_
#include <avr/interrupt.h>

/******************************************************************************
Enables global interrupt.
******************************************************************************/
#define HAL_EnableInterrupts() sei()

/******************************************************************************
Disables global interrupt.
******************************************************************************/
#define HAL_DisableInterrupts() cli()

#endif
// eof halInterrupt.h
