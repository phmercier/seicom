/******************************************************************************
  zdoZdpManager.h  
  Copyright (c) 2008 Meshnetics.

  Description:
              
*******************************************************************************/
#ifndef _ZDOZDPMANAGER_H
#define _ZDOZDPMANAGER_H

#include <queue.h>
#include <appTimer.h>
#include <zdoZdpFrameProcessor.h> 

#define ZDP_CLUSTER_MASK 0x0FFF
#define ZDP_WAITRESPONSE_INTERVAL 2000

typedef enum
{
  ZDO_IDLE_ZDP_MANAGER_STATE,
  ZDO_REQUEST_SENDING_ZDP_MANAGER_STATE,
  ZDO_CONFIRM_ZDP_MANAGER_STATE,
  ZDO_WAITING_RESPONSE_ZDP_MANAGER_STATE,
  ZDO_WAITING_CONFIRM_ZDP_MANAGER_STATE
} ZDO_ZdpManagerState_t;

typedef struct
{
  uint8_t status;
} ZdoZdpResetConf_t;

typedef struct 
{
  ZdoZdpResetConf_t conf;
} ZdoZdpResetReq_t;

typedef struct 
{
  QueueDescriptor_t     requestQueue;
  ZDO_ZdpManagerState_t requestState;
  ZDO_ZdpReq_t          *zdpRequest;
  uint8_t               requestSeqNum;
  HAL_AppTimer_t        waitResponseTimer;
  APS_DataInd_t         *zdpReceivedReq;
  ZDO_ZdpFrame_t        zdpFrame;
  ZdpMessageReq_t       zdpRequestMessage;
  ZdpMessageReq_t       zdpResponseMessage;
} ZdoZdpManager_t;

void zdoZdpResetReq(ZdoZdpResetReq_t *reset);

#endif /*ZDOZDPMANAGER_H_*/
