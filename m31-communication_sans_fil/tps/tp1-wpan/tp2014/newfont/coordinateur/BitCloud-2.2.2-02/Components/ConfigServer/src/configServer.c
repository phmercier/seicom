/*****************************************************************************
  configServer.c

  Copyright (c)Meshnetics
  
  Description:
    Config Server implementation
    
  History:
    04/07/07 A. Potashov - Created
*****************************************************************************/
 
#include <configServer.h>
#include <macAddr.h>
#include <macBuffers.h>

#ifndef _MAC2_
#include <appFramework.h>
#include <aps.h>
#include <apsDataManager.h>
#include <apsGroupManager.h>
#include <apsSecurityManager.h>
#include <neibTable.h>
#include <nwkDataReq.h>
#include <dbg.h>
#include <nwkJoinInd.h>
#include <nwkRouteTable.h>
#include <nwkAddrMap.h>
#include <nwkRouteDiscovery.h>
#include <pdsDataServer.h>
#include <zdo.h>
#include <nwk.h>

#if defined(_SECURITY_)
#include <tcAuthentic.h>
#ifdef _HIGH_SECURITY_
#include <tcKeyEstablish.h>
#endif
#endif
#endif // _MAC2_

/*****************************************************************************
  Allocated memory
*****************************************************************************/
#ifndef _MAC2_

static Neib_t      csNeibTable[CS_NEIB_TABLE_SIZE];

static uint64_t    csUId = CS_UID;

static ExtAddr_t   csExtPANID = CS_EXT_PANID;

static ExtAddr_t   csNwkExtPANID = CS_NWK_EXT_PANID;

static ShortAddr_t csNwkAddr = CS_NWK_ADDR;

static bool        csNwkUniqueAddr = CS_NWK_UNIQUE_ADDR;

static uint32_t    csChannelMask = CS_CHANNEL_MASK;

static uint8_t    csChannelPage = CS_CHANNEL_PAGE;

static uint32_t    csEndDeviceActivePeriod = CS_END_DEVICE_ACTIVE_PERIOD;

static uint32_t    csEndDeviceSleepPeriod = CS_END_DEVICE_SLEEP_PERIOD;

static NwkDataReqObj_t csNwkDataReqBuffer[CS_NWK_DATA_REQ_BUFFER_SIZE];

static NwkDataIndObj_t csNwkDataIndBuffer[CS_NWK_DATA_IND_BUFFER_SIZE];

static ApsDataManagerMemoryPoolEntry_t csApsDataReqBuffer[CS_APS_DATA_REQ_BUFFER_SIZE];

static ApsAcknowledgementEntry_t csApsAckFrameBuffer[CS_APS_ACK_FRAME_BUFFER_SIZE];

static uint32_t csIndirectPollRate = CS_INDIRECT_POLL_RATE;

static bool csAutonetwork = CS_AUTONETWORK;

static DeviceType_t csDeviceType = CS_DEVICE_TYPE;

static NwkAssociateRespObj_t csAssociateResponseBuffer[CS_MAX_CHILDREN_AMOUNT];

static NWK_NetworkDescriptor_t csNwkPanDescriptorBuffer[CS_NEIB_TABLE_SIZE];

static MAC_PanDescriptor_t csMacPanDescriptorBuffer[CS_NEIB_TABLE_SIZE];

static ApsDuplicateRejectionTableElement_t csDuplicateRejectionTable[CS_DUPLICATE_REJECTION_TABLE_SIZE];

static FrameRxBuffer_t csMacFrameRxBuffer[CS_MAC_FRAME_RX_BUFFER_SIZE];

static uint8_t csApsGroupTable[CS_APS_GROUP_TABLE_SIZEOF];

#ifdef CS_RX_ON_WHEN_IDLE
static bool csRxOnWhenIdle = CS_RX_ON_WHEN_IDLE;
#else
static bool csRxOnWhenIdle = (CS_DEVICE_TYPE == DEVICE_TYPE_END_DEVICE)?false:true;
#endif

static int8_t csRfTxPower = CS_RF_TX_POWER;

static uint8_t csSoftResetReason = CS_SOFT_RESET_REASON;

//Stack profile identifier
static uint8_t csStackProfileId = CS_STACK_PROFILE;

//Protocol version identifier
static uint8_t csProtocolVersionId = CS_PROTOCOL_VERSION;

