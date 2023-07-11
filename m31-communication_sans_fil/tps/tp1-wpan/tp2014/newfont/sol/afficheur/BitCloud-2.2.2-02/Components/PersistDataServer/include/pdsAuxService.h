/***************************************************************************//**
\file pdsAuxService.h

\brief The header file describes the auxiliary service of Persistence Data Server

\internal
  Copyright (c)Meshnetics.

  History:
    22/01/08 A. Khromykh - Created
*****************************************************************************/

#ifndef _PDSAUXSERVICE_H
#define _PDSAUXSERVICE_H

/******************************************************************************
                   Includes section
******************************************************************************/
#ifndef _MAC2_
  #include <aps.h>
  #include <nwk.h>
  #include <nwkRouteTable.h>
  #include <nwkAddrMap.h>
  #include <nwkRouteDiscovery.h>
  #include <apsSecurityManager.h>
#endif // _MAC2_

/******************************************************************************
                   Define(s) section
******************************************************************************/
/* define for eeprom write highlight */
//#define USE_LED

#define SECURITY_KEY_SIZE                              16

#ifndef _MAC2_
  #if defined(_POWER_FAILURE_)
    #if defined(_SECURITY_)
      #ifdef _HIGH_SECURITY_
        // number of parameters
        #define PARAMETER_NUMBER                             25
        // number of config server variable
        #define PARAMETER_NUMBER_CS                          19
        // number of config server memory
        #define MEMORY_NUMBER_CS                             23
        // number of nwk memory
        //#define MEMORY_NUMBER_NWK
      #else
        // number of parameters
        #define PARAMETER_NUMBER                             22
        // number of config server variable
        #define PARAMETER_NUMBER_CS                          17
        // number of config server memory
        #define MEMORY_NUMBER_CS                             20
      #endif
    #else
      // number of parameters
      #define PARAMETER_NUMBER                               19
      // number of config server variable
      #define PARAMETER_NUMBER_CS                            15
      // number of config server memory
      #define MEMORY_NUMBER_CS                               17
      // number of nwk memory
      //#define MEMORY_NUMBER_NWK
    #endif
  #else
    #if defined(_SECURITY_)
      #ifdef _HIGH_SECURITY_
        // number of parameters
        #define PARAMETER_NUMBER                             20
        // number of config server variable
        #define PARAMETER_NUMBER_CS                          16
        // number of config server memory
        #define MEMORY_NUMBER_CS                             18
        // number of nwk memory
        //#define MEMORY_NUMBER_NWK
      #else
        // number of parameters
        #define PARAMETER_NUMBER                             17
        // number of config server variable
        #define PARAMETER_NUMBER_CS                          14
        // number of config server memory
        #define MEMORY_NUMBER_CS                             15
      #endif
    #else
      // number of parameters
      #define PARAMETER_NUMBER                               15
      // number of config server variable
      #define PARAMETER_NUMBER_CS                            12
      // number of config server memory
      #define MEMORY_NUMBER_CS                               13
      // number of nwk memory
      //#define MEMORY_NUMBER_NWK
    #endif
  #endif
#else  // _MAC2_
  // number of parameters
  #define PARAMETER_NUMBER                             2
  // number of config server variable
  #define PARAMETER_NUMBER_CS                          2
  // number of config server memory
  #define MEMORY_NUMBER_CS                             2
  // number of nwk memory
  //#define MEMORY_NUMBER_NWK
#endif // _MAC2_

// offsets table
#define SYSTEM_BASE_EEPROM_ADDRESS    0x0000

