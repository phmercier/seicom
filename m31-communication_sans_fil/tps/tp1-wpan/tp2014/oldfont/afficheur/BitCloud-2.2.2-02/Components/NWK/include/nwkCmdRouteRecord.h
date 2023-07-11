/******************************************************************************
  nwkCmdRouteRequest.h
  Copyright (c)Meshnetics.
  Description: 
    route record command types and functions.
  History:
    28/09/07 V. Panov - Created.
******************************************************************************/
#ifndef _NWKCMDROUTERECORD_H
#define _NWKCMDROUTERECORD_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <nwk.h>
#include <nwkFrame.h>

/******************************************************************************
                   Types section
******************************************************************************/
BEGIN_PACK
typedef struct PACK _NwkRouteRecordFrame_t
{
  uint8_t                 relayCount;
  ShortAddr_t             relayList[1];
} NwkRouteRecordFrame_t;
END_PACK

typedef struct _NwkRouteRecordItem_t
{
  ShortAddr_t path[NWKC_ROUTE_RECORD_ITEM_SIZE];
  uint8_t     pathSize;
  bool        active;
} NwkRouteRecordItem_t;

typedef struct _NwkRouteRecordTable_t
{
  NwkRouteRecordItem_t table[NWKC_ROUTE_RECORD_TABLE_SIZE];
  uint8_t index;
} NwkRouteRecordTable_t;

typedef struct _NwkRouteRecord_t
{
  NwkRouteRecordTable_t table;
} NwkRouteRecord_t;


/******************************************************************************
  prototypes
******************************************************************************/

/******************************************************************************
  action when command received
payload - cmd payload
header  - nwk header
parse   - parsed header fields
******************************************************************************/
void nwkRouteRecordFrameInd(uint8_t *payload, NwkFrameHeader_t *header, NwkParseHeader_t *parse);

void nwkRouteRecordConfirm(void);
void nwkRouteRecordRequest(ShortAddr_t dstAddr, NWK_DstAddrMode_t dstAddrMode);

NwkRouteRecordItem_t* nwkRouteRecordFindByDest(ShortAddr_t addr);

#endif
//eof
