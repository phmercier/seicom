/*****************************************************************************
  apsSmAui.h

  Copyright (c)Meshnetics.

  Description:  
    APSME-AUTHENTICATE.indication feature header file. 
         
  History:
    07/11/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSSMAUI_H
#define _APSSMAUI_H

#ifdef _SECURITY_
#ifdef _HIGH_SECURITY_

#include <aps.h>

extern void apsSmAuiReqHandler(APS_AuthenticateReq_t *req);
extern bool apsAuiNwkDataInd(NWK_DataInd_t *ind);
extern void apsSmAuiProcess(void);
extern void apsResetSmAui(void);
extern void apsSmAuiTimeoutHandler(ApsSmBuffer_t *sspReq);

#endif //#ifdef _HIGH_SECURITY_
#endif //#ifdef _SECURITY_

#endif //#ifndef _APSSMAUI_H

//eof apsSmAui.h

