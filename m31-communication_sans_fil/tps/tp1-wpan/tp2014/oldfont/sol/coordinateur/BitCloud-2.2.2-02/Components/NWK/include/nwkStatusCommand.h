/******************************************************************************
  nwkStatusCommand.h
  Copyright (c)Meshnetics.

  Description:
              
******************************************************************************/

#ifndef _NWKSTATUSCOMMAND_H
#define _NWKSTATUSCOMMAND_H

#include <nwk.h>
#include <queue.h>
#include <nwkCommands.h>

typedef enum _NwkCommandState_t
{
  NETWORK_COMMAND_IDLE_STATE,
  NETWORK_COMMAND_WAIT_CONFIRM_STATE,
  NETWORK_COMMAND_CONFIRMED_STATE,
  NETWORK_COMMAND_LOCAL_CONFLICT_STATE,
} NwkCommandState_t;

typedef enum _NwkCommandDestMode_t
{
  UNICAST_DEST_MODE,
  BROADCAST_DEST_MODE,
} NwkCommandDestMode_t;

typedef struct _NwkCommandOptions_t
{
  uint8_t count     : 4;
  uint8_t commandId : 4;
} NwkCommandOptions_t;

BEGIN_PACK
typedef struct PACK _NwkStatusCommandPayload_t
{
  uint8_t           commandId;
  uint8_t           statusCode;
  ShortAddr_t       dstAddr;
} NwkStatusCommandPayload_t;
END_PACK

typedef struct _NwkStatusCommandConf_t
{
  uint8_t status;
} NwkStatusCommandConf_t;

typedef struct _NwkStatusCommandReq_t
{
  struct
  {
    void *next; // pointer used for queuing
  } service;
  
  NwkCommandDestMode_t      destMode;
  ShortAddr_t               dstShortAddr; 
  ExtAddr_t                 dstExtAddr;            
  uint8_t                   statusCode;
  ShortAddr_t               shortAddr;  
  NwkStatusCommandConf_t    confirm;
  void (*nwkStatusCommandConf)(NwkStatusCommandConf_t *confirmParams);
} NwkStatusCommandReq_t;

typedef struct _NwkStatusCommand_t
{
  QueueDescriptor_t     queue;
  struct {
  NwkCommandState_t     state:8;  
  };
  NwkStatusCommandReq_t *req;
  MAC_SetReq_t          setReq;  
  NwkCommandReq_t       commandReq;
} NwkStatusCommand_t;

void nwkSendStatusCommand(NwkStatusCommandReq_t *req);

/******************************************************************************
  task handler
******************************************************************************/
void nwkStatusCommandTaskHandler(void);

/******************************************************************************
  reset routine
******************************************************************************/
void nwkResetStatusCommand(void);

/***********************************************************************************
  network status command has been received.

  Parameters:
    payload - command payload pointer
    header  - command parameters
    parse   - source and destination extended address pointers
  
  Return:
    none
  
 ***********************************************************************************/
void nwkStatusFrameInd(uint8_t *payload, NwkFrameHeader_t *header, NwkParseHeader_t *parse);

#endif /*_NWKSTATUSCOMMANDS_H*/
