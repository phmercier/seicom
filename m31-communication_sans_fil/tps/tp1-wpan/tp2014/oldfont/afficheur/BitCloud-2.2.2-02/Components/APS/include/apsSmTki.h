/*****************************************************************************
  apsSmTki.h

  Copyright (c)Meshnetics.

  Description:  
    APSME-TRANSPORT-KEY.indication feature header file. 
         
  History:
    07/11/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSSMTKI_H
#define _APSSMTKI_H

#ifdef _SECURITY_

#include <apsSecurityManager.h>

#ifdef _HIGH_SECURITY_
extern void apsSmTkiNwkDataInd(ApsSmBuffer_t *buffer);
#endif //#ifdef _HIGH_SECURITY_

extern bool apsSmTkiUnsecuredInd(NWK_DataInd_t *ind);
extern void apsSmTkiProcess(void);

#endif //#ifdef _SECURITY_

#endif  //#ifndef _APSSMTKI_H

//eof apsSmTki.h

