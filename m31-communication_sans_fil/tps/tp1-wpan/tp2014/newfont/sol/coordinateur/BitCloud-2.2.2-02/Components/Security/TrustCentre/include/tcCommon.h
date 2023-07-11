/**************************************************************************//**
  \file 
    tcCommon.h
  \brief
    Trust Centre common types and definitions header file.
  \internal
    Copyright (c)Meshnetics.
    History:
      2008.12.01 - ALuzhetsky created.
******************************************************************************/
#ifndef _TCCOMMONH
#define _TCCOMMONH

/**************************************************************************//**
  \brief Trust Centre service field.

   Service field - for internal needs - to store requets in the requets' queue.
******************************************************************************/
typedef struct PACK
{
  void *next;
} TC_Service_t;

#endif // _TCCOMMONH
// eof tcCommon.h
