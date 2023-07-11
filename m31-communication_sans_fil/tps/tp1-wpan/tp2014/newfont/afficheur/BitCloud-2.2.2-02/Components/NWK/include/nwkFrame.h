/******************************************************************************
  nwkFrame.h
  Copyright (c)Meshnetics.
  Description: 
    nwk frames header file.
  History:
    01/07/07 S. Vladykin - Created.
******************************************************************************/
#ifndef _NWKFRAME_H
#define _NWKFRAME_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <nwk.h>
#include <types.h>

/******************************************************************************
                   Types section
******************************************************************************/
typedef enum _NwkFrameTypeFlag_t
{
  NWK_FRAMETYPE_DATA     =  0,
  NWK_FRAMETYPE_COMMAND  =  1
} NwkFrameTypeFlag_t;

typedef enum _NwkDiscoverRouteFlag_t
{
  NWK_DISCOVER_ROUTE_SUPPRESS    =  0,
  NWK_DISCOVER_ROUTE_ENABLE      =  1,
} NwkDiscoverRouteFlag_t;

BEGIN_PACK
typedef struct PACK _NwkFrameControl_t
{
  uint16_t frameType       : 2;
  uint16_t protocolVersion : 4;
  uint16_t discoverRoute   : 2;
  uint16_t multicastFlag   : 1;
  uint16_t security        : 1;
  uint16_t sourceRoute     : 1;
  uint16_t dstExtAddr      : 1;
  uint16_t srcExtAddr      : 1;
} NwkFrameControl_t;

typedef struct PACK 
{
  ExtAddr_t value;
} NwkFrameExtAddr_t;
END_PACK

enum
{
  NWK_FRAME_MULTICAST_NON_MEMBER_MODE  =  0,
  NWK_FRAME_MULTICAST_MEMBER_MODE      =  1,
};

BEGIN_PACK
typedef struct PACK _NwkFrameMulticastField_t
{
  uint8_t multicastMode      : 2;
  uint8_t nonMemberRadius    : 3;
  uint8_t maxNonMemberRadius : 3;
} NwkFrameMulticastField_t;

typedef struct PACK _NwkSourceRouteSubframe
{
  uint8_t     relayCount;
  uint8_t     relayIndex;
  ShortAddr_t relayList[1];
} NwkSourceRouteSubframe;
END_PACK

typedef struct _NwkParseHeader_t
{
  NwkFrameExtAddr_t        *dstExt;
  NwkFrameExtAddr_t         *srcExt;
  NwkFrameMulticastField_t *multicast;
  NwkSourceRouteSubframe   *sourceRouteSubframe;
  uint8_t                  *payload;
  uint8_t                  headerSize;
//there is reserved storage for mac source addr of data indication
  ShortAddr_t macSrcAddr;
  uint8_t lqi;
  uint8_t rssi;
} NwkParseHeader_t;

BEGIN_PACK
typedef struct PACK _NwkFrameHeader
{
  NwkFrameControl_t     frameControl;
  ShortAddr_t           dstAddr;
  ShortAddr_t           srcAddr;
  uint8_t               radius;
  uint8_t               sequenceNumber;
  union PACK {
    struct PACK
    {
      NwkFrameExtAddr_t         dstExt;
      NwkFrameExtAddr_t         srcExt;
      uint8_t                   payload[1];
    } dst_src;
    struct PACK
    {
      NwkFrameExtAddr_t         srcExt;
      uint8_t                   payload[1];
    } src;
    struct PACK
    {
      NwkFrameMulticastField_t  multicast;
      uint8_t                   payload[1];
    } multicast;
    struct PACK
    {
      NwkFrameExtAddr_t         dstExt;
      NwkFrameExtAddr_t         srcExt;
      NwkFrameMulticastField_t  multicast;
      uint8_t                   payload[1];
    } dst_src_multicast;
    uint8_t                     payload[1];
  };
} NwkFrameHeader_t;

typedef struct PACK _NwkBeaconPayload
{
  uint8_t  protocolId;
  struct PACK {
  uint8_t  stackProfile       : 4;
  uint8_t  nwkProtocolVersion : 4;
  };
  struct PACK {
  uint8_t  reserved           : 2;
  uint8_t  routerCapacity     : 1;
  uint8_t  deviceDepth        : 4;
  uint8_t  endDeviceCapacity  : 1;
  };
  uint64_t nwkExtendedPanid;
  struct PACK {
  uint32_t txOffset           :24;
  };
  uint8_t  updateId;
} NwkBeaconPayload_t;
END_PACK

enum {
  NWK_CMD_ROUTE_REQUEST   = 0x01, // Route request 3.4.1
  NWK_CMD_ROUTE_REPLY     = 0x02, // Route reply 3.4.2
  NWK_CMD_NETWORK_STATUS  = 0x03, // Network Status 3.4.3
  NWK_CMD_LEAVE           = 0x04, // Leave 3.4.4
  NWK_CMD_ROUTE_RECORD    = 0x05, // Route Record 3.4.5
  NWK_CMD_REJOIN_REQUEST  = 0x06, // Rejoin request 3.4.6
  NWK_CMD_REJOIN_RESPONSE = 0x07, // Rejoin response 3.4.7
  NWK_CMD_LINK_STATUS     = 0x08, // Link Status 3.4.8
  NWK_CMD_NETWORK_REPORT  = 0x09, // Network Report 3.4.9
  NWK_CMD_NETWORK_UPDATE  = 0x0a, // Network Update 3.4.10
};

BEGIN_PACK
typedef struct PACK 
{
  uint8_t entryCount : 4;
  uint8_t firstFrame : 1;
  uint8_t lastFrame  : 1;
  uint8_t reserved   : 1;
} NwkLinkStatusCommandOptions_t;

typedef struct PACK 
{
  uint8_t incomingCost : 3;
  uint8_t reserved1    : 1;
  uint8_t outgoingCost : 3;
  uint8_t reserved2    : 1;
} LinkStatus_t;

typedef struct PACK 
{
  ShortAddr_t  neighborAddress;
  LinkStatus_t linkStatus;
} LinkStatusEntry_t;
END_PACK

/******************************************************************************
                   Prototypes section
******************************************************************************/

/******************************************************************************
  clear frame, then fill it with commonly used fields
nwkHeader - pointer to header
******************************************************************************/
void nwkPrepareCommonFrame(NwkFrameHeader_t *nwkHeader);

/******************************************************************************
  parse floating fields of frame
nwkHeader - header to parse
parse     - structure with pointer to frame fields
            NULL - if field is not present, correct pointer otherwise
******************************************************************************/
void nwkParseHeader(NwkFrameHeader_t *nwkHeader, NwkParseHeader_t *parse);

#endif
