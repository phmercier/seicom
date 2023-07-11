/**************************************************************************//**
  \file
    sspCommon.h
  \brief
    Declarations of common Security Service Provider's fields and types.
  \internal
    Copyright (c)Meshnetics.
    History:     
      06/12/07 ALuzhetsky - Created.
******************************************************************************/

#ifndef _SSPCOMMON_H
#define _SSPCOMMON_H

/******************************************************************************
                        Includes section.
******************************************************************************/
#include "types.h"

/******************************************************************************
                        Definitions section.
******************************************************************************/
#define SECURITY_KEY_SIZE   16
#define SECURITY_BLOCK_SIZE 16

/******************************************************************************
                        Types section.
******************************************************************************/
/**************************************************************************//**
  \brief Possible status values of different SSP primitives.
******************************************************************************/
typedef enum
{
  SSP_SUCCESS_STATUS,
  SSP_NOT_PERMITED_STATUS,
  SSP_MAX_FRM_COUNTER_STATUS,
  SSP_BAD_CCM_OUTPUT_STATUS,
} PACK SSP_Status_t;

/**************************************************************************//**
  \brief Internal service fields which give an opportunity to compose requests' queue.
******************************************************************************/
typedef struct                         
{
  void    *next;
  uint8_t requestId;
} PACK SSP_Service_t;

#endif //_SSPCOMMON_H

// eof sspCommon.h
