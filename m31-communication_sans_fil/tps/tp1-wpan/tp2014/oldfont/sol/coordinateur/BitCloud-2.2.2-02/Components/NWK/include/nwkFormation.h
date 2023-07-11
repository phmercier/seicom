/******************************************************************************
  nwkFormation.h
  Copyright (c)Meshnetics.
  Description: 
    Formation header file.
  History:
    14/06/07 S. Vladykin - Created.
******************************************************************************/
#ifndef _NWKFORMATION_H
#define _NWKFORMATION_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <nwk.h>

/******************************************************************************
                   Types section
******************************************************************************/
typedef enum _NwkFormationState_t  // states 
{
  FORMATION_IDLE_STATE,
  FORMATION_ACTIVE_SCAN_STATE,
  FORMATION_WAIT_STATE,
  FORMATION_SET_SHORT_ADDR_STATE,
  FORMATION_SET_SHORT_ADDR_WAIT_STATE,
  FORMATION_SET_BEACON_PAYLOAD_LEN_STATE,
  FORMATION_SET_BEACON_PAYLOAD_LEN_WAIT_STATE,
  FORMATION_SET_BEACON_PAYLOAD_STATE,
  FORMATION_SET_BEACON_PAYLOAD_WAIT_STATE,
  FORMATION_SET_RX_ON_WHEN_IDLE_STATE,
  FORMATION_SET_RX_ON_WHEN_IDLE_WAIT_STATE,
  FORMATION_START_STATE,
  FORMATION_START_WAIT_STATE,
  FORMATION_RX_ENABLE_STATE,
  FORMATION_RX_ENABLE_WAIT_STATE,
  FORMATION_CONFIRM_STATE,
} NwkFormationState_t;

typedef struct _NwkFormation_t
{
  struct {
  NwkFormationState_t        state:8; // finite-state machine
  };
  NWK_NetworkFormationReq_t* req;   // request being processed    
  QueueDescriptor_t          queue; // additional fields
  union
  {
    MAC_ScanReq_t            scanReq;
    MAC_SetReq_t             setReq;
    MAC_StartReq_t           startReq;
    MAC_RxEnableReq_t        rxEnableReq;
  };
  uint32_t                   scanChannels;
  uint32_t                   restScanChannels;
  uint8_t                    currentChannel;
  PHY_EnergyLevel_t          energyList[NWK_MAX_CHANNEL];
  union {
    MAC_PanDescriptor_t      *panDescriptors;
    MAC_PanDescriptor_t      (*panDescriptorsArray)[];
    DEFINE_DBG_ARRAY(MAC_PanDescriptor_t);
  };
  uint8_t                    maxPanDescriptors;
} NwkFormation_t;

/******************************************************************************
                   Prototypes section
******************************************************************************/

/******************************************************************************
  standard request
******************************************************************************/
void NWK_NetworkFormationReq(NWK_NetworkFormationReq_t *req);

/******************************************************************************
  reset routine
******************************************************************************/
void nwkResetFormation(void);

/******************************************************************************
  task handler
******************************************************************************/
void nwkFormationTaskHandler(void);

#endif   // _NWKFORMATION_H
//eof nwkFormation
