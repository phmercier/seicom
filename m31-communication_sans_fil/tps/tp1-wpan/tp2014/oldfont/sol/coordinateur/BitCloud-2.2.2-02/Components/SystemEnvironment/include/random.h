/******************************************************************************
  random.h
  Copyright (c)Meshnetics.

  Description:
    Interface to the generator of random numbers.

  History:
    29/06/07 E. Ivanov - Created
******************************************************************************/

#ifndef _RANDOM_H
#define _RANDOM_H

#include <types.h>
#include <stdlib.h>
#include <appTimer.h>

/******************************************************************************
Random number generator.
The range of the generator is 0-7FFFF.
The SID is generated in ZDO from UID by srand()
Parameters:
  none.
Returns:
  a random number.
******************************************************************************/
static inline uint16_t SYS_GetRandomNumber()
{
  return rand();
}
#endif
//eof random.h
