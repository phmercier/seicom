/******************************************************************************
  nwkStartRouter.h
  Copyright (c)Meshnetics.
  Description: 
  History:
    27/06/07 V. Panov - Created.
******************************************************************************/
#ifndef _NWKSTARTROUTER_H
#define _NWKSTARTROUTER_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <types.h>
#include <nwk.h>
#include <queue.h>

/******************************************************************************
                        Includes section
******************************************************************************/
typedef enum _NwkStartRouterStates_t
{
  START_ROUTER_IDLE_STATE,
  START_ROUTER_WAIT_STATE,
  START_ROUTER_CONFIRM_STATE,
} NwkStartRouterState_t;

typedef struct _NwkStartRouter_t
{
  QueueDescriptor_t     queue;
  struct {
  NwkStartRouterState_t state:8;
  };
  MAC_StartReq_t        macReq;
  NWK_StartRouterReq_t  *req;
} NwkStartRouter_t;

/******************************************************************************
                        Prototypes section
******************************************************************************/

/******************************************************************************
  standard request
******************************************************************************/
void NWK_StartRouterReq(NWK_StartRouterReq_t *req);

/******************************************************************************
  task handler
******************************************************************************/
void nwkStartRouterTaskHandler(void);

/******************************************************************************
  reset routine
******************************************************************************/
void nwkResetStartRouter(void);

#endif //_NWKSTARTROUTER_H
//eof nwkStartRouter.h
