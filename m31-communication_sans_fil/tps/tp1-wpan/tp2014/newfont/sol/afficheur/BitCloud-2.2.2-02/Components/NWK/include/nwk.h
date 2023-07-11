/******************************************************************************
  nwk.h
  Copyright (c)Meshnetics.
  Description: 
    NWK  header file.
  History:
    14/06/07 S. Vladykin - Created.
******************************************************************************/
#ifndef _NWK_H
#define _NWK_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <mac.h>
#include <appFramework.h>
#include <types.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
#ifndef _SECURITY_
#define NWK_MAX_NSDU_SIZE                96
#define NWK_MAX_DATA_FRAME_HEADER_LEHGTH 9
#define NWK_MAX_DATA_FRAME_FOOTER_LENGTH 0
#endif

#ifdef _SECURITY_
#define NWK_MAX_NSDU_SIZE                96-14-16
#define NWK_MAX_DATA_FRAME_HEADER_LEHGTH 9+14
#define NWK_MAX_DATA_FRAME_FOOTER_LENGTH 16
#endif

#define NWK_AFFIX_LENGTH (NWK_MAX_DATA_FRAME_HEADER_LEHGTH + NWK_MAX_DATA_FRAME_FOOTER_LENGTH + MAC_AFFIX_LENGTH)
#define NWK_NSDU_OFFSET  (MAC_MSDU_OFFSET + NWK_MAX_DATA_FRAME_HEADER_LEHGTH)


#ifdef CS_NWK_DATA_IND_BUFFER_SIZE
#if CS_NWK_DATA_IND_BUFFER_SIZE < 3
#error CS_NWK_DATA_IND_BUFFER_SIZE shall be at least 3
#endif
#endif

#ifdef _SECURITY_
#ifdef CS_NWK_DATA_IND_BUFFER_SIZE
#if CS_NWK_DATA_IND_BUFFER_SIZE < 4
#error CS_NWK_DATA_IND_BUFFER_SIZE shall be at least 4 with security enabled 
#endif
#endif
#endif
/******************************************************************************
                   Types section
******************************************************************************/
typedef uint64_t ExtPanId_t;

typedef enum _NWK_DstAddrMode_t
{
  NWK_DSTADDRMODE_NOADDR = 0,
  NWK_DSTADDRMODE_MULTICAST = 1,
  NWK_DSTADDRMODE_SHORT = 2
} NWK_DstAddrMode_t;

typedef enum _NWK_AddrAlloc_t 
{
  NWK_ADDR_ALLOC_DISTRIBUTED = 0,
  NWK_ADDR_ALLOC_RESERVED    = 1,
  NWK_ADDR_ALLOC_STOCHASTIC  = 2,
} NWK_AddrAlloc_t;