static NwkRouteItem_t csRouteTable[CS_ROUTE_TABLE_SIZE];
static NwkAddrMapItem_t csAddressMapTable[CS_ADDRESS_MAP_TABLE_SIZE];
static NwkRouteDiscoveryItem_t csRouteDiscoveryTable[CS_ROUTE_DISCOVERY_TABLE_SIZE];


static bool csDtrWakeup = CS_DTR_WAKEUP;
static uint8_t csMaxFrameTransmissionTime = CS_MAX_FRAME_TRANSMISSION_TIME;
static uint8_t csNwkLogicalChannel = 0;
static uint16_t csNwkPanid = 0;


/*****************************************************************************
 The Permit duration parameter affect directly to asscociation permit in 
 MAC layer.
 0xff - always on
 0x00 - always off
*****************************************************************************/
static uint8_t csPermitDuration = CS_PERMIT_DURATION;
//============================================================================

static bool csNwkUseMulticast = CS_NWK_USE_MULTICAST;
static uint32_t csMacTransactionTime = CS_MAC_TRANSACTION_TIME;

#if defined(_SECURITY_)
static NWK_SecurityIB_t  csNwkSecurityIb;
static uint8_t  csZdoSecurityStatus = CS_ZDO_SECURITY_STATUS;
PROGMEM_DECLARE(static const uint32_t  csApsSecurityTimeoutPeriod) = CS_APS_SECURITY_TIMEOUT_PERIOD;
static ExtAddr_t csApsTrustCenterAddress = CS_APS_TRUST_CENTER_ADDRESS;
static uint8_t csNetworkKey[16] = CS_NETWORK_KEY;
static ApsSmBuffer_t csApsSecurityBuffers[CS_APS_SECURITY_BUFFERS_AMOUNT];
static TC_AuthenticObj_t csTcAuthenticProcessBuffer[CS_MAX_TC_AUTHENTIC_PROCESS_AMOUNT];
#ifdef _TC_PERMISSION_TABLE_
  static ExtAddr_t csTcDevicePermissionTable[CS_MAX_TC_ALLOWED_DEVICES_AMOUNT];
#endif
#ifdef _HIGH_SECURITY_
static ApsKeyPairDescriptor_t csApsKeyPairDescriptors[CS_APS_KEY_PAIR_DESCRIPTORS_AMOUNT];
PROGMEM_DECLARE(static const uint8_t csLinkKey[16]) = CS_LINK_KEY;
PROGMEM_DECLARE(static const uint8_t csMasterKey[16]) = CS_MASTER_KEY;
static TC_KeyEstablishObj_t csTcEstablishKeyBuffer[CS_MAX_TC_ESTABLISH_KEY_AMOUNT];
#endif
#endif

#else   // _MAC2_

// variables. Memory was not allocate for CS_MAC_TRANSACTION_TIME.
static uint64_t    csUId                      = CS_UID;
static int8_t      csRfTxPower                = CS_RF_TX_POWER;
static uint8_t     csMaxFrameTransmissionTime = CS_MAX_FRAME_TRANSMISSION_TIME;
// buffers
static FrameRxBuffer_t csMacFrameRxBuffer[CS_MAC_FRAME_RX_BUFFER_SIZE];
static uint32_t csMacTransactionTime = CS_MAC_TRANSACTION_TIME;

#endif  // _MAC2_

