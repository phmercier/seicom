/*****************************************************************************
  apsSmEkresp.h

  Copyright (c)Meshnetics.

  Description:  
    SKKE Protocol Responder Role features header file. 
         
  History:
    07/11/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSSMEKRESP_H
#define _APSSMEKRESP_H

#ifdef _SECURITY_
#ifdef _HIGH_SECURITY_

#include <aps.h>

extern bool apsSmEkrespNwkDataInd(NWK_DataInd_t *ind);
extern void apsSmEkrespProcess(void);
extern void apsResetSmEkresp(void);
extern void apsSmEkrespTimeoutHandler(ApsSmBuffer_t *sspReq);

#endif //#ifdef _HIGH_SECURITY_
#endif //#ifdef _SECURITY_

#endif //#ifndef _APSSMEKRESP_H

//eof apsSmEkresp.h


