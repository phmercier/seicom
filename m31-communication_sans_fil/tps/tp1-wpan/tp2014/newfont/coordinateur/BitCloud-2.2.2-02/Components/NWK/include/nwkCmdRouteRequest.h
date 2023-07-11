/******************************************************************************
  nwkCmdRouteRequest.h
  Copyright (c)Meshnetics.
  Description: 
    route request command types and functions.
  History:
    17/09/07 V. Panov - Created.
******************************************************************************/
#ifndef _NWKCMDROUTEREQUEST_H
#define _NWKCMDROUTEREQUEST_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <nwk.h>
#include <nwkFrame.h>

/******************************************************************************
                   Types section
******************************************************************************/
#define CONST_COST 7

typedef enum _NwkRouteRequestManyToOneFlag_t {
  RR_NOT_MANY_TO_ONE                     = 0,
  RR_MANY_TO_ONE_SENDER_WITH_RRTABLE     = 1,
  RR_MANY_TO_ONE_SENDER_WITHOUT_RRTABLE  = 2,
} NwkRouteRequestManyToOneFlag_t;

BEGIN_PACK
typedef struct PACK _NwkRouteRequestOptions_t
{
  uint8_t reserved1  : 3;
  uint8_t manyToOne  : 2;
  uint8_t dstExt     : 1;
  uint8_t multicast  : 1;
  uint8_t reserved2  : 1;
} NwkRouteRequestOptions_t;

typedef struct PACK _NwkRouteRequestFrame_t
{
  union PACK 
  {
    NwkRouteRequestOptions_t   cmdOptions;
    uint8_t                    cmdOptionsByte;
  };
  uint8_t                    identifier;
  ShortAddr_t                dstAddr;
  uint8_t                    pathCost;
  ExtAddr_t                  dstExt;
} NwkRouteRequestFrame_t;
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
void nwkRouteReqFrameInd(uint8_t *payload, NwkFrameHeader_t *header, NwkParseHeader_t *parse);

/******************************************************************************
//preparing nwk payload for route request
//route table items to process stored in global pointers
******************************************************************************/
void cmdRouteReqPrepareMacData(uint8_t *data);

/******************************************************************************
preparing mac request for route request frame
******************************************************************************/
void cmdRouteReqPrepareMacReq(MAC_DataReq_t *req);

/******************************************************************************
route request sent ready to 
******************************************************************************/
void cmdRouteReqConfirm(uint8_t status);

#endif
//eof
