/******************************************************************************
  nwkJoinInd.h
  Copyright (c)Meshnetics.
  Description: 
    Join indivation header file.
  History:
    14/06/07 S. Vladykin - Created.
******************************************************************************/
#ifndef _NWKJOININD_H
#define _NWKJOININD_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <types.h>
#include <nwk.h>
#include <neibTable.h>
#include <nwkJoinReq.h>
#include <nwkDataInd.h>

/******************************************************************************
                   Types section
******************************************************************************/
typedef enum _NwkRespState_t
{

  JOIN_IND_OBJ_FREE_STATE,

  JOIN_IND_OBJ_ASSOC_STATES_START,

  JOIN_IND_OBJ_ASSOC_SEND_RESP_STATE,
  JOIN_IND_OBJ_ASSOC_WAIT_STATUS_STATE,
  JOIN_IND_OBJ_ASSOC_INDICATE_STATE,

  JOIN_IND_OBJ_ASSOC_STATES_END,

  JOIN_IND_OBJ_REJOIN_STATES_START,

  JOIN_IND_OBJ_REJOIN_SEND_RESP_STATE,
  JOIN_IND_OBJ_REJOIN_WAIT_STATUS_STATE,
  JOIN_IND_OBJ_REJOIN_INDICATE_STATE, 

  JOIN_IND_OBJ_REJOIN_STATES_END,

} NwkRespState_t;

typedef struct _NwkRejoinResp_t
{
  //NwkRespState_t         state;
  ShortAddr_t            newNetworkAddr;    
  ShortAddr_t            oldNetworkAddr;
  ExtAddr_t              extendedAddr;
  MAC_CapabilityInf_t    capability;
  uint8_t                rejoinStatus;
  bool                   secureJoin;
  NwkCommandReq_t        rejoinCmd;
} NwkRejoinResp_t;

typedef struct _NwkAssociateRespObj_t
{
  union
  {
    MAC_AssociateResp_t     macResp;
    NwkRejoinResp_t         rejoinResp;
  };
  struct {
  NwkRespState_t            state:8;
  };
  Neib_t                    *neib;
} NwkAssociateRespObj_t;

BEGIN_PACK
typedef struct PACK
{
  uint8_t      commandId;
  ShortAddr_t  networkAddr;
  uint8_t      rejoinStatus;
} NwkRejoinRespCmd_t;
END_PACK

typedef struct _NwkJoinInd_t
{
  NWK_JoinInd_t            joinIndication;
  MAC_SetReq_t             setReq;
  bool                     addChildStatus;
  union
  {
    NwkAssociateRespObj_t  *responseBuffer;
    DEFINE_DBG_ARRAY(NwkAssociateRespObj_t);
  };
  uint8_t                  maxResponses;
  MAC_DataReq_t            dataReq;
  bool                     commandReqBusy;
  NwkCommandReq_t          *cmd;
  NwkCommandReq_t          rejoinCmd;
} NwkJoinInd_t;

/******************************************************************************
                   Prototypes section
******************************************************************************/

/******************************************************************************
  task handler
******************************************************************************/
void nwkJoinIndTaskHandler(void);

/******************************************************************************
  reset routine
******************************************************************************/
void nwkResetJoinInd(void);

/******************************************************************************
  action when command received
payload - cmd payload
header  - nwk header
parse   - parsed header fields
******************************************************************************/
void nwkRejoinRequestFrameInd(uint8_t *payload, NwkFrameHeader_t *header, NwkParseHeader_t *parse);

/******************************************************************************
  action when command received
payload - cmd payload
header  - nwk header
parse   - parsed header fields
******************************************************************************/
void nwkRejoinResponseFrameInd(uint8_t *payload, NwkFrameHeader_t *header, NwkParseHeader_t *parse);

void nwkPrepareRejoinMacData(uint8_t *data);
void nwkPrepareRejoinMacReq(MAC_DataReq_t *req);
void nwkRejoinResponseConfirm(uint8_t status);
void nwkRejoinResponseConfirmConflict(uint8_t status);

#endif // _NWKJOININD_H

// eof
