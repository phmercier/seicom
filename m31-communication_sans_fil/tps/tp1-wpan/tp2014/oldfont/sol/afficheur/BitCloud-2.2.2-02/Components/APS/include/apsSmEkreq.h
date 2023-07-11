/*****************************************************************************
  apsSmEkreq.h

  Copyright (c)Meshnetics.

  Description:  
    APSME-ESTABLISH-KEY.request feature header file. 
         
  History:
    07/11/07 A. Potashov - Created.
*****************************************************************************/


#ifndef _APSSMEKREQ_H
#define _APSSMEKREQ_H

#ifdef _SECURITY_
#ifdef _HIGH_SECURITY_

#include <aps.h>

extern bool apsSmEkreqNwkDataInd(NWK_DataInd_t *ind);
extern void apsResetSmEkreq(void);
extern void apsSmEkreqProcess(void);
extern void apsSmEkreqTimeoutHandler(ApsSmBuffer_t *sspReq);

#endif //#ifdef _HIGH_SECURITY_
#endif //#ifdef _SECURITY_

#endif  //#ifndef _APSSMKEREQ_H

//eof apsSmEkreq.h