/*****************************************************************************
Read parameter value specified by parameter identifier
Parameters:  
  parameterId     - parameter Id
  parameterValue  - parameter value pointer will be read to
Returns:
  None
*****************************************************************************/
void CS_ReadParameter(CS_ParameterId_t parameterId, void *parameterValue)
{
  if (parameterValue)
  {
    switch (parameterId)
    {
#ifndef _MAC2_
      case CS_AUTONETWORK_ID:
        *((bool *) parameterValue) = csAutonetwork;
        break;
      case CS_DEVICE_TYPE_ID:
        *((DeviceType_t *) parameterValue) = csDeviceType;
        break;
      case CS_NWK_ADDR_ID:
        *((ShortAddr_t *) parameterValue) = csNwkAddr;
        break;
      case CS_RX_ON_WHEN_IDLE_ID:
        *((bool *) parameterValue) = csRxOnWhenIdle;
        break;
      case CS_INDIRECT_POLL_RATE_ID:
        *((uint32_t *) parameterValue) = csIndirectPollRate;
        break;
      case CS_NEIB_TABLE_SIZE_ID:
        *((uint8_t *) parameterValue) = CS_NEIB_TABLE_SIZE;
        break;
      case CS_MAX_CHILDREN_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_MAX_CHILDREN_AMOUNT;
        break;
      case CS_MAX_CHILDREN_ROUTER_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_MAX_CHILDREN_ROUTER_AMOUNT;
        break;
      case CS_MAX_NETWORK_DEPTH_ID:
        *((uint8_t *) parameterValue) = CS_MAX_NETWORK_DEPTH;
        break;
      case CS_END_DEVICE_ACTIVE_PERIOD_ID:
        *((uint32_t *) parameterValue) = csEndDeviceActivePeriod;
        break;
      case CS_END_DEVICE_SLEEP_PERIOD_ID:
        *((uint32_t *) parameterValue) = csEndDeviceSleepPeriod;
        break;
      case CS_ADDRESS_ASSIGNMENT_METHOD_ID:
        *((uint8_t *) parameterValue) = CS_ADDRESS_ASSIGNMENT_METHOD;
        break;
      case CS_NWK_DATA_IND_BUFFER_SIZE_ID:
        *((uint8_t *) parameterValue) = CS_NWK_DATA_IND_BUFFER_SIZE;
        break;
      case CS_NWK_DATA_REQ_BUFFER_SIZE_ID:
        *((uint8_t *) parameterValue) = CS_NWK_DATA_REQ_BUFFER_SIZE;
        break;
      case CS_APS_DATA_REQ_BUFFER_SIZE_ID:
        *((uint8_t *) parameterValue) = CS_APS_DATA_REQ_BUFFER_SIZE;
        break;
      case CS_APS_ACK_FRAME_BUFFER_SIZE_ID:
        *((uint8_t *) parameterValue) = CS_APS_ACK_FRAME_BUFFER_SIZE;
        break;
      case CS_PROTOCOL_VERSION_ID:
        *((uint8_t *) parameterValue) = csProtocolVersionId;
        break;
      case CS_STACK_PROFILE_ID:
        *((uint8_t *) parameterValue) = csStackProfileId;
        break;
      case CS_SCAN_DURATION_ID:
        *((uint8_t *) parameterValue) = CS_SCAN_DURATION;
        break;
      case CS_PERMIT_DURATION_ID:
        *((uint8_t *) parameterValue) = csPermitDuration;
        break;
      case CS_NWK_EXT_PANID_ID:
        *((ExtAddr_t *) parameterValue) = csNwkExtPANID;
        break;
      case CS_EXT_PANID_ID:
        *((ExtAddr_t *) parameterValue) = csExtPANID;
        break;
      case CS_CHANNEL_MASK_ID:
        *((uint32_t *) parameterValue) = csChannelMask;
        break;
      case CS_CHANNEL_PAGE_ID:
        *((uint8_t *) parameterValue) = csChannelPage;
        break;
#endif // _MAC2_
      case CS_UID_ID:
        //*((uint64_t *) parameterValue) = csUId;
		memcpy(parameterValue, &csUId, sizeof(uint64_t));
        break;
#ifndef _MAC2_
      case CS_DUPLICATE_REJECTION_TABLE_SIZE_ID:
        *((uint8_t *) parameterValue) = CS_DUPLICATE_REJECTION_TABLE_SIZE;
        break;
      case CS_ACK_TIMEOUT_ID :
        *((uint32_t *) parameterValue) = CS_ACK_TIMEOUT;
        break;
#endif // _MAC2_
      case CS_MAC_FRAME_RX_BUFFER_SIZE_ID:
        *((uint8_t *) parameterValue) = CS_MAC_FRAME_RX_BUFFER_SIZE;
        break;
#ifndef _MAC2_
      case CS_APS_GROUP_TABLE_ENDPOINTS_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_APS_GROUP_TABLE_ENDPOINTS_AMOUNT;
        break;  
      case CS_APS_GROUP_TABLE_GROUPS_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_APS_GROUP_TABLE_GROUPS_AMOUNT;
        break;
#endif // _MAC2_		
      case CS_RF_TX_POWER_ID:
        *((int8_t *) parameterValue) = csRfTxPower;
        break;
#ifndef _MAC2_
      case CS_SOFT_RESET_REASON_ID:
        *((uint8_t *) parameterValue) = csSoftResetReason;
        break;
      case CS_NWK_USE_MULTICAST_ID:
        *((bool *) parameterValue) = csNwkUseMulticast;
        break;
      case CS_ROUTE_TABLE_SIZE_ID:
        *((uint8_t *) parameterValue) = CS_ROUTE_TABLE_SIZE;
        break;
      case CS_ADDRESS_MAP_TABLE_SIZE_ID:
        *((uint8_t *) parameterValue) = CS_ADDRESS_MAP_TABLE_SIZE;
        break;
      case CS_ROUTE_DISCOVERY_TABLE_SIZE_ID:
        *((uint8_t *) parameterValue) = CS_ROUTE_DISCOVERY_TABLE_SIZE;
        break;
#endif //_MAC2_
      case CS_MAC_TRANSACTION_TIME_ID:
        *((uint32_t *) parameterValue) = csMacTransactionTime;
        break;
#ifndef _MAC2_
      case CS_NWK_UNIQUE_ADDR_ID:
        *((bool *) parameterValue) = csNwkUniqueAddr;
        break;
      case CS_DTR_WAKEUP_ID:
        *((bool *) parameterValue) = csDtrWakeup;
        break;
      case CS_NWK_LOGICAL_CHANNEL_ID:
        *((uint8_t *) parameterValue) = csNwkLogicalChannel;
        break;
      case CS_NWK_PANID_ID:
        *((uint16_t *) parameterValue) = csNwkPanid;
        break;
#endif // _MAC2_
      case CS_MAX_FRAME_TRANSMISSION_TIME_ID:
        *((uint8_t *) parameterValue) = csMaxFrameTransmissionTime;
        break;
#ifndef _MAC2_
/***********************************************************************
 Security related action's
***********************************************************************/
#ifdef _SECURITY_
      case CS_APS_SECURITY_BUFFERS_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_APS_SECURITY_BUFFERS_AMOUNT;
        break;
      case CS_APS_SECURITY_TIMEOUT_PERIOD_ID:
        memcpy_P(parameterValue, &csApsSecurityTimeoutPeriod, sizeof(uint32_t)); 
        break;
      case CS_APS_TRUST_CENTER_ADDRESS_ID:
        memcpy(parameterValue, &csApsTrustCenterAddress, sizeof(ExtAddr_t)); 
        break;
      case CS_ZDO_SECURITY_STATUS_ID:        
        *((uint8_t *) parameterValue) = csZdoSecurityStatus;
        break;
      case CS_SECURITY_LEVEL_ID:
        *((uint8_t *) parameterValue) = CS_SECURITY_LEVEL;
        break;
      case CS_SECURITY_ALL_FRAMES_ID:
        *((uint8_t *) parameterValue) = CS_SECURITY_ALL_FRAMES;
        break;
      case CS_NETWORK_KEY_ID:       
		memcpy(parameterValue, csNetworkKey, sizeof(csNetworkKey));
        break;
	  case CS_MAX_TC_AUTHENTIC_PROCESS_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_MAX_TC_AUTHENTIC_PROCESS_AMOUNT; 
		break;  
#ifdef _TC_PERMISSION_TABLE_
	  case CS_MAX_TC_ALLOWED_DEVICES_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_MAX_TC_ALLOWED_DEVICES_AMOUNT;  
	    break; 	  
#endif
#ifdef _HIGH_SECURITY_
      case CS_APS_KEY_PAIR_DESCRIPTORS_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_APS_KEY_PAIR_DESCRIPTORS_AMOUNT;
        break;
      case CS_LINK_KEY_ID:
        memcpy_P(parameterValue, csLinkKey, sizeof(csLinkKey));
        break;
      case CS_MASTER_KEY_ID:
        memcpy_P(parameterValue, csMasterKey, sizeof(csMasterKey));
        break;
      case CS_MAX_TC_ESTABLISH_KEY_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_MAX_TC_ESTABLISH_KEY_AMOUNT; 
		break;  
#endif // _SECURITY_
#endif // _HIGH_SECURITY_
#endif // _MAC2_
      default:
        break;
    }
  }
}


