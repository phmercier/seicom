/*****************************************************************************
  apsSmSkr.h

  Copyright (c)Meshnetics.

  Description:  
    APSME-SWITCH-KEY.request feature header file. 
         
  History:
    07/11/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSSMSKR_H
#define _APSSMSKR_H

#ifdef _SECURITY_

extern void apsSmSkrProcess(void);
extern void apsSmSkrSspConf(ApsSmBuffer_t *buffer, uint8_t status);
extern void apsResetSmSkr(void);

#endif  //#ifdef _SECURITY_

#endif  //#ifndef _APSSMSKR_H

//eof apsSmSkr.h

