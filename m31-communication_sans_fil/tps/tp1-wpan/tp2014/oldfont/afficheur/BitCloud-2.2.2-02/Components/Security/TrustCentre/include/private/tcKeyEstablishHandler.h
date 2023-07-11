/**************************************************************************//**
  \file
    tcKeyEstablishHandler.h
  \brief
    Trust Centre end to end key establishment routine header file.
  \internal
    Copyright (c)Meshnetics.
    History:
      2008.01.17 - ALuzhetsky created.
******************************************************************************/
#ifndef _TCKEYESTABLISHHANDLERH
#define _TCKEYESTABLISHHANDLERH

#ifdef _HIGH_SECURITY_
/******************************************************************************
                             Includes section.
******************************************************************************/
#include <aps.h>
#include <types.h>
#include <tcKeyEstablish.h>

/******************************************************************************
                             Definitions section.
******************************************************************************/


/******************************************************************************
                             Types section.
******************************************************************************/
/**************************************************************************//**
  \brief TBD.

  TBD
******************************************************************************/
typedef enum
{
  TC_KEY_ESTABLISH_OBJ_STATE_IDLE,
  TC_KEY_ESTABLISH_OBJ_STATE_TRANSPORT_KEY_POSTED,
  TC_KEY_ESTABLISH_OBJ_STATE_FIRST_TRANSPORT_KEY_EXECUTING,
  TC_KEY_ESTABLISH_OBJ_STATE_SECOND_TRANSPORT_KEY_EXECUTING,
} TcKeyEstablishHandlerObjState_t;

/**************************************************************************//**
  \brief TBD.

  TBD
******************************************************************************/
typedef struct PACK
{
  TC_KeyEstablishObj_t *keyEstablishObj;
  uint8_t              maxRequests;
} TcKeyEstablishHandlerMem_t;

/******************************************************************************
                             Functions prototypes section.
******************************************************************************/
/**************************************************************************//**
  \brief TBD.
  
  \param TBD.
  \return TBD.
******************************************************************************/
void tcKeyEstablishTaskHandler(void);

/**************************************************************************//**
  \brief TBD.
  
  \param TBD.
  \return TBD.
******************************************************************************/
void tcResetKeyEstablishHandler(void);

#endif // _HIGH_SECURITY_

#endif //_TCKEYESTABLISHHANDLERH
// eof tcKeyEstablishHandler.h
