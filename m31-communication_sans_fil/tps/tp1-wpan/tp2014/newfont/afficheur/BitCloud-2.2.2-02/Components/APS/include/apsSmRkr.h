/*****************************************************************************
  apsSmRkr.h

  Copyright (c)Meshnetics.

  Description:  
    APSME-REQUEST-KEY.request feature header file. 
         
  History:
    07/11/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSSMRKR_H
#define _APSSMRKR_H

#ifdef _SECURITY_
#ifdef _HIGH_SECURITY_

extern void apsSmRkrProcess(void);
extern void apsSmRkrSspConf(ApsSmBuffer_t *buffer, uint8_t status);
extern void apsResetSmRkr(void);

#endif  //#ifdef _HIGH_SECURITY_
#endif  //#ifdef _SECURITY_

#endif  //#ifndef _APSSMRKR_H

//eof apsSmRkr.h