/*****************************************************************************
Allocate memory area specified by memory identifier
Parameters:  
  memoryId        - memory area Id
  memoryPtr       - pointer to pointer wich will be modified
Returns:
  None
*****************************************************************************/
void CS_GetMemory(CS_MemoryId_t memoryId, void **memoryPtr)
{
  switch (memoryId)
  {
#ifndef _MAC2_
    case CS_NEIB_TABLE_ID:
      *memoryPtr = csNeibTable;
      break;
    case CS_NWK_DATA_REQ_BUFFER_ID:
      *memoryPtr = csNwkDataReqBuffer;
      break;
    case CS_NWK_DATA_IND_BUFFER_ID:
      *memoryPtr = csNwkDataIndBuffer;
      break;
    case CS_APS_DATA_REQ_BUFFER_ID:
      *memoryPtr = csApsDataReqBuffer;
      break;
    case CS_APS_ACK_FRAME_BUFFER_ID:
      *memoryPtr = csApsAckFrameBuffer;
      break;
    case CS_ASSOCIATE_RESPONSE_BUFFER_ID:
      *memoryPtr = csAssociateResponseBuffer;    
      break;  
    case CS_NWK_PAN_DESCRIPTOR_BUFFER_ID:
      *memoryPtr = csNwkPanDescriptorBuffer;    
      break; 
    case CS_MAC_PAN_DESCRIPTOR_BUFFER_ID:
      *memoryPtr = csMacPanDescriptorBuffer;    
      break; 
    case CS_DUPLICATE_REJECTION_TABLE_ID:
      *memoryPtr = csDuplicateRejectionTable;
      break;
#endif //_MAC2_
    case CS_MAC_FRAME_RX_BUFFER_ID:
      *memoryPtr = csMacFrameRxBuffer;
      break;
#ifndef _MAC2_
    case CS_APS_GROUP_TABLE_ID:
      *memoryPtr = csApsGroupTable;
      break;
    case CS_ROUTE_TABLE_ID:
      *memoryPtr = csRouteTable;
      break;
    case CS_ADDRESS_MAP_TABLE_ID:
      *memoryPtr = csAddressMapTable;
      break;
    case CS_ROUTE_DISCOVERY_TABLE_ID:
      *memoryPtr = csRouteDiscoveryTable;
      break;    
/***********************************************************************
  Security related action's
***********************************************************************/
#if defined(_SECURITY_)
      case CS_NWK_SECURITY_IB_ID:
        *memoryPtr = &csNwkSecurityIb;
        break;
      case CS_APS_SECURITY_BUFFERS_ID:
        *memoryPtr = csApsSecurityBuffers;
        break;
      case CS_TC_AUTHENTIC_PROCESS_BUFFER_ID:
        *memoryPtr = csTcAuthenticProcessBuffer;
        break; 
#ifdef _TC_PERMISSION_TABLE_
      case CS_TC_PERMISSION_TABLE_ID:
        *memoryPtr = csTcDevicePermissionTable;
        break; 
#endif
#ifdef _HIGH_SECURITY_
      case CS_APS_KEY_PAIR_DESCRIPTORS_ID:
        *memoryPtr = csApsKeyPairDescriptors;
        break;
      case CS_TC_ESTABLISH_KEY_BUFFER_ID:
        *memoryPtr = csTcEstablishKeyBuffer;
        break;
#endif
#endif
#endif //_MAC2_
    default:
      *memoryPtr = NULL;
      break;
  }
}