#ifndef _MAC2_
  // cs variable list
  #define PDS_UID_OFFSET                 0
  #define PDS_EXT_PANID_OFFSET           (PDS_UID_OFFSET + sizeof(uint64_t))
  #define PDS_CHANNEL_MASK_OFFSET        (PDS_EXT_PANID_OFFSET + sizeof(uint64_t))
  #define PDS_CHANNEL_PAGE_OFFSET        (PDS_CHANNEL_MASK_OFFSET + sizeof(uint32_t))
  #define PDS_DEVICE_TYPE_OFFSET         (PDS_CHANNEL_PAGE_OFFSET + sizeof(uint8_t))
  #define PDS_AUTONETWORK_OFFSET         (PDS_DEVICE_TYPE_OFFSET + sizeof(DeviceType_t))
  #define PDS_RX_ON_WHEN_IDLE_OFFSET     (PDS_AUTONETWORK_OFFSET + sizeof(bool))
  #define PDS_RF_TX_POWER_OFFSET         (PDS_RX_ON_WHEN_IDLE_OFFSET + sizeof(bool))
  #define PDS_SOFT_RESET_REASON_OFFSET   (PDS_RF_TX_POWER_OFFSET + sizeof(int8_t))
  #if defined(_POWER_FAILURE_)
    #define PDS_NWK_EXT_PANID_OFFSET       (PDS_SOFT_RESET_REASON_OFFSET + sizeof(uint8_t))
    #define PDS_NWK_ADDR_OFFSET            (PDS_NWK_EXT_PANID_OFFSET + sizeof(uint64_t))
  #else
    #define PDS_NWK_ADDR_OFFSET            (PDS_SOFT_RESET_REASON_OFFSET + sizeof(uint8_t))
  #endif
  #define PDS_NWK_UNIQUE_ADDR_OFFSET     (PDS_NWK_ADDR_OFFSET + sizeof(ShortAddr_t))
  #define PDS_DTR_WAKEUP_OFFSET          (PDS_NWK_UNIQUE_ADDR_OFFSET + sizeof(bool))
  #if defined(_POWER_FAILURE_)
    #define PDS_NWK_LOGICAL_CHANNEL_OFFSET (PDS_DTR_WAKEUP_OFFSET + sizeof(bool))
    #define PDS_NWK_PANID_OFFSET           (PDS_NWK_LOGICAL_CHANNEL_OFFSET + sizeof(uint8_t))
    #define PDS_AUXILIARY1_OFFSET          (PDS_NWK_PANID_OFFSET + sizeof(uint16_t))
  #else
    #define PDS_AUXILIARY1_OFFSET          (PDS_DTR_WAKEUP_OFFSET + sizeof(bool))
  #endif

  #if defined(_SECURITY_)
    #define PDS_NETWORK_KEY_OFFSET        PDS_AUXILIARY1_OFFSET
    #ifdef _HIGH_SECURITY_
      #define PDS_LINK_KEY_OFFSET            (PDS_NETWORK_KEY_OFFSET + SECURITY_KEY_SIZE)
      #define PDS_MASTER_KEY_OFFSET          (PDS_LINK_KEY_OFFSET + SECURITY_KEY_SIZE)
      #define PDS_ZDO_SECURITY_STATUS_OFFSET (PDS_MASTER_KEY_OFFSET + SECURITY_KEY_SIZE)
    #else
      #define PDS_ZDO_SECURITY_STATUS_OFFSET (PDS_NETWORK_KEY_OFFSET + SECURITY_KEY_SIZE)
    #endif
    #define PDS_MEMORY_OFFSET              (PDS_ZDO_SECURITY_STATUS_OFFSET + sizeof(uint8_t))
  #else
    #define PDS_MEMORY_OFFSET             PDS_AUXILIARY1_OFFSET
  #endif

  // cs memory list
  #if defined(_POWER_FAILURE_)
    #define PDS_NEIB_TABLE_OFFSET                 PDS_MEMORY_OFFSET //CS_NEIB_TABLE_ID
    #if defined(_SECURITY_)
      #define PDS_NWK_SECURITY_IB_OFFSET            (PDS_NEIB_TABLE_OFFSET + CS_NEIB_TABLE_SIZE * sizeof(Neib_t))
      #define PDS_APS_GROUP_TABLE_OFFSET            (PDS_NWK_SECURITY_IB_OFFSET + sizeof(NWK_SecurityIB_t))
    #endif
    #define PDS_APS_GROUP_TABLE_OFFSET            (PDS_NEIB_TABLE_OFFSET + CS_NEIB_TABLE_SIZE * sizeof(Neib_t))
  #else
    #define PDS_APS_GROUP_TABLE_OFFSET            PDS_MEMORY_OFFSET
  #endif
  #define PDS_AUXILIARY2_OFFSET                   (PDS_APS_GROUP_TABLE_OFFSET + CS_APS_GROUP_TABLE_SIZEOF * sizeof(uint8_t))

  #if defined(_SECURITY_)
    #ifdef _HIGH_SECURITY_
      #define PDS_APS_KEY_PAIR_DESCRIPTORS_OFFSET   PDS_AUXILIARY2_OFFSET
      #define PDS_NWK_MEMORY_OFFSET                 (PDS_APS_KEY_PAIR_DESCRIPTORS_OFFSET + CS_APS_KEY_PAIR_DESCRIPTORS_AMOUNT * sizeof(ApsKeyPairDescriptor_t))
    #endif
  #endif

  #define PDS_NWK_MEMORY_OFFSET                 PDS_AUXILIARY2_OFFSET

  // nwk memory list
  #define PDS_PARENT_ADDR_OFFSET                PDS_NWK_MEMORY_OFFSET
  #define PDS_CURRENT_DEPTH_OFFSET              (PDS_PARENT_ADDR_OFFSET + sizeof(uint16_t))

  #define PDS_MAX_DATA_OFFSET                   (PDS_CURRENT_DEPTH_OFFSET + sizeof(uint8_t))

#else  // _MAC2_

  // cs variable list
  #define PDS_UID_OFFSET                 0
  #define PDS_RF_TX_POWER_OFFSET         (PDS_UID_OFFSET + sizeof(uint64_t))
  #define PDS_MAX_DATA_OFFSET            (PDS_RF_TX_POWER_OFFSET + sizeof(int8_t))

#endif // _MAC2_

// crc area
#define PDS_CRC_AREA                  10
// user area
#define USER_BASE_EEPROM_ADDRESS      (PDS_MAX_DATA_OFFSET + PDS_CRC_AREA)

#define PDS_CS_PARAMETER             0
#define PDS_CS_MEMORY                1
#define PDS_NWK_MEMORY               2
#define PDS_STOP_SAVE                3

#define EEPROM_BUSY                  -2
#define EEPROM_ERROR                 -1

#define STORE_TIMER_TIMEOUT  300000ul  // 5 minutes
//#define STORE_TIMER_TIMEOUT  300ul
#define SHORT_TIMEOUT        50ul      // 50 msec
#define PDS_LONG_INTERVAL            0
#define PDS_SHORT_INTERVAL           1
#define SAVE_IS_STARTED              1
#define SAVE_IS_STOPED               0

#define MAX_CS_PDS_VARIABLE_SIZE     16

/******************************************************************************
                   Types section
******************************************************************************/
// crc property
typedef struct
{
  uint8_t crc;
  uint16_t position;
  PDS_DataServerState_t eepromState;
} PDS_ServiceCrc_t;

// crc property
typedef struct
{
  uint8_t id;
  uint8_t currentAction;
} PDS_CurrentState_t;

// memory for default value
typedef union
{
  uint8_t resetCRC[PDS_CRC_AREA];
  uint8_t readBuff[MAX_CS_PDS_VARIABLE_SIZE];
  void *__void;
  uint8_t *pUint8;
  uint8_t uint8;
} PDS_Default_t;

#endif /*_PDSAUXSERVICE_H*/
