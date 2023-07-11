/**************************************************************************//**
  \file
    tcRemoveHandler.h
  \brief
    Trust Centre device remove routine header file.
  \internal
    Copyright (c)Meshnetics.
    History:
      2008.01.20 - ALuzhetsky created.
******************************************************************************/
#ifndef _TCREMOVEHANDLERH
#define _TCREMOVEHANDLERH

/******************************************************************************
                             Includes section.
******************************************************************************/
#include <queue.h>
#include <aps.h>
#include <types.h>
#include <tcRemove.h>


/******************************************************************************
                             Definition section.
******************************************************************************/
/******************************************************************************
                             Types section.
******************************************************************************/
/**************************************************************************//**
  \brief TBD.

  TBD
******************************************************************************/
typedef struct PACK
{
  QueueDescriptor_t     reqQueueDescr;
  APS_RemoveDeviceReq_t removeDeviceReq;
  TC_RemoveDeviceReq_t *currentReq;
} TcRemoveHandlerMem_t;

/******************************************************************************
                             Functions prototypes section.
******************************************************************************/
/**************************************************************************//**
  \brief TBD.
  
  \param TBD.
  \return TBD.
******************************************************************************/
void tcUpdateDeviceIndToRemoveHandler(APS_UpdateDeviceInd_t *indParam);

/**************************************************************************//**
  \brief TBD.
  
  \param TBD.
  \return TBD.
******************************************************************************/
void tcRemoveTaskHandler(void);

/**************************************************************************//**
  \brief TBD.
  
  \param TBD.
  \return TBD.
******************************************************************************/
void tcResetRemoveHandler(void);


#endif //_TCREMOVEHANDLERH

// eof tcRemoveHandler.h
