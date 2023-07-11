/*************************************************************************//** 
\file taskManager.h 

\brief The header file describes the public stack Task Manager interface

The file describes public interface, task handlers and tasks IDs of Task Manager.

\internal
  Copyright (c)Meshnetics.
        
  History:
    15/05/07 E. Ivanov - Created
*****************************************************************************/

#ifndef _TASKMANAGER_H
#define _TASKMANAGER_H
#include <inttypes.h>
#include <types.h>
#include <atomic.h>

// \cond internal
//! The list of task ID
typedef enum
{
  MAC_PHY_HWD_TASK_ID = 1 << 0,
  HAL_TASK_ID         = 1 << 1,
  MAC_HWI_TASK_ID     = 1 << 2,
  NWK_TASK_ID         = 1 << 3,
  ZDO_TASK_ID         = 1 << 4,
  APS_TASK_ID         = 1 << 5,
  SSP_TASK_ID         = 1 << 6,
  TC_TASK_ID          = 1 << 7,
  BSP_TASK_ID         = 1 << 8,
  APL_TASK_ID         = 1 << 9
} SYS_TaskId_t;
// \endcond

/*! This function is called for processing user application task.
 Should be defined in user application.
 Its very first call is intended just for setting parameters into the stack.
 For starting a network a new task should be posted. */ 
extern void APL_TaskHandler(void);
// \cond internal
//! This function is called for processing HAL task. Should be defined in HAL
extern void HAL_TaskHandler(void);
//! This function is called for processing BSP task. Should be defined in BSP
extern void BSP_TaskHandler(void);
//! This function is called for processing MAC_PHY_HWD task. Should be defined in MAC_PHY_HWD
extern void MAC_PHY_HWD_TaskHandler(void);
//! This function is called for processing MAC_HWI task. Should be defined in MAC_HWI
extern void MAC_HWI_TaskHandler(void);
//! This function is called for processing NWK task. Should be defined in NWK
extern void NWK_TaskHandler(void);
//! This function is called for processing ZDO task. Should be defined in ZDO
extern void ZDO_TaskHandler(void);
//! This function is called for processing APS task. Should be defined in APS
extern void APS_TaskHandler(void);
//! This function is called for processing SSP task. Should be defined in SSP
extern void SSP_TaskHandler(void);
//! This function is called for processing Trust Center task. Should be defined in Trust Center
extern void TC_TaskHandler(void);

extern volatile uint16_t SYS_taskFlag;
// \endcond

/**************************************************************************************//**
\brief Posts task to the stack Task Manager

\param[in] taskId - ID of the posted task. An application has APL_TASK_ID.
*********************************************************************************************/
/*
IDs of the tasks are listed in the SYS_TaskId enum. Each task has its own priority and is called
only if there is no any task with higher priority. A handler is called when respective task can be run.
Each task has its own task handler. Correspondence between tasks and handlers is listed below:  \n
HAL - HAL_TaskHandler()                 \n
BSP - BSP_TaskHandler()                 \n
MAC_PHY_HWD - MAC_PHY_HWD_TaskHandler() \n
MAC_HWI - MAC_HWI_TaskHandler()         \n
NWK - NWK_TaskHandler()                 \n
ZDO - ZDO_TaskHandler()                 \n
APS - APS_TaskHandler()                 \n
APL - APL_TaskHandler()                 \n
*/
INLINE void SYS_PostTask(SYS_TaskId_t taskId)
{
  ATOMIC_SECTION_ENTER
   SYS_taskFlag |= taskId;
  ATOMIC_SECTION_LEAVE
}

//\cond internal
/**************************************************************************************//**
\brief  This function is called by an OS or from main() for processing the stack tasks. 
***************************************************************************************/
bool SYS_RunTask();

/**************************************************************************************//*
 \brief To force runTask to help making sync calls
******************************************************************************************/
void SYS_ForceRunTask();
// \endcond

#endif
