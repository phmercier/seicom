/*****************************************************************************
  apsSmAur.h

  Copyright (c)Meshnetics.

  Description:  
    APSME-AUTHENTICATE.request feature header file. 
         
  History:
    07/11/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSSMAUR_H
#define _APSSMAUR_H

#ifdef _SECURITY_
#ifdef _HIGH_SECURITY_

#include <aps.h>

extern bool apsAurNwkDataInd(NWK_DataInd_t *ind);
extern void apsResetSmAur(void);
extern void apsSmAurProcess(void);
extern void sendAuc(ApsSmBuffer_t *sspReq, APS_AuthenticateStatus_t status);
extern void apsSmAurTimeoutHandler(ApsSmBuffer_t *sspReq);

#endif //#ifdef _HIGH_SECURITY_
#endif //#ifdef _SECURITY_

#endif  //#ifndef _APSSMKEREQ_H

//eof apsSmAur.h