typedef enum NWK_NIBAttribute_t
{
  NIB_PANID                             = 0x80,
  NIB_TIME_STAMP                        = 0x8C,
  NIB_SEQUENCE_NUMBER                   = 0x81,
  NIB_PASSIVE_ACK_TIMEOUT               = 0x82,
  NIB_MAX_BROADCAST_RETRIES             = 0x83,
  NIB_MAX_CHILDREN                      = 0x84,
  NIB_MAX_DEPTH                         = 0x85,
  NIB_MAX_ROUTERS                       = 0x86,
  NIB_NEIGHBOR_TABLE                    = 0x87,
  NIB_NETWORK_BROADCAST_DELIVERY_TIME   = 0x88,
  NIB_REPORT_CONSTANT_COST              = 0x89,
  NIB_ROUTE_DISCOVERY_RETRIES_PERMITTED = 0x8A,
  NIB_ROUTE_TABLE                       = 0x8B,
  NIB_SYM_LINK                          = 0x8E,
  NIB_CAPABILITY_INFORMATION            = 0x8F,
  NIB_ADDR_ALLOC                        = 0x90,
  NIB_USE_TREE_ROUTING                  = 0x91,
  NIB_MANAGER_ADDR                      = 0x92,
  NIB_MAX_SOURCE_ROUTE                  = 0x93,
  NIB_UPDATE_ID                         = 0x94,
  NIB_TRANSACTION_PERSISTENCE_TIME      = 0x95,
  NIB_NETWORK_ADDRESS                   = 0x96,
  NIB_STACK_PROFILE                     = 0x97,
  NIB_BROADCAST_TRANSACTION_TABLE       = 0x98,
  NIB_EXTENDED_PANID                    = 0x9A,
  NIB_USE_MULTICAST                     = 0x9B,
  NIB_ROUTE_RECORD_TABLE                = 0x9C,
  NIB_IS_CONCENTRATOR                   = 0x9D,
  NIB_CONCENTRATOR_RADIUS               = 0x9E,
  NIB_CONCENTRATOR_DISCOVERY_TIME       = 0x9F,
  NIB_SECURITY_LEVEL                    = 0xA0,
  NIB_SECURITY_MATERIAL_SET             = 0xA1,
  NIB_ACTIVE_KEY_SEQ_NUMBER             = 0xA2,
  NIB_ALL_FRESH                         = 0xA3,
  NIB_SECURE_ALL_FRAMES                 = 0xA5,
  NIB_LINK_STATUS_PERIOD                = 0xA6,
  NIB_ROUTER_AGE_LIMIT                  = 0xA7,
  NIB_UNIQUE_ADDR                       = 0xA8,
  NIB_ADDRESS_MAP                       = 0xA9,

  NIB_INT_LOGICAL_CHANNEL,
  NIB_INT_PARENT_SHORT,
  NIB_INT_TRANSMIT_COUNTER,
  NIB_INT_TRANSMIT_FAILURE_COUNTER,
  NIB_INT_DEPTH,

  NIB_INT_SECURITY_IB,
  NIB_INT_EXTENDED_ADDRESS,

} NWK_NIBAttribute_t;

typedef enum _NWK_RejoinNetwork_t
{
  NWK_REJOIN_ASSOCIATION    = 0,
  NWK_REJOIN_ORPHAN         = 1,
  NWK_REJOIN_NWK_REJOIN     = 2,
  NWK_REJOIN_CHANGE_CHANNEL = 3
} NWK_RejoinNetwork_t;

typedef enum _NWK_Status
{
  NWK_SUCCESS_STATUS                 = 0x00,
  NWK_INVALID_PARAMETERS_STATUS      = 0xC1,
  NWK_INVALID_REQUEST_STATUS         = 0xC2,
  NWK_NOT_PERMITTED_STATUS           = 0xC3,
  NWK_STARTUP_FAILURE_STATUS         = 0xC4,
  NWK_ALREADY_PRESENT_STATUS         = 0xC5,
  NWK_SYNC_FAILURE_STATUS            = 0xC6,
  NWK_NEIGHBOR_TABLE_FULL_STATUS     = 0xC7,
  NWK_UNKNOWN_DEVICE_STATUS          = 0xC8,
  NWK_UNSUPPORTED_ATTRIBUTE_STATUS   = 0xC9,
  NWK_NO_NETWORKS_STATUS             = 0xCA,
  NWK_MAX_FRM_COUNTER_STATUS         = 0xCC,
  NWK_NO_KEY_STATUS                  = 0xCD,
  NWK_BAD_CCM_OUTPUT_STATUS          = 0xCE,
  NWK_NO_ROUTING_CAPACITY_STATUS     = 0xCF,
  NWK_ROUTE_DISCOVERY_FAILED_STATUS  = 0xD0,
  NWK_ROUTE_ERROR_STATUS             = 0xD1,
  NWK_BT_TABLE_FULL_STATUS           = 0xD2,
  NWK_FRAME_NOT_BUFFERED_STATUS      = 0xD3,
} NWK_Status_t;

