/******************************************************************************
  nwkRouteDiscovery.h
  Copyright (c)Meshnetics.
  Description: 
  History:
    05/09/07 V. Panov - Created.
******************************************************************************/
#ifndef _NWKROUTEDISCOVERY_H
#define _NWKROUTEDISCOVERY_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <types.h>
#include <nwk.h>
#include <queue.h>
#include <nwkDataInd.h>
#include <nwkRouteTable.h>

/******************************************************************************
                        Types section.
******************************************************************************/
typedef enum _NwkRouteDiscoveryStates_t
{
  ROUTE_DISCOVERY_IDLE_STATE,
  ROUTE_DISCOVERY_REQUEST_STATE,
  ROUTE_DISCOVERY_CONFIRM_STATE,
} NwkRouteDiscoveryState_t;

typedef struct _NwkRouteDiscovery_t
{
  QueueDescriptor_t        queue;
  struct {
  NwkRouteDiscoveryState_t state:8;
  };
  NWK_RouteDiscoveryReq_t  *req;
  NwkCommandReq_t          commandReq;

  NwkRouteItem_t           *routeItem;
  NwkRouteDiscoveryItem_t  *routeDiscoveryItem;
  bool                     processTableNeeded;
  bool                     processTableInProgress;
  uint8_t                  frameLength;
  HAL_AppTimer_t           confirmTimer;
} NwkRouteDiscovery_t;

/******************************************************************************
                        Prototypes section
******************************************************************************/

/******************************************************************************
  standard request
******************************************************************************/
void NWK_RouteDiscoveryReq (NWK_RouteDiscoveryReq_t *req);

/******************************************************************************
  task handler
******************************************************************************/
void nwkRouteDiscoveryTaskHandler(void);

/******************************************************************************
  reset routine
******************************************************************************/
void nwkResetRouteDiscovery(void);

#endif //_NWKROUTEDISCOVERY_H
//eof nwkRouteDiscovery.h
