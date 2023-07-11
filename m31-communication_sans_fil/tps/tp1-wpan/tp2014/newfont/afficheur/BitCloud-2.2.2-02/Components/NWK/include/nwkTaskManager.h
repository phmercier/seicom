/******************************************************************************
  taskManager.h
  Copyright (c)Meshnetics.
  Description: 
    task manager header file.
  History:
    14/06/07 V. Panov - Created.
******************************************************************************/
#ifndef _NWKTASKMANAGER_H
#define _NWKTASKMANAGER_H

/******************************************************************************
                        Includes section
******************************************************************************/
#include <types.h>

/******************************************************************************
                        Definitions section
******************************************************************************/
#define NWK_TASKS_LIST                    \
{                                         \
  {nwkResetTaskHandler},                  \
  {nwkSyncTaskHandler},                   \
  {nwkStatusCommandTaskHandler},          \
  {nwkFindRouteTaskHandler},              \
\
  {nwkDataReqTaskHandler},                \
  {nwkDataIndTaskHandler},                \
  {nwkRouteDiscoveryTaskHandler},         \
  {nwkStartRouterTaskHandler},            \
\
  {nwkPermitJoiningTaskHandler},          \
  {nwkDiscoveryTaskHandler},              \
  {nwkFormationTaskHandler},              \
  {nwkJoinReqTaskHandler},                \
\
  {nwkJoinIndTaskHandler},                \
  {nwkLeaveTaskHandler},                  \
  {nwkReportCommandTaskHandler},          \
  {nwkUpdateCommandTaskHandler},          \
\
  {nwkEDScanTaskHandler},                 \
}                                         \

/******************************************************************************
                        Types section
******************************************************************************/
typedef enum 
{
  NWK_TASK_RESET,
  NWK_TASK_SYNC,
  NWK_TASK_STATUS_COMMAND,
  NWK_TASK_FIND_ROUTE,

  NWK_TASK_DATA_REQ,
  NWK_TASK_DATA_IND,
  NWK_TASK_ROUTE_DISCOVERY,
  NWK_TASK_START_ROUTER,

  NWK_TASK_PERMIT_JOINING,
  NWK_TASK_DISCOVERY_REQ,
  NWK_TASK_FORMATION_REQ,
  NWK_TASK_JOIN_REQ,

  NWK_TASK_JOIN_IND,
  NWK_TASK_LEAVE,
  NWK_TASK_REPORT_COMMAND,
  NWK_TASK_UPDATE_COMMAND,

  NWK_TASK_EDSCAN,

  NWK_TASKS_SIZE,
} nwkTaskID_t;

typedef uint32_t nwkTaskBitMask_t;

typedef struct _NwkTaskManager_t
{
  nwkTaskBitMask_t taskBitMask;
} NwkTaskManager_t;

/******************************************************************************
                        Prototypes section
******************************************************************************/

/******************************************************************************
  post task
taskID - task id
******************************************************************************/
void nwkPostTask(nwkTaskID_t taskID);

/******************************************************************************
  global task handler
******************************************************************************/
void NWK_TaskHandler(void);

/******************************************************************************
  reset routine
******************************************************************************/
void nwkResetTaskManager(void);

#endif //_NWKTASKMANAGER_H
//eof taskManager.h
