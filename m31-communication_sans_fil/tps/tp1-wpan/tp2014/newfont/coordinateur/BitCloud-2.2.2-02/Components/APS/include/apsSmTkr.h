/*****************************************************************************
  apsSmTkr.h

  Copyright (c)Meshnetics.

  Description:  
    APSME-TRANSPORT-KEY.request feature header file. 
         
  History:
    07/11/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSSMTKR_H
#define _APSSMTKR_H

#ifdef _SECURITY_

extern void apsSmTkrProcess(void);
extern void apsSmTkrSspConf(ApsSmBuffer_t *buffer, uint8_t status);
extern void apsResetTkr(void);
extern ShortAddr_t *apsFindNextNeibRxOffWhenIdleShortAddr(ShortAddr_t *shortAddr);
extern ExtAddr_t *apsFindNextNeibRxOffWhenIdleExtAddr(ExtAddr_t *extAddr);

#endif  //#ifdef _SECURITY_

#endif  //#ifndef _APSSMTKR_H

//eof apsSmTkr.h

