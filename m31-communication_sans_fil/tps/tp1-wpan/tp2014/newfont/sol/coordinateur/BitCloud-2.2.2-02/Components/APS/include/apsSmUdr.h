/*****************************************************************************
  apsSmUdr.h

  Copyright (c)Meshnetics.

  Description:  
    APSME-UPDATE-DEVICE.request feature header file. 
         
  History:
    07/11/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSSMUDR_H
#define _APSSMUDR_H

#ifdef _SECURITY_

extern void apsSmUdrProcess(void);
#ifdef _HIGH_SECURITY_
extern void apsSmUdrSspConf(ApsSmBuffer_t *buffer, uint8_t status);
#endif
extern void apsResetSmUdr(void);

#endif  //#ifdef _SECURITY_

#endif  //#ifndef _APSSMUDR_H

//eof apsSmUdr.h

