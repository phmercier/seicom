/*****************************************************************************
  apsSmUdi.h

  Copyright (c)Meshnetics.

  Description:  
    APSME-UPDATE-DEVICE.indication feature headder file. 
         
  History:
    07/11/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSSMUDI_H
#define _APSSMUDI_H

#ifdef _SECURITY_

#include <apsSecurityManager.h>

#ifdef _HIGH_SECURITY_
extern void apsSmUdiNwkDataInd(ApsSmBuffer_t *buffer);
#endif //#ifdef _HIGH_SECURITY_

extern bool apsSmUdiUnsecuredInd(NWK_DataInd_t *ind);

#endif //#ifdef _SECURITY_

#endif  //#ifndef _APSSMUDI_H

//eof apsSmUdi.h

