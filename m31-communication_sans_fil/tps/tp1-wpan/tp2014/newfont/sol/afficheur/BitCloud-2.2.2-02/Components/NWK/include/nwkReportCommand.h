/******************************************************************************
  nwkReportCommand.h
  Copyright (c)Meshnetics.

  Description:
              
******************************************************************************/

#ifndef _NWKREPORTCOMMAND_H
#define _NWKREPORTCOMMAND_H

#include <nwkStatusCommand.h>
#include <nwkUpdateCommand.h>

enum
{
  IDLE_STATE,
  PROCESSING_STATE
};

enum
{
  PANID_CONFLICT     = 0x00,
  LOCAL_INTERFERENCE = 0x01,
};

typedef struct _PanIdConflict_t
{
  PanId_t *panid;
} PanIdConflict_t;

typedef struct _LocalInterference_t
{
  uint16_t txFailureCount;
  uint8_t  *energyScanValue;
} LocalInterference_t;

typedef struct _NwkReportCommandConf_t
{
  uint8_t status;
} NwkReportCommandConf_t;

typedef struct _NwkReportCommandReq_t
{
  struct
  {
    void *next; // pointer used for queuing
  } service;
  
  NwkCommandOptions_t        options;
  union
  {
    PanIdConflict_t      panidConflict;
    LocalInterference_t  localInterference;
  };
  NwkReportCommandConf_t     confirm;
  void (*nwkReportCommandConf)(NwkReportCommandConf_t *confirmParams);
} NwkReportCommandReq_t;


typedef struct _NwkReportCommand_t
{
  QueueDescriptor_t     queue;
  struct {
  NwkCommandState_t     state:8; 
  };
  uint8_t               indState; 
  NwkReportCommandReq_t *req;
  NwkCommandReq_t       commandReq;
  union
  {
    MAC_StartReq_t        macStartReq;
    HAL_AppTimer_t        waitTimer;
  }; 
  NwkUpdateCommandReq_t updateCommandReq;
} NwkReportCommand_t;

/******************************************************************************
  task handler
******************************************************************************/
void nwkReportCommandTaskHandler(void);
void nwkResetReportCommand(void);
void nwkSendReportCommand(NwkReportCommandReq_t *req);
void nwkReportFrameInd(uint8_t *payload, NwkFrameHeader_t *header, NwkParseHeader_t *parse);

#endif /*NWKREPORTCOMMAND_H_*/
