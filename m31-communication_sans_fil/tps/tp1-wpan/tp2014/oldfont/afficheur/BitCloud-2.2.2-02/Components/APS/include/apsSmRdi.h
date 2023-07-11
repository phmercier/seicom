/*****************************************************************************
  apsSmRdi.h

  Copyright (c)Meshnetics.

  Description:  
    APSME-REMOVE-DEVICE.indication feature header file. 
         
  History:
    07/11/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSSMRDI_H
#define _APSSMRDI_H

#ifdef _SECURITY_

#include <apsSecurityManager.h>

#ifdef _HIGH_SECURITY_
extern void apsSmRdiNwkDataInd(ApsSmBuffer_t *buffer);
#endif //#ifdef _HIGH_SECURITY_

extern bool apsSmRdiUnsecuredNwkDataInd(NWK_DataInd_t *ind);

#endif //#ifdef _SECURITY_

#endif  //#ifndef _APSSMRDI_H

//eof apsSmRdi.h