typedef enum _NWK_StatusIndErrorCodes_t
{
  NWK_NO_ROUTE_AVAILABLE    =  0x00,
  NWK_TREE_LINK_FAILURE,
  NWK_NON_TREE_LINK_FAILURE,
  NWK_LOW_BATTERY_LEVEL,
  NWK_NO_ROUTING_CAPACITY,
  NWK_NO_INDIRECT_CAPACITY,
  NWK_INDIRECT_TRANSACTION_EXPIRY,
  NWK_TARGET_DEVICE_UNAVAILABLE,
  NWK_TARGET_ADDRESS_UNALLOCATED,
  NWK_PARENT_LINK_FAILURE,
  NWK_VALIDATE_ROUTE,
  NWK_SOURCE_ROUTE_FAILURE,
  NWK_MANY_TO_ONE_ROUTE_FAILURE,
  NWK_ADDRESS_CONFLICT,
  NWK_VERIFY_ADDRESSES,
  NWK_PAN_IDENTIFIER_UPDATE,
  NWK_NETWORK_ADDRESS_UPDATE,
  NWK_BAD_FRAME_COUNTER,
  NWK_BAD_KEY_SEQUENCE_NUMBER,

  NWK_PARENT_LINK_SUCCESS,
  NWK_BAD_LINK,
} NWK_StatusIndErrorCodes_t;

enum
{
  BROADCAST_ADDR_ALL              =  0xFFFF,
  BROADCAST_ADDR_RX_ON_WHEN_IDLE  =  0xFFFD,
  BROADCAST_ADDR_ROUTERS          =  0xFFFC,
  BROADCAST_ADDR_LOWPOWER_ROUTERS =  0xFFFB,
  NWK_NO_SHORT_ADDR               =  0xFFFF,
  NWK_MIN_PANID                   =  1,
  NWK_MAX_PANID                   =  0xFFFE,
};

#define IS_BROADCAST_ADDR(A)     ((A)>=0xFFF8)
#define IS_CORRECT_SHORT_ADDR(A) ((A)< 0xFFF8)
#define IS_CORRECT_BROADCAST_ADDR(A) ( ((A)>= 0xFFFB) && (0xFE != (uint8_t)A) )
#define NWK_NO_EXT_ADDR        0

/* ---  --- */
typedef struct _NWK_NetworkDescriptor_t
{
  uint64_t      extendedPANId;
  uint32_t      logicalChannel;
  uint8_t       stackProfile;
  uint8_t       zigBeeVersion;
  uint8_t       beaconOrder;
  uint8_t       superframeOrder;
  bool          permitJoining;
  bool          routerCapacity;
  bool          endDeviceCapacity;
} NWK_NetworkDescriptor_t;

/* --- primitives' parameters --- */

typedef struct _NWK_DataConf_t 
{
  struct
  {
    void *next;                 // pointer used for queuing
  } service;

  uint8_t       nsduHandle;
  uint8_t       status;
  uint32_t      txTime;
} NWK_DataConf_t;

typedef struct _NWK_DataResp_t 
{
  uint8_t status;
} NWK_DataResp_t;

typedef struct _NWK_DataInd_t 
{
  struct
  {
    void *next;                 // pointer used for queuing
  } service;

  uint16_t              dstAddr;
  NWK_DstAddrMode_t     dstAddrMode;
  uint8_t               nsduLength;
  uint16_t              srcAddr;
  uint8_t               *nsdu;
  uint8_t               linkQuality;
  uint8_t               rssi;
  uint32_t              rxTime;
  bool                  securityUse;
  void                  (*NWK_DataResp)(NWK_DataResp_t *resp);
  NWK_DataResp_t        response;
} NWK_DataInd_t;

