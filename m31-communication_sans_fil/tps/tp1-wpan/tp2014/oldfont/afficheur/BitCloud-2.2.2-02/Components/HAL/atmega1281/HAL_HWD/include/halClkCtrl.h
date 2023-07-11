/******************************************************************************
  halClkCtrl.h
  Copyright (c)Meshnetics.

  Description: 
    Declarations of clock control hardware-dependent module.
  
  History:
    29/05/07 E. Ivanov - Created
******************************************************************************/

#ifndef HPLCLK_H_
#define HPLCLK_H_
#include <inttypes.h>
#include <avr/boot.h>
#include <types.h>
#include <halFCPU.h>

#define HAL_RC_OSCILLATOR_CLOCK 0x02 // defines fuse mask for RC oscillator

/******************************************************************************
Inits system clock.
******************************************************************************/
void halInitFreq(void);

/****************************************************************
System clock.
Returns:
  system clock in Hz.
****************************************************************/
INLINE uint32_t HAL_ReadFreq(void)
{ 
  return (uint32_t)F_CPU;
}

#endif /* HPLCLK_H_ */

// eof halClkCtrl.h
