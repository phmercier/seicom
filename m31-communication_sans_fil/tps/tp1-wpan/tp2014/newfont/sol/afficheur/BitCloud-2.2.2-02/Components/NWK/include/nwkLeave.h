/******************************************************************************
  nwkLeave.h
  Copyright (c)Meshnetics.  
  Description: 
  History:
    27/06/07 V. Panov - Created.
******************************************************************************/
#ifndef _NWKLEAVE_H
#define _NWKLEAVE_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <types.h>
#include <nwk.h>
#include <queue.h>
#include <nwkFrame.h>
#include <nwkDataInd.h>
#include <neibTable.h>

/******************************************************************************
                   Implementations section
******************************************************************************/
typedef enum _NwkLeaveState_t
{
  LEAVE_IDLE_STATE,
  LEAVE_REMOVE_CHILDREN_STATE,
  LEAVE_REMOVE_CHILD_STATE,
  LEAVE_REMOVE_CHILD_WAIT_STATE,
  LEAVE_REMOVE_SELF_STATE,
  LEAVE_REMOVE_SELF_WAIT_STATE,
  LEAVE_RESET_MAC_STATE,
  LEAVE_CONFIRM_STATE,
  LEAVE_REQUEST_STATE,
} NwkLeaveState_t;

typedef struct _NwkLeave_t
{
  QueueDescriptor_t queue;
  struct {
  NwkLeaveState_t   state:8;
  };
  NWK_LeaveReq_t    *req;
  NwkCommandReq_t   cmdReq;
  Neib_t            *childToRemove;
  bool              removeChildren;
  bool              rejoin;
  uint64_t          deviceAddress;
  ShortAddr_t       unknownDeviceShortAddr;
  union {
    MAC_ResetReq_t  macReq;
    MAC_SetReq_t    setReq;
  };
} NwkLeave_t;

enum
{
  NWK_LEAVE_REJOIN          = 0x20,
  NWK_LEAVE_REQUEST         = 0x40,
  NWK_LEAVE_REMOVE_CHILDREN = 0x80,
};

/******************************************************************************
                   Prototypes section
******************************************************************************/

/******************************************************************************
  standard request
******************************************************************************/
void NWK_LeaveReq(NWK_LeaveReq_t *req);

/******************************************************************************
  task handler
******************************************************************************/
void nwkLeaveTaskHandler(void);
void nwkResetLeave(void);
bool nwkLeaveNonNeib(ShortAddr_t sh, ExtAddr_t ext);

/******************************************************************************
  action when command received
payload - cmd payload
header  - nwk header
parse   - parsed header fields
******************************************************************************/
void nwkLeaveFrameInd(uint8_t *payload, NwkFrameHeader_t *header, NwkParseHeader_t *parse);

#endif //_NWKLEAVE_HH
//eof nwkLeave.h
