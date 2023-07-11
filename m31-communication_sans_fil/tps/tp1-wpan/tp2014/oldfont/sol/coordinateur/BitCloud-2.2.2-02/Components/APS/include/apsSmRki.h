/*****************************************************************************
  apsSmRki.h

  Copyright (c)Meshnetics.

  Description:  
    APSME-REQUEST-KEY.indication feature header file. 
         
  History:
    07/11/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSSMRKI_H
#define _APSSMRKI_H

#ifdef _SECURITY_
#ifdef _HIGH_SECURITY_

#include <apsSecurityManager.h>
extern void apsSmRkiInd(ApsSmBuffer_t *buffer);
extern bool apsSmRkiUnsecuredInd(NWK_DataInd_t *ind);

#endif //#ifdef _HIGH_SECURITY_
#endif //#ifdef _SECURITY

#endif  //#ifndef _APSSMRDI_H

//eof apsSmRki.h

