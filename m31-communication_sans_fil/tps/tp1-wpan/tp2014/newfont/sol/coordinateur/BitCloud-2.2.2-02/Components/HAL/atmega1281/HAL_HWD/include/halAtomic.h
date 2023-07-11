/******************************************************************************
  atomic.h
  Copyright (c)Meshnetics.

  Description: 
    Implementation of atomic sections.
  History:     
    29/05/07 E. Ivanov - Created
******************************************************************************/

#ifndef _HALATOMIC_H
#define _HALATOMIC_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <types.h>

typedef  uint8_t atomic_t;

/******************************************************************************
Saves global interrupt bit. Disables global interrupt.
Parameters:
  none.
Returns:
  none.
******************************************************************************/
INLINE atomic_t halStartAtomic()
{
  atomic_t result = SREG;
  cli();
  return result;
}

/******************************************************************************
Restores global interrupt.
Parameters:
  none.
Returns:
  none.
******************************************************************************/
INLINE void halEndAtomic(atomic_t sreg)
{
  SREG = sreg;
}

#endif /* _HALATOMIC_H */
// eof atomic.h

