/******************************************************************************
  nib.h
  Copyright (c)Meshnetics.
  Description:
    NIB header file.
  History:
    14/06/07 S. Vladykin - Created.
******************************************************************************/
#ifndef _NIB_H
#define _NIB_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <types.h>
#include <appFramework.h>
#include <nwk.h>
#include <neibTable.h>
#include <mac.h>
#include <queue.h>
#include <nwkFrame.h>

/******************************************************************************
                   Types section
******************************************************************************/
typedef struct _NIB_t
{
// Standard part
  uint8_t             sequenceNumber;
  uint8_t             passiveAckTimeout;
  uint8_t             maxBroadcastRetries;
  uint8_t             maxDepth;
  uint8_t             maxRouters;
  uint8_t             maxChildren;
  uint8_t             networkBroadcastDeliveryTime;
  uint8_t             reportConstantCost;
  uint8_t             routeDiscoveryRetriesPermitted;
  bool                symLink;
  MAC_CapabilityInf_t capabilityInformation;
  uint8_t             addrAlloc;
  bool                useTreeRouting;
  uint16_t            managerAddr;
  uint8_t             maxSourceRoute;
  uint16_t            transactionPersistenceTime;
  ShortAddr_t         networkAddress;
  uint8_t             stackProfile;
  uint8_t             protocolVersion;
  PanId_t             panId;
  ExtPanId_t          extendedPanId;
  bool                useMulticast;
  bool                isConcentrator;
  uint8_t             concentratorRadius;
  uint8_t             concentratorDiscoveryTime;
  uint8_t             linkStatusPeriod;
  uint8_t             routerAgeLimit;
  bool                uniqueAddr;
  bool                timeStamp;
  uint8_t             updateId;
//security
#ifdef _SECURITY_
  NWK_SecurityIB_t    *securityIB;
#endif
// user part  
  uint8_t             depth;
  uint16_t            cSkipChildren;
  uint16_t            cSkipSibling;
  uint8_t             logicalChannel;
  ShortAddr_t         parentNetworkAddress;
  DeviceType_t        deviceType;
  ExtAddr_t           extendedAddress;
  uint16_t            transmitCounter;
  uint16_t            transmitFailureCounter;
  struct {
   uint8_t            macBeaconPayloadHeader[MAC_MAX_BEACON_HEADER_LENGTH];
   NwkBeaconPayload_t beaconPayload;
  };
  NeibTable_t         neibTable;
} NIB_t;

/******************************************************************************
                   Prototypes section
******************************************************************************/

/******************************************************************************
  standard get request
  confirm is not used, result on function exit
******************************************************************************/
void NWK_GetReq(NWK_GetReq_t *req);

/******************************************************************************
  standard set request
  confirm is not used, result on function exit
******************************************************************************/
void NWK_SetReq(NWK_SetReq_t *req);

/******************************************************************************
  reset routine
******************************************************************************/
void nwkResetNib(bool commission);

/******************************************************************************
  update beacon payload depending on nib values
******************************************************************************/
void nibUpdateBeaconPayload(void);

/******************************************************************************
  get sequence number for new frame
******************************************************************************/
uint8_t nibGetSequenceNumber(void);

/******************************************************************************
  set depth in nib. cSkips updated
******************************************************************************/
void nibSetDepth(uint8_t depth);

/******************************************************************************
******************************************************************************/
uint8_t nibGetChannelPage(void);

/******************************************************************************
******************************************************************************/
#ifdef _SECURITY_
NWK_SecMaterialDescriptor_t *nwkFindDescriptor(uint8_t seqNu);
#endif

void nwkNibCheckDeviceType(void);

void nwkNibInitTimeDelays(void);
uint8_t nibGetMaxFrameTransmissionTime(void);

#endif //_NIB_H
//eof nib.h
