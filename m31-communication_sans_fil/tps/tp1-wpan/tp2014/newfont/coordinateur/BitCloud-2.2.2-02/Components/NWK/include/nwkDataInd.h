/******************************************************************************
  nwkDataIndication.h
 Copyright (c)Meshnetics.
  Description: 
  History:
    14/06/07 V. Panov - Created.
******************************************************************************/
#ifndef _NWKDATAINDICATION_H
#define _NWKDATAINDICATION_H

/******************************************************************************
                        Includes section
******************************************************************************/
#include <nwk.h>
#include <mac.h>
#include <queue.h>
#include <nwkConfig.h>
#include <nwkFrame.h>
#include <nwkSystem.h>
#ifdef _SECURITY_
#include <sspSfp.h>
#endif

/******************************************************************************
                        Types section
******************************************************************************/
typedef enum _NwkDataIndState_t 
{
  DATA_IND_OBJ_FREE_STATE,
  DATA_IND_OBJ_PREPARE_TO_TRANSIT_STATE,
  DATA_IND_OBJ_PREPARE_TO_INDICATE_STATE,
  DATA_IND_OBJ_PREPARE_TO_BROADCAST_STATE,
  DATA_IND_OBJ_INDICATION_STATE,
  DATA_IND_OBJ_ROUTING_STATE,
  DATA_IND_OBJ_BROADCAST_STATE,
  DATA_IND_OBJ_WAIT_RESPONSE_STATE,
  DATA_IND_OBJ_WAIT_BROADCAST_RESPONSE_STATE,
  DATA_IND_OBJ_CMD_BUFFER_STATE,
  DATA_IND_OBJ_SR_BUFFER_STATE,
  DATA_IND_OBJ_DECRIPTING_STATE,
} NwkDataIndState_t;

typedef struct _NwkCommandReq_t
{
  struct { void *next; } service;
  uint8_t retryCounter;
  uint8_t baseJitter;
  uint8_t randomJitterMask;
  void (*prepareMacData)(uint8_t *data);
  void (*prepareMacReq)(MAC_DataReq_t *req);
  void (*confirm)(uint8_t status);
} NwkCommandReq_t;

typedef struct _NwkDataIndObj
{
  struct { 
    void *next;
  } service;

  union 
  {
    NWK_DataInd_t       dataInd;
    NwkParseHeader_t    parsedHeader;
    uint8_t             macHeader[MAC_MAX_DATA_FRAME_HEADER_LENGTH + 14];
  };
  uint8_t               data[MAC_MAX_MSDU_SIZE];

  uint8_t               length;
  struct {
  NwkDataIndState_t     state:8;
  };
  union
  {
    NwkCommandReq_t     *commandReq;
    struct 
    {
      uint8_t           linkQuality;
      uint8_t           rssi;
    };
  };

#ifdef _SECURITY_
  SSP_DecryptFrameReq_t decryptReq;
#endif
  bool decryptRequired;
} NwkDataIndObj_t;

typedef struct _NwkDataInd
{
  QueueDescriptor_t     commandQueue;
  union {
    NwkDataIndObj_t     *objects;
    DEFINE_DBG_ARRAY(NwkDataIndObj_t);
  };
  uint8_t               objectsSize;
  uint8_t               nhleFramesCounter;
  uint8_t               transitFramesCounter;
  uint8_t               commandReqFramesCounter;
  uint8_t               commandIndFramesCounter;

  uint16_t loadCounter;
} NwkDataInd_t;

/******************************************************************************
                        Prototypes section
******************************************************************************/

/******************************************************************************
  reset routine
******************************************************************************/
void nwkResetDataInd(void);

/******************************************************************************
  MAC event handler
******************************************************************************/
void MAC_DataInd(MAC_DataInd_t *macDataInd);

/******************************************************************************
  task handler
******************************************************************************/
void nwkDataIndTaskHandler(void);

/******************************************************************************
  confirm to data indication manager
  transit frame processed by data request manager
******************************************************************************/
void nwkDataIndTransitConf(NwkDataIndObj_t *dataIndObj);

/******************************************************************************
  confirm to data indication manager
  outgoing command frame processed by data request manager
   (outgoing frame allocated in data indication buffer)
******************************************************************************/
void nwkDataIndCommandConf(NwkDataIndObj_t *dataIndObj, uint8_t status);

/******************************************************************************
  request to perform outgoing command
   (outgoing frame allocated in data indication buffer)
******************************************************************************/
void nwkCommandReq(NwkCommandReq_t *req);

/******************************************************************************
******************************************************************************/
void nwkResetSourceRouteBuffer(void);

NwkDataIndObj_t* nwkDataIndSourceRouteBuffer(void);

#endif /* _NWKDATAINDICATION_H */
//eof nwkDataIndication.h
