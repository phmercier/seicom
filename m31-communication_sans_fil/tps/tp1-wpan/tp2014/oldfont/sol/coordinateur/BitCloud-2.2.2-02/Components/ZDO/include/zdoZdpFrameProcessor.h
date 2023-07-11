/******************************************************************************
  zdoZdpFrameProcessor.h

  Copyright (c)Meshnetics.

  Description:
    ZDP Frame Processor

  History:
    28/11/07 A. Zemlyanov - Created.
******************************************************************************/
#ifndef _ZDP_FRAME_PROCESSOR_H
#define _ZDP_FRAME_PROCESSOR_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <types.h>
#include <queue.h>
#include <zdo.h>
#include <zdoDbg.h>
#include <aps.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/

/******************************************************************************
                   Types section
******************************************************************************/
typedef void (*ZdoAPSDataConf_t)(APS_DataConf_t *conf);

typedef enum zdoFrameProcState_t_
{
  ZDO_FRAME_REQ_NONE,     // No request is being processed
  ZDO_FRAME_REQ_PENDING,  // Request is being processed
  ZDO_FRAME_REQ_CALLBACK  // Callback is called
} ZdoFrameProcState_t;

typedef struct ZdpMessageReq_t_
{
  struct 
  {
    void *next;
  } service;
  
  void (*prepareZdpMessage)(APS_DataReq_t *apsDataReq);
  void (*zdpMessageConfirm)(APS_DataConf_t *apsDataConf);
} ZdpMessageReq_t;


typedef struct zdoFrameProc_t_
{
  // Outgoing requests
  ZdoFrameProcState_t     reqState;     // State of request processing
  QueueDescriptor_t       reqQueue;     // Queue of pending requests
  APS_DataReq_t           reqDataReq;

  // Incoming data from APS
  ZdoFrameProcState_t     apsState;                       // State of APS frame processing
  APS_DataInd_t           apsDataInd;                     // Data indication struct
  uint8_t                 apsAsduBuff[APS_MAX_ASDU_SIZE]; // Buffer for inconing APS ASDU
} ZdoFrameProc_t;


/******************************************************************************
                   Prototypes section
******************************************************************************/
/******************************************************************************
 Reset the ZDP Frame Processor into initial state
 Parameters:
   None
 Returns:
   None.
******************************************************************************/
extern void zdoZdpFrameProcessorReset(void);

/******************************************************************************
 Send ZDP request
 Parameters:
   sendReq - Pointer to ZdpSendReq_t type object
 Returns:
   None.
******************************************************************************/
extern void zdoZdpSendRequest(ZdpMessageReq_t *sendReq);

/******************************************************************************
 Process incoming ZDP frames data from APS layer
 Parameters:
   apsInd - Pointer to APS_DataInd_t type object
 Returns:
   None.
******************************************************************************/
extern void APS_ZdoDataInd(APS_DataInd_t *apsInd);

/******************************************************************************
 To be called when gets frame from APS
 Parameters:
   apsInd - Pointer to APS_DataInd_t type object
 Returns:
   None.
******************************************************************************/
extern void zdoZdpMessageInd(APS_DataInd_t *dataInd);

/******************************************************************************
 Confirms that ZDP finished processing of received message
 Parameters:
   None
 Returns:
   None.
******************************************************************************/
extern void zdoZdpMessageResp(void);

#endif /* _ZDP_FRAME_PROCESSOR_H */
