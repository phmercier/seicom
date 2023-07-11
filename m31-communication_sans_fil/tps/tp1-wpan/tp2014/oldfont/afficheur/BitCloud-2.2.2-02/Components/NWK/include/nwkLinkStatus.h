/******************************************************************************
  nwkLinkStatus.h
  Copyright (c)Meshnetics.
  Description: 
  History:
    01/08/07 V. Panov - Created.
******************************************************************************/
#ifndef _NWKLINKSTATUS_H
#define _NWKLINKSTATUS_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <nwkDataInd.h>
#include <appTimer.h>

/******************************************************************************
                   Types section
******************************************************************************/
typedef enum _NwkLinkStatusState_t
{
  LINK_STATUS_IDLE_STATE,
  LINK_STATUS_WAIT_STATE,
} NwkLinkStatusState_t;

typedef struct _NwkLinkStatus_t
{
  NwkCommandReq_t      req;
  HAL_AppTimer_t       delayTimer;
  struct {
  NwkLinkStatusState_t state:8;
  };
} NwkLinkStatus_t;

BEGIN_PACK
typedef struct PACK _NwkLinkStatusOptions_t
{
  uint8_t entryCount : 5;
  uint8_t firstFrame : 1;
  uint8_t lastFrame  : 1;
  uint8_t reserved   : 1;
} NwkLinkStatusOptions_t;

typedef struct PACK _NwkLinkStatusEntry_t
{
  uint8_t incomingCost : 3;
  uint8_t reserved1    : 1;
  uint8_t outgoingCost : 3;
  uint8_t reserved2    : 1;
} NwkLinkStatusEntry_t;

typedef struct PACK _NwkLinkStatusItem_t
{
  ShortAddr_t           addr;
  NwkLinkStatusEntry_t  linkStatus;
} NwkLinkStatusItem_t;

typedef struct PACK _NwkLinkPayload_t
{
  NwkLinkStatusOptions_t options;
  NwkLinkStatusItem_t    table[1];
} NwkLinkStatusPayload_t;
END_PACK

/******************************************************************************
                   Prototypes section
******************************************************************************/

/******************************************************************************
  reset routine
******************************************************************************/
void nwkResetLinkStatus(void);

/******************************************************************************
  action when command received
payload - cmd payload
header  - nwk header
parse   - parsed header fields
******************************************************************************/
void nwkLinkStatusInd(uint8_t *payload, NwkFrameHeader_t *header, NwkParseHeader_t *parse);

#endif
//eof nwkLinkStatus.h
