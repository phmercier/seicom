/**************************************************************************//**
  \file
    tcTaskManager.h
  \brief
    Security Trust Centre task manager header file.
  \internal
    Copyright (c)Meshnetics.
    History:
      2007.12.25 - ALuzhetsky created.
******************************************************************************/
#ifndef _TCTASKMANAGER_H
#define _TCTASKMANAGER_H

/******************************************************************************
                            Includes section.
******************************************************************************/
#include <types.h>

/******************************************************************************
                             Definitions section.
******************************************************************************/
#ifdef _HIGH_SECURITY_
  #define TC_TASKS_LIST         \
  {                             \
    {tcAuthenticTaskHandler},   \
    {tcKeyUpdateTaskHandler},   \
    {tcKeyEstablishTaskHandler},\
    {tcRemoveTaskHandler}       \
  }                             
#else // _HIGH_SECURITY_
  #define TC_TASKS_LIST         \
  {                             \
    {tcAuthenticTaskHandler},   \
    {tcKeyUpdateTaskHandler},   \
    {tcRemoveTaskHandler}       \
  }                             
#endif // _HIGH_SECURITY_

/******************************************************************************
                             Types section.
******************************************************************************/
/**************************************************************************//**
  \brief TBD.

  TBD
******************************************************************************/
typedef enum 
{
  //TC_TASK_RESET,
  TC_TASK_AUTHENTIC,
  TC_TASK_KEY_UPDATE,
#ifdef _HIGH_SECURITY_
  TC_TASK_KEY_ESTABLISH,
#endif // _HIGH_SECURITY_
  TC_TASK_REMOVE,

  TC_TASKS_SIZE,
} tcTaskID_t;

/**************************************************************************//**
  \brief TBD.

  TBD
******************************************************************************/
typedef uint8_t TcTaskBitMask_t;

/**************************************************************************//**
  \brief TBD.

  TBD
******************************************************************************/
typedef struct PACK
{
  TcTaskBitMask_t taskBitMask;
} TcTaskManagerMem_t;

/******************************************************************************
                        Functions prototypes section.
******************************************************************************/
/**************************************************************************//**
  \brief TBD.
  
  \param TBD.
  \return TBD.
******************************************************************************/
void tcPostTask(tcTaskID_t taskID);

/**************************************************************************//**
  \brief TBD.
  
  \param TBD.
  \return TBD.
******************************************************************************/
void tcResetTaskManager(void);

#endif // _TCTASKMANAGER_H

// eof tcTaskManager.h