typedef struct _NWK_DataReq_t
{
  struct
  {
    void *next;                 // pointer used for queuing
  } service;
  NWK_DstAddrMode_t  dstAddrMode;
  uint16_t           dstAddr;
  uint8_t            nsduLength;
  uint8_t            *nsdu;
  uint8_t            nsduHandle;
  uint8_t            radius;
  uint8_t            nonmemberRadius;
  bool               discoverRoute;
  bool               securityEnable;
  void               (*NWK_DataConf)(NWK_DataConf_t *conf);
  NWK_DataConf_t     confirm;
} NWK_DataReq_t;

/* -- */

typedef struct _NWK_DirectJoinConf_t 
{
  uint8_t       status;
} NWK_DirectJoinConf_t;

typedef struct _NWK_DirectJoinReq_t
{
  struct
  {
    void *next;
  }  service;
  uint64_t             deviceAddress;
  uint8_t              capabilityInformation;
  void                 (*NWK_DirectJoinConf)(NWK_DirectJoinConf_t *conf);
  NWK_DirectJoinConf_t confirm;
} NWK_DirectJoinReq_t;

/* --- */

typedef struct _NWK_EDScanConf_t
{
  uint8_t       status;
  uint32_t      scannedChannels;
  uint16_t      energyDetectList[32];
  uint8_t       energyDetectListSize;
} NWK_EDScanConf_t;

typedef struct _NWK_EDScanReq_t
{
  struct
  {
    void             *next;
  }  service;
  uint32_t           scanChannels;
  uint8_t            scanDuration;

  void               (*NWK_EDScanConf)(NWK_EDScanConf_t *conf);
  NWK_EDScanConf_t   confirm;
} NWK_EDScanReq_t;

/* --- */

typedef struct _NWK_GetConf_t
{
  uint8_t               status;
  NWK_NIBAttribute_t    nibAttribute;
  uint8_t               nibAttributeLength;
  void                  *nibAttributeValue;
} NWK_GetConf_t;

typedef struct _NWK_GetReq_t
{
  struct
  {
    void               *next;
  }  service;
  NWK_NIBAttribute_t   nibAttribute;

  void                 (*NWK_GetConf)(NWK_GetConf_t *conf);
  NWK_GetConf_t        confirm;
} NWK_GetReq_t;

/* --- */

typedef struct _NWK_JoinConf_t
{
  uint8_t       status;
  uint16_t      networkAddress;
  uint64_t      extendedPANId;
  uint8_t       activeChannel;
} NWK_JoinConf_t;

typedef struct _NWK_JoinInd_t
{
  uint16_t              networkAddress;
  uint64_t              extendedAddress;
  MAC_CapabilityInf_t   capabilityInformation;
  NWK_RejoinNetwork_t   rejoinNetwork;
  bool                  secureJoin;
  bool                  isRejoin;
} NWK_JoinInd_t;

typedef struct _NWK_JoinReq_t
{
  struct
  {
    void                *next;
  }  service;
  uint64_t              extendedPANId;
  NWK_RejoinNetwork_t   rejoinNetwork;
  uint32_t              scanChannels;
  uint8_t               scanDuration;
  uint8_t               capabilityInformation;
  bool                  securityEnable;

  void                  (*NWK_JoinConf)(NWK_JoinConf_t *conf);
  NWK_JoinConf_t        confirm;
} NWK_JoinReq_t;

/* --- */

typedef struct _NWK_LeaveConf_t
{
  uint8_t       status;
} NWK_LeaveConf_t;

typedef struct _NWK_LeaveInd_t
{
  uint64_t      deviceAddress;
  bool          rejoin;
} NWK_LeaveInd_t;


typedef struct _NWK_LeaveReq_t
{
  struct
  {
    void        *next;
  }  service;
  uint64_t      deviceAddress;
  bool          removeChildren;
  bool          rejoin;

  void (*NWK_LeaveConf)(NWK_LeaveConf_t *conf);
  NWK_LeaveConf_t confirm;
} NWK_LeaveReq_t;

/* --- */

typedef struct _NWK_NetworkDiscoveryConf_t
{
  uint8_t                       status;
  uint8_t                       networkCount;
  NWK_NetworkDescriptor_t       *networkDescriptors;
} NWK_NetworkDiscoveryConf_t;

