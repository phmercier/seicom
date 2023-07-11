/******************************************************************************
  nwkCmdRouteRequest.h
  Copyright (c)Meshnetics.
  Description: 
    route request command types and functions.
  History:
    17/09/07 V. Panov - Created.
******************************************************************************/
#ifndef _NWKCMDROUTEREPLY_H
#define _NWKCMDROUTEREPLY_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <nwk.h>
#include <nwkFrame.h>

/******************************************************************************
                   Types section
******************************************************************************/
BEGIN_PACK
typedef struct PACK _NwkRouteReplyOptions_t
{
  uint8_t reserved1     : 4;
  uint8_t originatorExt : 1;
  uint8_t responderExt  : 1;
  uint8_t multicast     : 1;
  uint8_t reserved2     : 1;
} NwkRouteReplyOptions_t;

typedef struct PACK _NwkRouteReplyFrame_t
{
  union PACK
  {
    NwkRouteReplyOptions_t  cmdOptions;
    uint8_t                 cmdOptionsByte;
  };
  uint8_t                   identifier;
  ShortAddr_t               originatorAddr;
  ShortAddr_t               responderAddr;
  uint8_t                   pathCost;
  ExtAddr_t                 originatorExt;
  ExtAddr_t                 responderExt;
} NwkRouteReplyFrame_t;
END_PACK

/******************************************************************************
  prototypes
******************************************************************************/

/******************************************************************************
  action when command received
payload - cmd payload
header  - nwk header
parse   - parsed header fields
******************************************************************************/
void nwkRouteReplyFrameInd(uint8_t *payload, NwkFrameHeader_t *header, NwkParseHeader_t *parse);

/******************************************************************************
callback, fill nwk payload of route reply cmd
******************************************************************************/
void cmdRouteReplyPrepareMacData(uint8_t *data);

/******************************************************************************
callback, fill mac request for route reply cmd
******************************************************************************/
void cmdRouteReplyPrepareMacReq(MAC_DataReq_t *req);

/******************************************************************************
callback, route reply sent, ready to send another command
******************************************************************************/
void cmdRouteReplyConfirm(uint8_t status);

#endif
//eof
