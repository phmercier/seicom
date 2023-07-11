/******************************************************************************
  nwkJoinReq.h
  Copyright (c)Meshnetics.
  Description: 
    join Request header file.
  History:
    14/06/07 S. Vladykin - Created.
******************************************************************************/
#ifndef _NWKJOINREQ_H
#define _NWKJOINREQ_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <types.h>
#include <mac.h>
#include <nwk.h>
#include <queue.h>
#include <neibTable.h>
#include <appTimer.h>
#include <nwkFrame.h>
#include <nwkDataInd.h>

/******************************************************************************
                   Defines section
******************************************************************************/
#define  NWK_ASSOCC_ATTEMPS_NUM  	3

/******************************************************************************
                   Types section
******************************************************************************/
typedef enum _NwkJoinReqState_t
{
  JOIN_REQ_IDLE_STATE,
  JOIN_REQ_INIT_STATE,
  JOIN_REQ_ASSOCIATION_STATE,
  JOIN_REQ_ASSOCIATION_WAIT_STATE,
  JOIN_REQ_ASSOCIATION_RETRY_STATE,
  JOIN_REQ_SCAN_STATE,
  JOIN_REQ_SCAN_WAIT_STATE,
  JOIN_REQ_GET_SUITABLE_PARENT_STATE,
  JOIN_REQ_REJOIN_STATE,
  JOIN_REQ_REJOIN_CONF_WAIT_STATE,
  JOIN_REQ_REJOIN_RESPONSE_WAITING_STATE,
  JOIN_REQ_SET_SHORT_ADDRESS_STATE,
  JOIN_REQ_SET_SHORT_ADDRESS_WAIT_STATE,
  JOIN_REQ_SET_FIRST_SHORT_ADDRESS_STATE,
  JOIN_REQ_SET_FIRST_SHORT_ADDRESS_WAIT_STATE,
  JOIN_REQ_SET_SHORT_ADDRESS_ONLY_STATE,
  JOIN_REQ_SET_SHORT_ADDRESS_ONLY_WAIT_STATE,
  JOIN_REQ_SET_COORD_SHORT_ADDR_STATE,
  JOIN_REQ_SET_COORD_SHORT_ADDR_WAIT_STATE,
  JOIN_REQ_SET_COORD_EXT_ADDR_STATE,
  JOIN_REQ_SET_COORD_EXT_ADDR_WAIT_STATE,
  JOIN_REQ_SET_ASSOC_PAN_COORD_STATE,
  JOIN_REQ_SET_ASSOC_PAN_COORD_WAIT_STATE,
  JOIN_REQ_SET_PANID_STATE,
  JOIN_REQ_SET_PANID_WAIT_STATE,
  JOIN_REQ_SET_CHANNEL_STATE,
  JOIN_REQ_SET_CHANNEL_WAIT_STATE,
  JOIN_REQ_SET_BEACON_PAYLOAD_STATE,
  JOIN_REQ_SET_BEACON_PAYLOAD_WAIT_STATE,
  JOIN_REQ_SET_BEACON_PAYLOAD_LEN_STATE,
  JOIN_REQ_SET_BEACON_PAYLOAD_LEN_WAIT_STATE,
  JOIN_REQ_SET_RX_ON_WHEN_IDLE_STATE,
  JOIN_REQ_SET_RX_ON_WHEN_IDLE_WAIT_STATE,
  JOIN_REQ_RX_ENABLE_STATE,
  JOIN_REQ_RX_ENABLE_WAIT_STATE,
  JOIN_REQ_CONFIRM_STATE,
  JOIN_REQ_WAIT_DECRYPT,
} NwkJoinReqState_t;

BEGIN_PACK
typedef struct PACK
{
  uint8_t              commandId;
  MAC_CapabilityInf_t  capability;
} NwkRejoinReqCmd_t;
END_PACK

typedef struct _NwkJoinReq_t
{
  struct {
  NwkJoinReqState_t       state:8;
  };
  QueueDescriptor_t       queue;
  NWK_JoinReq_t           *req;
  Neib_t                  *currentCandidateRouter;
  uint8_t                 assoccAttempNum;
  MAC_PanDescriptor_t     *panDescriptors;
  NwkCommandReq_t         rejoinCmd;
  NWK_NetworkDescriptor_t networkList[5];
  MAC_PollReq_t           pollReq;
  union
  {
    MAC_AssociateReq_t        assocReq;
    MAC_SetReq_t              setReq;
    MAC_RxEnableReq_t         rxEnableReq;
    NWK_NetworkDiscoveryReq_t discReq;
        
  };
  HAL_AppTimer_t            responseWaitTimer;
} NwkJoinReq_t;

/******************************************************************************
                   Prototypes section
******************************************************************************/

/******************************************************************************
  reset routine
******************************************************************************/
void nwkResetJoinReq(void);

/******************************************************************************
  task handler
******************************************************************************/
void nwkJoinReqTaskHandler(void);

/******************************************************************************
  action when command received
payload - cmd payload
header  - nwk header
parse   - parsed header fields
******************************************************************************/
void nwkRejoinResponseFrameInd(uint8_t *payload, NwkFrameHeader_t *header, NwkParseHeader_t *parse);

#endif //_NWKJOINREQ_H
//eof nwkJoinReq.h
