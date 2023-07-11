/*********************************************************************************
  halDbg.h 
  Copyright (c)Meshnetics.

  Description:
    Declarations of hal , bsb mistake interface.
          
  History:
    09/11/07 A. Khromykh - Created
**********************************************************************************/

#ifndef _HALDBG_H
#define _HALDBG_H

#include <dbg.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
enum
{
  APPTIMER_MISTAKE =         0x2000,
  INCORRECT_EEPROM_ADDRESS = 0x2001,
  MEMORY_CANNOT_WRITE =      0x2002
};

/******************************************************************************
                   Prototypes section
******************************************************************************/

#endif /* _HALDBG_H */

// eof halDbg.h