typedef struct _NWK_NetworkDiscoveryReq_t
{
  struct
  {
    void        *next;
  } service;
  uint8_t       scanDuration;
  uint32_t      scanChannels;
  void (*NWK_NetworkDiscoveryConf)(NWK_NetworkDiscoveryConf_t *conf);
  NWK_NetworkDiscoveryConf_t confirm;
} NWK_NetworkDiscoveryReq_t;

/* --- */

typedef struct _NWK_NetworkFormationConf_t
{
  uint8_t status;
} NWK_NetworkFormationConf_t;


typedef struct _NWK_NetworkFormationReq_t
{
  struct
  {
    void                      *next;
  } service;
  uint32_t                    scanChannels;
  uint8_t                     scanDuration;
  uint8_t                     beaconOrder;
  uint8_t                     superFrameOrder;
  bool                        batteryLifeExtention;
  void                        (*NWK_NetworkFormationConf)(NWK_NetworkFormationConf_t *conf);
  NWK_NetworkFormationConf_t  confirm;
} NWK_NetworkFormationReq_t;

/* --- */

typedef struct _NWK_NwkStatusInd_t
{
  ShortAddr_t               shortAddress;
  NWK_StatusIndErrorCodes_t status;
} NWK_NwkStatusInd_t;

/* --- */

typedef struct _NWK_PermitJoiningConf_t
{
  uint8_t status;
} NWK_PermitJoiningConf_t;

typedef struct _NWK_PermitJoiningReq_t
{
  struct
  {
    void     *next;
  } service;
  uint8_t    permitDuration;
  void       (*NWK_PermitJoiningConf)(NWK_PermitJoiningConf_t *conf);
  NWK_PermitJoiningConf_t confirm;
} NWK_PermitJoiningReq_t;

/* --- */

typedef struct _NWK_ResetConf_t
{
  uint8_t status;
} NWK_ResetConf_t;

typedef struct _NWK_ResetReq_t
{
  struct
  {
    void            *next;
  } service;
  bool              commission;
  void              (*NWK_ResetConf)(NWK_ResetConf_t *conf);
  NWK_ResetConf_t   confirm;
} NWK_ResetReq_t;

/* --- */

typedef struct _NWK_RouteDiscoveryConf_t
{
  uint8_t       status;
  uint8_t       networkStatusCode;
} NWK_RouteDiscoveryConf_t;

typedef struct _NWK_RouteDiscoveryReq_t
{
  struct
  {
    void                     *next;
  } service;
  NWK_DstAddrMode_t          dstAddrMode;
  uint16_t                   dstAddr;
  uint8_t                    radius;
  bool                       noRouteCache;
  void                       (*NWK_RouteDiscoveryConf)(NWK_RouteDiscoveryConf_t *conf);
  NWK_RouteDiscoveryConf_t   confirm;
} NWK_RouteDiscoveryReq_t;

/* --- */

typedef struct _NWK_SetConf_t
{
  uint8_t               status;
  NWK_NIBAttribute_t    nibAttribute;
} NWK_SetConf_t;

typedef struct _NWK_SetReq_t
{
  struct
  {
    void *next;
  };
  NWK_NIBAttribute_t    nibAttribute;
  uint8_t               nibAttributeLength;
  void                  *nibAttributeValue;
  void                  (*NWK_SetConf)(NWK_SetConf_t *conf);
  NWK_SetConf_t         confirm;
} NWK_SetReq_t;

/* --- */

typedef struct _NWK_StartBackOffReq_t
{
  uint8_t       backOffTime;
} NWK_StartBackOffReq_t;

/* --- */

typedef struct _NWK_StartRouterConf_t
{
  uint8_t       status;
} NWK_StartRouterConf_t;


