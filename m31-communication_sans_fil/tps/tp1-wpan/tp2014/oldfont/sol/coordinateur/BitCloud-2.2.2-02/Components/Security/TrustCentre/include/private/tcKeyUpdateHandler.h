/**************************************************************************//**
  \file
    tcKeyUpdateHandler.h
  \brief
    Trust Centre key update routine header file.
  \internal
    Copyright (c)Meshnetics.
    History:
      2008.01.11 - ALuzhetsky created.
******************************************************************************/
#ifndef _TCKEYUPDATEHANDLERH
#define _TCKEYUPDATEHANDLERH

/******************************************************************************
                        Includes section.
******************************************************************************/
#include <queue.h>
#include <appTimer.h>
#include <aps.h>

typedef struct PACK
{
  QueueDescriptor_t reqQueueDescr;
  uint8_t           deviceIndex;
  void              *currentReq;
  union
  {
    APS_TransportKeyReq_t transportKeyReq;
    APS_SwitchKeyReq_t    switchKeyReq;
    HAL_AppTimer_t        keyUpdateTimer;
  };
} TcKeyUpdateHandlerMem_t;

/******************************************************************************
                        Functions prototypes section.
******************************************************************************/
/**************************************************************************//**
  \brief TBD.
  
  \param TBD.
  \return TBD.
******************************************************************************/
void tcKeyUpdateTaskHandler(void);

/**************************************************************************//**
  \brief TBD.
  
  \param TBD.
  \return TBD.
******************************************************************************/
void tcResetKeyUpdateHandler(void);

#endif //_TCKEYUPDATEHANDLERH
// eof tcKeyUpdateHandler.h