/*****************************************************************************
Write parameter value specified by parameter identifier and parameter value 
pointer
Parameters:  
  parameterId     - parameter Id
  parameterValue  - parameter value pointer will be write from
Returns:
  None
*****************************************************************************/
extern void CS_WriteParameter(CS_ParameterId_t parameterId, void *parameterValue)
{
  switch (parameterId)
  {
#ifndef _MAC2_
    case CS_NWK_ADDR_ID:  
      csNwkAddr = *(ShortAddr_t *) parameterValue;  
	  break;
    case CS_NWK_UNIQUE_ADDR_ID:
      csNwkUniqueAddr = *(bool *) parameterValue;
      break;
    case CS_AUTONETWORK_ID:
      csAutonetwork = *(bool *) parameterValue;
      break;
    case CS_DEVICE_TYPE_ID:
      csDeviceType = *(DeviceType_t *) parameterValue;
      break;
#endif // _MAC2_
    case CS_UID_ID:
      csUId = *(uint64_t *) parameterValue;
      break;
#ifndef _MAC2_
    case CS_EXT_PANID_ID:
      csExtPANID = *(uint64_t *) parameterValue;
      break;
    case CS_NWK_EXT_PANID_ID:
      csNwkExtPANID = *(uint64_t *) parameterValue;
      break;
    case CS_RX_ON_WHEN_IDLE_ID:
      csRxOnWhenIdle = *(bool *) parameterValue;
      break;
    case CS_CHANNEL_MASK_ID:
      csChannelMask = *(uint32_t *) parameterValue;
      break;
    case CS_CHANNEL_PAGE_ID:
      csChannelPage = *(uint8_t *) parameterValue;
      break;
#endif //_MAC2_
    case CS_RF_TX_POWER_ID:
      csRfTxPower = *(int8_t *) parameterValue;
      break;
#ifndef _MAC2_
    case CS_SOFT_RESET_REASON_ID:
      csSoftResetReason = *(uint8_t *) parameterValue;
      break;
    case CS_STACK_PROFILE_ID:
      csStackProfileId = *(uint8_t *) parameterValue;
      break;
    case CS_PROTOCOL_VERSION_ID:
      csProtocolVersionId = *(uint8_t *) parameterValue;
      break;
    case CS_PERMIT_DURATION_ID:
      csPermitDuration = *(uint8_t *) parameterValue;
      break;
    case CS_INDIRECT_POLL_RATE_ID:
      csIndirectPollRate = *(uint32_t *) parameterValue;
      break;
    case CS_END_DEVICE_ACTIVE_PERIOD_ID:
      csEndDeviceActivePeriod = *(uint32_t *) parameterValue;
      break;
    case CS_END_DEVICE_SLEEP_PERIOD_ID:
      csEndDeviceSleepPeriod = *(uint32_t *) parameterValue;
      break;
    case CS_NWK_USE_MULTICAST_ID:
      csNwkUseMulticast = *(bool *) parameterValue;
      break;
    case CS_DTR_WAKEUP_ID:      
	  csDtrWakeup = *(bool *) parameterValue;
      break;
    case CS_NWK_LOGICAL_CHANNEL_ID:
      csNwkLogicalChannel = *(uint8_t *) parameterValue;
      break;
    case CS_NWK_PANID_ID:
      csNwkPanid = *(uint16_t *) parameterValue;
      break;
#endif //_MAC2_
    case CS_MAX_FRAME_TRANSMISSION_TIME_ID:
	  csMaxFrameTransmissionTime = *(uint8_t *) parameterValue;
      break;
    case CS_MAC_TRANSACTION_TIME_ID:
      csMacTransactionTime = *(uint32_t *) parameterValue;
      break;      
#ifndef _MAC2_
#ifdef _SECURITY_
    case CS_ZDO_SECURITY_STATUS_ID:     
      csZdoSecurityStatus = *(uint8_t *) parameterValue;        
      break;
    case CS_NETWORK_KEY_ID:       
      memcpy(&csNetworkKey, parameterValue, sizeof(csNetworkKey));
      break;
    case CS_APS_TRUST_CENTER_ADDRESS_ID:  
      memcpy(&csApsTrustCenterAddress, parameterValue, sizeof(uint64_t));
      break;
#endif       
#endif //_MAC2_
    default:
      break;
  }
}