typedef struct _NWK_StartRouterReq_t
{
  struct
  {
    void                  *next;
  } service;
  uint8_t                 beaconOrder;
  bool                    batteryLifeExtention;
  uint8_t                 superFrameOrder;
  void                    (*NWK_StartRouterConf)(NWK_StartRouterConf_t *conf);
  NWK_StartRouterConf_t   confirm;
} NWK_StartRouterReq_t;

/* -- */

typedef struct _NWK_SyncConf_t
{
  uint8_t status;
} NWK_SyncConf_t;

typedef struct _NWK_SyncLossInd_t
{
  uint8_t dummy;
} NWK_SyncLossInd_t;

typedef struct _NWK_SyncReq_t
{
  struct 
  {
    void           *next;
  } service;
  uint32_t         track;
  void             (*NWK_SyncConf)(NWK_SyncConf_t *conf);
  NWK_SyncConf_t   confirm;
} NWK_SyncReq_t;

typedef struct _NWK_AddDeviceReq_t
{
  ShortAddr_t shortAddr;
  ExtAddr_t   extAddr;
} NWK_AddDeviceReq_t;

typedef enum
{
  RELATIONSHIP_PARENT                = 0x00,
  RELATIONSHIP_CHILD                 = 0x01,
  RELATIONSHIP_SIBLING               = 0x02,
  RELATIONSHIP_NONE_OF_ABOVE         = 0x03,
  RELATIONSHIP_PREVIOUS_CHILD        = 0x04,
  RELATIONSHIP_UNAUTHENTICATED_CHILD = 0x05,

  RELATIONSHIP_EMPTY,
} Relationship_t;

typedef struct
{

// standart part

  ExtAddr_t             extAddr;          //move it to addrMap, have ability do not remove it
  ShortAddr_t           networkAddr;
  DeviceType_t          deviceType;       //can be 2-bit size
  bool                  rxOnWhenIdle;     //can be 1-bit size
  Relationship_t        relationship;     //can be 3-bit size
  uint8_t               lqi;
  uint8_t               rssi;
  uint8_t               outgoingCost;
  uint8_t               incomingCost;
  uint16_t              lqiSumm;
  uint8_t               lqiCounter;
  ExtPanId_t            extPanId;
  uint8_t               logicalChannel;
  uint8_t               depth;            //can be 4-bit size
  bool                  permitJoining;    //can be 1-bit size
  bool                  potentialParent;  //can be 1-bit size

  bool                  useNetworkKey;
  uint8_t               updateId;

// non-standard
  PanId_t               coordPANId;       
  MAC_AddrMode_t        coordAddrMode;    
  MAC_Addr_t            coordAddr;        
  MAC_CapabilityInf_t   capability;       
  ShortAddr_t           newNetworkAddr;
  uint16_t              age;
} Neib_t;
/******************************************************************************
                   Prototypes section
******************************************************************************/

void NWK_DataReq (NWK_DataReq_t *req);
void NWK_DirectJoinReq (NWK_DirectJoinReq_t *req);
void NWK_EDScanReq (NWK_EDScanReq_t *req);
void NWK_GetReq (NWK_GetReq_t *req);
void NWK_JoinReq (NWK_JoinReq_t *req);
void NWK_LeaveReq (NWK_LeaveReq_t *req);
void NWK_NetworkDiscoveryReq (NWK_NetworkDiscoveryReq_t *req);
void NWK_NetworkFormationReq (NWK_NetworkFormationReq_t *req);
void NWK_PermitJoiningReq (NWK_PermitJoiningReq_t *req);
void NWK_ResetReq (NWK_ResetReq_t *req);
void NWK_RouteDiscoveryReq (NWK_RouteDiscoveryReq_t *req);
void NWK_SetReq (NWK_SetReq_t *req);
void NWK_StartBackOffReq (NWK_StartBackOffReq_t *req);
void NWK_StartRouterReq (NWK_StartRouterReq_t *req);
void NWK_SyncReq(NWK_SyncReq_t *req);
void NWK_AddDeviceReq(NWK_AddDeviceReq_t *req);

