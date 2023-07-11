/******************************************************************************
  nwkSync.h
  Copyright (c)Meshnetics.
  Description:
  History:
    27/06/07 V. Panov - Created.
******************************************************************************/
#ifndef _NWKSYNC_H
#define _NWKSYNC_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <types.h>
#include <nwk.h>
#include <queue.h>

/******************************************************************************
                   Implementations section
******************************************************************************/
typedef enum _NwkSyncStates_t
{
  SYNC_IDLE_STATE,
  SYNC_SENDING_STATE,
  SYNC_CONFIRM_STATE,
} NwkSyncState_t;

typedef struct _NwkSync_t
{
  QueueDescriptor_t queue;
  uint8_t           syncFailCounter;
  struct {
  NwkSyncState_t    state:8;
  };
  MAC_PollReq_t     macReq;
  NWK_SyncReq_t     *req;
} NwkSync_t;

/******************************************************************************
                        Prototypes section
******************************************************************************/

/******************************************************************************
  standard request
******************************************************************************/
void NWK_SyncReq(NWK_SyncReq_t *req);

/******************************************************************************
  task handler
******************************************************************************/
void nwkSyncTaskHandler(void);

/******************************************************************************
  reset routine
******************************************************************************/
void nwkResetSync(void);

#endif //_NWKSYN�_H
//eof nwkSync.h
