/******************************************************************************
  nwkPermitJoining.h
  Copyright (c)Meshnetics
  Description: 
  History:
    27/06/07 V. Panov - Created.
******************************************************************************/
#ifndef _NWKPERMITJOINING_H
#define _NWKPERMITJOINING_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <types.h>
#include <nwk.h>
#include <queue.h>

/******************************************************************************
                   Types section
******************************************************************************/
typedef enum _NwkPermitJoiningStates_t
{
  PERMIT_JOINING_IDLE_STATE,
  PERMIT_JOINING_WAIT_STATE,
  PERMIT_JOINING_CONFIRM_STATE,
} NwkPermitJoiningState_t;

typedef struct _NwkPermitJoining_t
{
  QueueDescriptor_t       queue;
  struct {
  NwkPermitJoiningState_t state:8;
  };
  MAC_SetReq_t            macReq;
  NWK_PermitJoiningReq_t  *req;
} NwkPermitJoining_t;

/******************************************************************************
                   Inline functions section
******************************************************************************/

/******************************************************************************
  standard request
******************************************************************************/
void NWK_PermitJoiningReq(NWK_PermitJoiningReq_t *req);

/******************************************************************************
  task handler
******************************************************************************/
void nwkPermitJoiningTaskHandler(void);

/******************************************************************************
  reset routine
******************************************************************************/
void nwkResetPermitJoining(void);

#endif //_NWKPERMITJOINING_H
//eof nwkPermitJoining.h
