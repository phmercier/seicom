/******************************************************************************
  nwkReset.h
  Copyright (c)Meshnetics.
  Description: 
    nwk reset header file.
  History:     
    20/06/07 V. Panov - Created.
******************************************************************************/
#ifndef _NWKRESET_H
#define _NWKRESET_H

/******************************************************************************
                        Includes section.
******************************************************************************/
#include <nwk.h>
#include <queue.h>

/******************************************************************************
                        Types section.
******************************************************************************/
typedef enum _NwkResetState_t
{
  RESET_IDLE_STATE,
  RESET_SET_SHORT_ADDRESS_STATE,
  RESET_SET_SHORT_ADDRESS_WAIT_STATE,
  RESET_SET_COORD_SHORT_ADDR_STATE,
  RESET_SET_COORD_SHORT_ADDR_WAIT_STATE,
  RESET_SET_COORD_EXT_ADDR_STATE,
  RESET_SET_COORD_EXT_ADDR_WAIT_STATE,
  RESET_SET_ASSOC_PAN_COORD_STATE,
  RESET_SET_ASSOC_PAN_COORD_WAIT_STATE,
  RESET_SET_PANID_STATE,
  RESET_SET_PANID_WAIT_STATE,
  RESET_SET_BEACON_PAYLOAD_STATE,
  RESET_SET_BEACON_PAYLOAD_WAIT_STATE,
  RESET_SET_BEACON_PAYLOAD_LEN_STATE,
  RESET_SET_BEACON_PAYLOAD_LEN_WAIT_STATE,
  RESET_SET_RX_ON_WHEN_IDLE_STATE,
  RESET_SET_RX_ON_WHEN_IDLE_WAIT_STATE,
  RESET_SET_CHANNEL_STATE,
  RESET_SET_CHANNEL_WAIT_STATE,
  RESET_START_STATE,
  RESET_START_WAIT_STATE,
  RESET_RX_ENABLE_STATE,
  RESET_RX_ENABLE_WAIT_STATE,
  RESET_CONFIRM_STATE,
} NwkResetState_t;

typedef struct _NwkReset_t
{
  union {
  MAC_ResetReq_t    macReq;
  MAC_SetReq_t      setReq;
  MAC_RxEnableReq_t rxEnableReq;
  MAC_StartReq_t    startReq;
  };

  NWK_ResetReq_t *req;
  NwkResetState_t state;
} NwkReset_t;

/******************************************************************************
                        Prototypes section
******************************************************************************/

/******************************************************************************
  standard request
******************************************************************************/
void NWK_ResetReq(NWK_ResetReq_t *req);

/******************************************************************************
  task handler
******************************************************************************/
void nwkResetTaskHandler(void);

#endif //_NWKRESET_H
//eof nwkReset.c
