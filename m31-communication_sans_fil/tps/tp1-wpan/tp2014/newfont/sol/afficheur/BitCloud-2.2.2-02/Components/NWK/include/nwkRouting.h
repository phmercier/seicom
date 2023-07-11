/******************************************************************************
  nwkRouting.h
  Copyright (c)Meshnetics.
  Description: 
    routing header file.
  History:
    14/06/07 V. Panov - Created.
******************************************************************************/
#ifndef _NWKROUTING_H
#define _NWKROUTING_H

/******************************************************************************
                        Includes section
******************************************************************************/
#include <types.h>
#include <queue.h>

/******************************************************************************
 types section
******************************************************************************/
typedef struct _NwkFindRouteReq_t
{
  void           *serviceNext;
//  union {
    ShortAddr_t  dstAddr;
    ShortAddr_t  nextHop;
//  };
  uint8_t        dstAddrMode;
  bool           discoverRoute;
} NwkFindRouteReq_t;

typedef enum _NwkFindRouteState_t
{
  FIND_ROUTE_IDLE,
  FIND_ROUTE_REQUEST,
  FIND_ROUTE_SENDING_RECORD,
} NwkFindRouteState_t;

typedef struct _NwkFindRoute_t
{
  QueueDescriptor_t       queue;
  NWK_RouteDiscoveryReq_t routeDiscoveryReq;
  struct {
  NwkFindRouteState_t     state:8;
  };
} NwkFindRoute_t;

/******************************************************************************
                        Prototypes section
******************************************************************************/

/******************************************************************************
  reset routine
******************************************************************************/
void nwkResetFindRoute(void);

/******************************************************************************
  task handler
******************************************************************************/
void nwkFindRouteTaskHandler(void);

/******************************************************************************
  calculation of Cskip's denend on depth
depth - to calculate
results stored in NIB
******************************************************************************/
uint16_t nwkCSkip(uint8_t depth);

/******************************************************************************
  request to find route
  looking for routing tables entries
  initiate route discovery if alowed in parameters
  calculate next hop by tree if it is allowed in NIB
  return next hop in confirm if it is known or NWK_NO_SHORT_ADDR otherwise
******************************************************************************/
void nwkFindRouteReq(NwkFindRouteReq_t *findRouteReq);

/******************************************************************************
  confirm to nwkFindRouteReq
******************************************************************************/
void nwkFindRouteConf(NwkFindRouteReq_t *findRouteReq);

/******************************************************************************
  allocate short address
router - parametes is used if tree addressing is active
addrRequested - if rejoin is used, it is addr device selects for itself
                NWK_NO_SHORT_ADDR otherwise
return: allocated address
        addrRequested - is possible, or addres allocated otherwise
******************************************************************************/
ShortAddr_t nwkAllocateShortAddr(bool router, ShortAddr_t addrRequested);

#endif //_NWKROUTING_H
//eof nwkRouting.h
