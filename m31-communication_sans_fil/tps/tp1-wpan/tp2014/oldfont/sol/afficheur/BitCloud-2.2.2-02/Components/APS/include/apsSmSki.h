/*****************************************************************************
  apsSmSki.h

  Copyright (c)Meshnetics.

  Description:  
    APSME-SWITCH-KEY.indication feature header file. 
         
  History:
    07/11/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSSMSKI_H
#define _APSSMSKI_H

#ifdef _SECURITY_

#include <apsSecurityManager.h>

#ifdef _HIGH_SECURITY_
extern void apsSmSkiNwkDataInd(ApsSmBuffer_t *buffer);
#endif //#ifdef _HIGH_SECURITY_

extern bool apsSmSkiUnsecuredInd(NWK_DataInd_t *ind);


#endif //#ifdef _SECURITY_

#endif  //#ifndef _APSSMSKI_H

//eof apsSmSki.h

