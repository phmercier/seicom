/************************************************************************
  ZdoTaskManager.h
  Copyright (c)Meshnetics.

  History:
    07/06/07 I. Kalganova - Modified
**************************************************************************/

#ifndef ZDOTASKMANAGER_H_
#define ZDOTASKMANAGER_H_

#include <inttypes.h>
#include <types.h>

#define ZDO_NUMBER_TASKHANDLERS     8

typedef uint16_t ZDO_TaskMask_t;

typedef enum
{
  ZDO_STATEMACHINE_TASK_ID        = 0,
  ZDO_SECURITYMANAGER_TASK_ID     = 1,
  ZDO_ZDP_FRAME_PROCESSOR_TASK_ID = 2,
  ZDO_ZDP_MANAGER_TASK_ID         = 3,
  ZDO_NETWORKMANAGER_TASK_ID      = 4,
  ZDO_DISCOVERYMANAGER_TASK_ID    = 5,
  ZDO_NODEMANAGER_TASK_ID         = 6,
  ZDO_BINDMANAGER_TASK_ID         = 7,
} ZDO_TaskID_t;

typedef struct
{
  void (*f)();
}ZdoTaskHandler_t;

extern void zdoStateMachineHandler(void);
extern void zdoSecurityManagerHandler(void);
extern void zdoZdpManagerHandler(void);
extern void zdoZdpFrameProcessorHandler(void);
extern void zdoPostTask(ZDO_TaskID_t);

#endif /*ZDOTASKMANAGER_H_*/
