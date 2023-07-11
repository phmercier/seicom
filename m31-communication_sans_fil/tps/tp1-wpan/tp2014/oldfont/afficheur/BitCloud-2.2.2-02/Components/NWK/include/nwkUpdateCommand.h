/******************************************************************************
  nwkUpdateCommand.h
  Copyright (c) 2008 Meshnetics.

  Description:
              
******************************************************************************/

#ifndef _NWKUPDATECOMMAND_H
#define _NWKUPDATECOMMAND_H

#include <nwkStatusCommand.h>
#include <nwkReportCommand.h>
#include <appTimer.h>

typedef struct _PanIdUpdate_t
{
  PanId_t panid;
} PanIdUpdate_t;

typedef struct _NetworkUpdate_t
{
  uint32_t channelMask;
  uint8_t  selectedChannel;
} NetworkUpdate_t;

typedef struct _NwkUpdateCommandConf_t
{
  uint8_t status;
} NwkUpdateCommandConf_t;

typedef struct _NwkUpdateCommandReq_t
{
  struct
  {
    void *next; // pointer used for queuing
  } service;
  
  NwkCommandOptions_t options;
  union
  {
    PanIdUpdate_t   panidUpdate;
    NetworkUpdate_t networkUpdate;
  };
  NwkUpdateCommandConf_t     confirm;
  void (*nwkUpdateCommandConf)(NwkUpdateCommandConf_t *confirmParams);
} NwkUpdateCommandReq_t;

typedef struct _NwkUpdateCommand_t
{
  QueueDescriptor_t     queue;
  struct {
  NwkCommandState_t     state:8;  
  };
  uint8_t               indState;   
  NwkUpdateCommandReq_t *req;
  NwkCommandReq_t       commandReq;
  PanId_t               newPanId;
  union
  {
    HAL_AppTimer_t        waitTimer;
    MAC_SetReq_t          macSetReq;
  };
} NwkUpdateCommand_t;

/******************************************************************************
  task handler
******************************************************************************/
void nwkUpdateCommandTaskHandler(void);
void nwkResetUpdateCommand(void);
void nwkSendUpdateCommand(NwkUpdateCommandReq_t *req);
void nwkUpdateFrameInd(uint8_t *payload, NwkFrameHeader_t *header, NwkParseHeader_t *parse);

#endif /*NWKUPDATECOMMAND_H_*/
