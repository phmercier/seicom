/*****************************************************************************
  apsSmRdr.h

  Copyright (c)Meshnetics.

  Description:  
    APSME-REMOVE-DEVICE.request feature header file. 
         
  History:
    07/11/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSSMRDR_H
#define _APSSMRDR_H

#ifdef _SECURITY_

extern void apsSmRdrProcess(void);
extern void apsSmRdrSspConf(ApsSmBuffer_t *buffer, uint8_t status);
extern void apsResetSmRdr(void);

#endif  //#ifdef _SECURITY_

#endif  //#ifndef _APSSMUDR_H

//eof apsSmRdr.h

