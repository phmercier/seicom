/******************************************************************************/
/** \file  uid.h
  
\brief
    Declaration of the UID interface.

\internal  
  Copyright (c)Meshnetics.
  History:
    7/12/07 A. Khromykh - Created
*******************************************************************************/

#ifndef _UID_H
#define _UID_H

/******************************************************************************
                   Includes section
******************************************************************************/
// \cond
#include <types.h>
// \endcond

/******************************************************************************
                   Prototypes section
******************************************************************************/
/************************************************************//**
\brief  UID discovery.
\param[in]
    id - UID buffer pointer. \n
    Attention! Memory size must be equal to (Number of devices) * 8 bytes
\return
    0 - if UID of DS2411 has been found successfully; \n
   -1 - if some error occured during UID discovery.
****************************************************************/
int HAL_ReadUid(uint64_t *id);

#endif /* _UID_H */

// eof uid.h
