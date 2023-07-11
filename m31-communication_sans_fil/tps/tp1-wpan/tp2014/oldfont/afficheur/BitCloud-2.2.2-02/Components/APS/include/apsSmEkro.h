/*****************************************************************************
  apsSmEkro.h

  Copyright (c)Meshnetics.

  Description:  
    SKKE Protocol Routing feature header file. 
         
  History:
    07/11/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSSMEKRO_H
#define _APSSMEKRO_H

#ifdef _SECURITY_
#ifdef _HIGH_SECURITY_

#include <aps.h>

extern void apsSmEkroProcess(void);
extern bool apsSmEkroNwkDataInd(NWK_DataInd_t *ind);
extern void apsResetSmEkro(void);

#endif //#ifdef _HIGH_SECURITY_
#endif //#ifdef _SECURITY_

#endif  //#ifndef _APSSMEKRO_H

//eof apsSmEkro.h