/*****************************************************************************
Init the Config Server
Parameters:  
  None
Returns:
  None
*****************************************************************************/
void CS_Init(void)
{
  PDS_Init();  
}

/*****************************************************************************
Set PDS default
Parameters:  
  None
Returns:
  None
*****************************************************************************/
void CS_PdsDefaultValue(void)
{
#ifndef _MAC2_
  csNwkExtPANID = CS_NWK_EXT_PANID;  
  csExtPANID = CS_EXT_PANID;
  csNwkAddr = CS_NWK_ADDR;
  csChannelMask = CS_CHANNEL_MASK;
  csChannelPage= CS_CHANNEL_PAGE;
#endif //_MAC2_
  csUId = CS_UID;
#ifndef _MAC2_
  csAutonetwork = CS_AUTONETWORK;
  csDeviceType = CS_DEVICE_TYPE;
  #ifdef CS_RX_ON_WHEN_IDLE
    csRxOnWhenIdle = CS_RX_ON_WHEN_IDLE;
  #else
    csRxOnWhenIdle = (CS_DEVICE_TYPE == DEVICE_TYPE_END_DEVICE)?false:true;
  #endif
#endif //_MAC2_
  csRfTxPower = CS_RF_TX_POWER;
#ifndef _MAC2_
  csSoftResetReason = CS_SOFT_RESET_REASON;
  csNwkUniqueAddr = CS_NWK_UNIQUE_ADDR;
  csDtrWakeup = CS_DTR_WAKEUP;
  csNwkLogicalChannel = 0;
  csNwkPanid = 0;

  #if defined(_SECURITY_)
  /* parameters is read from flash */
  #endif
#endif //_MAC2_
}

