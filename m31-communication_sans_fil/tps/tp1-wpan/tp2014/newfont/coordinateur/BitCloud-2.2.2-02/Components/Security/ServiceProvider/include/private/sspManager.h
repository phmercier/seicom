/**************************************************************************//**
  \file
    sspManager.h
  \brief
    Security Service Provider header file.
  \internal
    Copyright (c)Meshnetics.
    History:
      06/12/2007 - ALuzhetsky API corrected.
******************************************************************************/
#ifndef _SSPMANAGER_H
#define _SSPMANAGER_H

/******************************************************************************
                             Includes section.
******************************************************************************/
#include <queue.h>

/******************************************************************************
                             Definition section.
******************************************************************************/
#ifdef _SSP_USE_FLASH_FOR_CONST_DATA
  #include <avr/pgmspace.h>
  #define HANDLERS_MEM  PROGMEM
  #define HANDLERS_GET(A, I) memcpy_P(A, &sspHandlers[I], sizeof(SspTask_t))
#else // _SSP_USE_FLASH_FOR_CONST_DATA
  #define HANDLERS_MEM
  #define HANDLERS_GET(A, I) (((A)->task) = sspHandlers[I].task)
#endif // _SSP_USE_FLASH_FOR_CONST_DATA
#ifdef _MAC_HW_AES_
  #ifdef _HIGH_SECURITY_
    #define SSP_TASKS_LIST                      \
      {sspCalculateAuthenticMacTag1ReqHandler}, \
      {sspCalculateAuthenticMacTag2ReqHandler}, \
      {sspCalculateSkkeParamsReqHandler},       \
      {sspEncryptFrameReqHandler},              \
      {sspDecryptFrameReqHandler}
  #else // _HIGH_SECURITY_
    #define SSP_TASKS_LIST                      \
      {sspEncryptFrameReqHandler},              \
      {sspDecryptFrameReqHandler}
  #endif // _HIGH_SECURITY_
#else // _MAC_HW_AES_
  #ifdef _HIGH_SECURITY_
    #define SSP_TASKS_LIST                      \
      {sspCalculateAuthenticMacTag1ReqHandler}, \
      {sspCalculateAuthenticMacTag2ReqHandler}, \
      {sspCalculateSkkeParamsReqHandler},       \
      {sspEncryptFrameReqHandler},              \
      {sspDecryptFrameReqHandler},              \
      {sspAesReqHandler}
  #else // _HIGH_SECURITY_
    #define SSP_TASKS_LIST                      \
      {sspEncryptFrameReqHandler},              \
      {sspDecryptFrameReqHandler},              \
      {sspAesReqHandler}
  #endif // _HIGH_SECURITY_
#endif // _MAC_HW_AES_

/******************************************************************************
                             Types section.
******************************************************************************/
/**************************************************************************//**
  \brief TBD.

  TBD
******************************************************************************/
typedef struct PACK
{
  void (*task)(void);
} SspTask_t;

/**************************************************************************//**
  \brief TBD.

  TBD
******************************************************************************/
typedef enum 
{
#ifdef _HIGH_SECURITY_
  SSP_TASK_AUTHENTIC_MAC_TAG1,
  SSP_TASK_AUTHENTIC_MAC_TAG2,
  SSP_TASK_SKKE,
#endif // _HIGH_SECURITY_
  SSP_TASK_ENCRYPT_FRAME,
  SSP_TASK_DECRYPT_FRAME,
#ifndef _MAC_HW_AES_
  SSP_TASK_AES,
#endif // _MAC_HW_AES_

  SSP_TASKS_SIZE,
} SspTaskId_t;

/**************************************************************************//**
  \brief TBD.

  TBD
******************************************************************************/
typedef enum  // ssp possible requests' types.
{
#ifdef _HIGH_SECURITY_
  SSP_REQ_ID_AUTHENTIC_MAC_TAG1 = SSP_TASK_AUTHENTIC_MAC_TAG1,
  SSP_REQ_ID_AUTHENTIC_MAC_TAG2 = SSP_TASK_AUTHENTIC_MAC_TAG2,
  SSP_REQ_ID_SKKE               = SSP_TASK_SKKE,
#endif // _HIGH_SECURITY_
  SSP_REQ_ID_SFP_ENCRYPT_FRAME  = SSP_TASK_ENCRYPT_FRAME,
  SSP_REQ_ID_SFP_DECRYPT_FRAME  = SSP_TASK_DECRYPT_FRAME
} SspRequestId_t;

/**************************************************************************//**
  \brief TBD.

  TBD
******************************************************************************/
typedef uint8_t SspTaskBitMask_t;

/**************************************************************************//**
  \brief TBD.

  TBD
******************************************************************************/
typedef struct PACK
{
  SspTaskBitMask_t  taskBitMask;
  QueueDescriptor_t reqQueueDescr;
} SspManagerMem_t;

/******************************************************************************
                        Functions prototypes section.
******************************************************************************/
/**************************************************************************//**
  \brief TBD.
  
  \param TBD.
  \return TBD.
******************************************************************************/
void sspPostTask(SspTaskId_t taskID);

/**************************************************************************//**
  \brief TBD.
  
  \param TBD.
  \return TBD.
******************************************************************************/
void sspResetTaskManager(void);

/******************************************************************************
 Sends confirmation to the SSP user.
 Parameters:
   request - parameters of the request to be confirmed.
 Returns:
   none.
******************************************************************************/
void sspSendConfToUpperLayer(void *request);

#endif // _SSPMANAGER_H

// eof sspManager.h
