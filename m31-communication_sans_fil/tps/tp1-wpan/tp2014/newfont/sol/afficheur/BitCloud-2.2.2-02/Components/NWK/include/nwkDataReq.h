/******************************************************************************
  nwkDataRequest.h
  Copyright (c)Meshnetics.
  Description: 
    data request source file.
  History:
    14/06/07 V. Panov - Created.
******************************************************************************/
#ifndef _NWKDATAREQUEST_H
#define _NWKDATAREQUEST_H

/******************************************************************************
                        Includes section
******************************************************************************/
#include <nwk.h>
#include <nwkDataInd.h>
#include <appTimer.h>
#include <nwkRouting.h>
#include <nwkSystem.h>
#include <nwkStatusCommand.h>
#ifdef _SECURITY_
#include <sspSfp.h>
#endif

/******************************************************************************
                        Types section
******************************************************************************/
typedef enum _NwkDataReqState_t
{
  DATA_REQ_OBJ_FREE_STATE,
  DATA_REQ_OBJ_REQUEST_STATE,
  DATA_REQ_OBJ_RESERVED_STATE,
  DATA_REQ_OBJ_ROUTING_WAIT_STATE,
  DATA_REQ_OBJ_ROUTING_DONE_STATE,
  DATA_REQ_OBJ_MACREQUEST_STATE,
  DATA_REQ_OBJ_ENCRIPTING_STATE,
  DATA_REQ_OBJ_MACREQUEST_REPEAT_STATE,
  DATA_REQ_OBJ_WAIT_STATE,
  DATA_REQ_OBJ_DECRIPTING_STATE,
  DATA_REQ_OBJ_CONFIRMING_STATE,
  DATA_REQ_OBJ_DELAY_STATE,
  DATA_REQ_OBJ_WAIT_TIMER_STATE,
  DATA_REQ_OBJ_USE_SOURCE_ROUTING,
} NwkDataReqState_t;


typedef struct _NwkDataReqObj_t
{
  union {
    NWK_DataReq_t   *nwkDataReq;
    NwkDataIndObj_t *dataIndObj;
  };
  MAC_DataReq_t     macDataReq;
  struct {
  NwkDataReqState_t state:8;
  };
  uint8_t           retryCounter;
  struct {
    bool            fromNhle  ;//:1;
    bool            transit   ;//:1;
    bool            command   ;//:1;
    bool            broadcast ;//:1;
    bool            indirect  ;//:1;
    bool            discoveryRequired;//:1;
    bool            sourceRouted;
    bool            decryptRequired;
  };
  Neib_t* edToRebroadcast;

  NwkFindRouteReq_t findRouteReq;
#ifdef _SECURITY_
  SSP_EncryptFrameReq_t encryptReq;
  SSP_DecryptFrameReq_t decryptReq;
#endif
} NwkDataReqObj_t;

typedef struct _NwkDataReq_t
{
  QueueDescriptor_t queue, 
                    transitQueue, 
                    commandQueue;
  QueueDescriptor_t queueIndir, 
                    transitQueueIndir,
                    commandQueueIndir;
  union {
    NwkDataReqObj_t *objects;
    DEFINE_DBG_ARRAY(NwkDataReqObj_t);
  };
  uint8_t           objectsSize;
  uint8_t           maxRetryCounter;
  HAL_AppTimer_t    delayTimer;
  bool              timerActive;
  NwkStatusCommandReq_t statusReq;
  bool                  statusReqActive;
} NwkDataReq_t;

/******************************************************************************
                        Prototypes section
******************************************************************************/

/******************************************************************************
  standard request
******************************************************************************/
void NWK_DataReq(NWK_DataReq_t *nwkDataReq);

/******************************************************************************
  reset routine
******************************************************************************/
void nwkResetDataReq(void);

/******************************************************************************
  task handler
******************************************************************************/
void nwkDataReqTaskHandler(void);

/******************************************************************************
  request to resend transit data
 (it is from & will be confirmed to dataindication)
******************************************************************************/
void nwkDataReqTransit(NwkDataIndObj_t *dataIndObj);

/******************************************************************************
  request to resend command frame
 (it is from & will be confirmed to dataindication)
******************************************************************************/
void nwkDataReqCommand(NwkDataIndObj_t *dataIndObj);

void nwkDataReqFlushConfirms(void);

bool nwkDataReqCheckReserved(void);

#endif
// eof dataRequest.h