void NWK_DataInd(NWK_DataInd_t *ind);
void NWK_JoinInd(NWK_JoinInd_t *ind);
void NWK_LeaveInd(NWK_LeaveInd_t *ind);

Neib_t *NWK_FindNeibByShortAddr(ShortAddr_t shortAddr);
Neib_t *NWK_FindNeibByExtAddr(ExtAddr_t *extAddr);
/******************************************************************************
  find ext by short
******************************************************************************/
ExtAddr_t* NWK_FindExtByShort(ShortAddr_t *addr);

/******************************************************************************
  find short by ext
******************************************************************************/
ShortAddr_t* NWK_FindShortByExt(ExtAddr_t *addr);

#ifdef _SECURITY_

#define NWK_KEY_SIZE                   16
#define NWK_IN_FRAMES_MAX              4
#define NWK_SECURITY_DESCRIPTORS_SIZE  2

typedef struct
{
  uint8_t  *npdu;
  uint8_t  headerLength;
  uint8_t  payloadLength;
} NpduDescriptor_t;

typedef struct
{
  ExtAddr_t senderAddress;  // Extended device address.
  uint32_t  inFrameCounter; // Incoming frames counter.
} NWK_InFrameCounterSet_t;

typedef struct
{
  uint8_t                 keySeqNum;                              // Key sequence number.
  uint32_t                outFrameCounter;                        // Outgoing frame counter.
  NWK_InFrameCounterSet_t inFrameCounterSet[NWK_IN_FRAMES_MAX];   // Maximal number of 
  uint8_t                 key[NWK_KEY_SIZE];                      // cifering key
} NWK_SecMaterialDescriptor_t;

typedef struct
{
  NWK_SecMaterialDescriptor_t descriptors[NWK_SECURITY_DESCRIPTORS_SIZE];
  uint8_t                     size;
} NWK_SecMaterialSet_t;

typedef struct
{
  uint8_t               securityLevel;
  NWK_SecMaterialSet_t  securityMaterialSet;
  uint8_t               activeKeySeqNumber;
  bool                  allFresh;
  bool                  secureAllFrames; 
} NWK_SecurityIB_t;

/******************************************************************************
******************************************************************************/
uint8_t NWK_GetActiveKeySeqNumber(void);

/******************************************************************************
******************************************************************************/
NWK_SecMaterialDescriptor_t* NWK_GetActiveKeyDescriptor(void);

/******************************************************************************
******************************************************************************/
uint32_t* NWK_GetInFrameCounter(NWK_SecMaterialDescriptor_t *keyDescriptor,
                                ExtAddr_t                   *srcExtAddr);

/******************************************************************************
******************************************************************************/
bool NWK_SetInFrameCounter(NWK_SecMaterialDescriptor_t *keyDescriptor,
                           ExtAddr_t                   *srcExtAddr,
                           uint32_t                    *newValue);

/******************************************************************************
******************************************************************************/
bool NWK_SetKey(uint8_t *key, uint8_t keySeqNumber);

/******************************************************************************
******************************************************************************/
bool NWK_SwitchKey(uint8_t keySeqNumber);

/******************************************************************************
******************************************************************************/
uint32_t* NWK_GetInFrameActiveKeyDescriptorCounter(ExtAddr_t *srcExtAddr);

/******************************************************************************
******************************************************************************/
bool NWK_SetInFrameActiveKeyDescriptorCounter(ExtAddr_t *srcExtAddr,
                                              uint32_t  *newValue);

#endif

void NWK_NeibTableDeleteNeib(Neib_t* child);

bool NWK_IsActiveTransaction(void);

ShortAddr_t NWK_GetNextHop(ShortAddr_t dstAddr);

//\cond internal
//NWK_Init shall be called only by APS and only once at startup
void NWK_Init();
//\endcond

#endif   // _NWK_H

//eof
