/******************************************************************************
  zdoDbg.h
  Copyright (c)Meshnetics.

  Description:
              
******************************************************************************/

#ifndef _ZDODBG_H
#define _ZDODBG_H

#include <dbg.h>

typedef enum ZdoDbgCode_t_
{
  ZDO_ASSERT_MESSAGE = 0x5000,
  ZDO_NULL_CONFIRM_MESSAGE = 0x5001,
  ZDO_UNKNOWN_DEVICE_TYPE_MESSAGE = 0x5002,
  ZDO_UNKNOWN_EVENT_MESSAGE = 0x5003,
  ZDO_UNKNOWN_STATE_MESSAGE = 0x5004,
  ZDO_UNEXPECTED_FAIL_CONFIRM_MESSAGE = 0x5005,
  ZDO_UNKNOWN_NETWORK_START_TYPE_MESSAGE = 0x5006,
  ZDO_STACK_RESET_FAIL_MESSAGE = 0x5007,
  ZDO_UNKNOWN_ZDP_CLUSTER_MESSAGE = 0x5008,
  ZDO_ILLEGAL_ADDRESS_MODE_MESSAGE = 0x5009,
  ZDO_UNKNOWN_SECURITY_KEY_MESSAGE = 0x500A,
  ZDO_UNEXPECTED_CALLBACK = 0x500B,
} ZdoDbgCode_t;

#endif /*ZDODBG_H_*/
