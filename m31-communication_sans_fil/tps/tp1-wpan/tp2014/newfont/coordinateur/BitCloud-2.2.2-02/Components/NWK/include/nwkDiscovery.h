/******************************************************************************
  nwkDiscovery.h
  Copyright (c)Meshnetics.
  Description: 
    Discovery header file.
  History:
    14/06/07 S. Vladykin - Created.
******************************************************************************/
#ifndef _NWKDISCOVERY_H
#define _NWKDISCOVERY_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <nwk.h>
#include <types.h>
#include <queue.h>
#include <nwkSystem.h>
#include <nwkReportCommand.h>

/******************************************************************************
                   Types section
******************************************************************************/
typedef enum _NwkDiscoveryState_t
{
  DISCOVERY_IDLE_STATE,
  DISCOVERY_SCANNING_STATE,
  DISCOVERY_WAITING_BEACON_NOTIFY_STATE,
  DISCOVERY_CONFIRMING_STATE,
} NwkDiscoveryState_t;

typedef struct _NwkDiscovery_t
{
  struct {
  NwkDiscoveryState_t         state:8;               // finite-state machine
  };
  union
  {
    NWK_NetworkDescriptor_t   *networksList;       // network list
    DEFINE_DBG_ARRAY(NWK_NetworkDescriptor_t);
  };
  uint8_t                     currentNetworksNum;  // request being processed
  NWK_NetworkDiscoveryReq_t   *req;
  QueueDescriptor_t           queue;// additional fields
  MAC_ScanReq_t               scanReq;
  union
  {
    MAC_PanDescriptor_t       *panDescriptors;
    MAC_PanDescriptor_t       (*panDescriptorsArray)[];
    DEFINE_DBG_ARRAY(MAC_PanDescriptor_t);
  };
  uint8_t                     maxPanDescriptors;
  union
  {
    NwkReportCommandReq_t     reportCommandReq;
    MAC_RxEnableReq_t         rxEnableReq;
    MAC_SetReq_t              setReq;
    MAC_GetReq_t              getReq;
  };
} NwkDiscovery_t;

/******************************************************************************
                   Prototypes section
******************************************************************************/

/******************************************************************************
  task handler
******************************************************************************/
void nwkDiscoveryTaskHandler(void);

/******************************************************************************
  reset routine
******************************************************************************/
void nwkResetDiscovery(void);

#endif   //_NWKDISCOVERY_H
//eof nwkDiscovery.h
