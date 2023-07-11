/*************************************************************************//** 
  \file configServer.h

  \brief The header file describes the public ConfigServer interface

  The file describes the public interface and parameters of Config Server.
  It is intended for reading/writing the stack parameters.
  To keep the default values unchanged, the user is recommended to redefine needed values
  in the application's Makefiles or via the environment variables.

  \internal
  Copyright (c)Meshnetics.
        
  History:
    04/07/07 A. Potashov - Created
*****************************************************************************/

#ifndef _CONFIGSERVER_H
#define _CONFIGSERVER_H

#include <types.h>

/*****************************************************************************
  Defines
*****************************************************************************/
// \cond internal
#ifdef _MAC2_

//BOOST mode is enabled automatically only for 11, 10, 9, 8, 7, 6 dBm(s) all other power valuses do not use BOOST mode.
#ifndef CS_RF_TX_POWER
/* It was TX_PWR_3_0DBM. */
#define CS_RF_TX_POWER                        3
#endif

// by default in MAC = 7680L
#ifndef CS_MAC_TRANSACTION_TIME               
#define CS_MAC_TRANSACTION_TIME               7680L
#endif

//! \brief Determines the device UID.
/*! Should be unique for each device in a network.
If set to 0, the stack will use the value from the UID chip (if present).*/
#ifndef CS_UID
#define CS_UID                                0x0000000000000000LL
#endif

#ifndef CS_MAX_FRAME_TRANSMISSION_TIME
#define CS_MAX_FRAME_TRANSMISSION_TIME         5
#endif

#ifndef CS_MAC_FRAME_RX_BUFFER_SIZE
#define CS_MAC_FRAME_RX_BUFFER_SIZE            1
#endif

#else  //_MAC2_
// \endcond
// \cond internal
//! \brief Protocol version identifier. Could not be changed by user.
#ifndef CS_PROTOCOL_VERSION
#define CS_PROTOCOL_VERSION                   0x02
#endif
//! \brief Stack profile identifier (Zigbee PRO profile is equal to 2). Could not be changed by user.
#ifndef CS_STACK_PROFILE
#define CS_STACK_PROFILE                      0x02
#endif
// \endcond
//! \brief Type of device
/*! May be chosen from: \n
0 = DEVICE_TYPE_COORDINATOR \n
1 = DEVICE_TYPE_ROUTER \n
2 = DEVICE_TYPE_ENDDEVICE*/
#ifndef CS_DEVICE_TYPE
#define CS_DEVICE_TYPE                        DEVICE_TYPE_ROUTER
#endif
//! \brief The size of neighbour table
/*! Upper-bounds the maximum possible amount of child devices.
Determines the maximum possible amount of beacons to be saved.
The parameter should exceed CS_MAX_CHILDREN_AMOUNT at least by 1*/
#ifndef CS_NEIB_TABLE_SIZE
#define CS_NEIB_TABLE_SIZE                    4
#endif
//! \brief Maximum number of children that a given device (coordinator or router) may have
#ifndef CS_MAX_CHILDREN_AMOUNT
#define CS_MAX_CHILDREN_AMOUNT                4
#endif
//! \brief Maximum number of routers among the children of one device
/*! The maximum number of end devices is equal to CS_MAX_CHILDREN_AMOUNT - CS_MAX_CHILDREN_ROUTER_AMOUNT */
#ifndef CS_MAX_CHILDREN_ROUTER_AMOUNT
#define CS_MAX_CHILDREN_ROUTER_AMOUNT         1
#endif
//! \brief Maximum depth of a network
/*! The maximum number of hops that a packet may travel is equal to 2*CS_MAX_NETWORK_DEPTH */
#ifndef CS_MAX_NETWORK_DEPTH
#define CS_MAX_NETWORK_DEPTH                  5
#endif
// \cond internal
//! \brief The method of address assignment.
/*!  In the current version is limited to 2.*/
#ifndef CS_ADDRESS_ASSIGNMENT_METHOD
#define CS_ADDRESS_ASSIGNMENT_METHOD          2
#endif
// \endcond
//! \brief Determines whether the auto network start is on.
/*! CS_AUTONETWORK = true means that the stack will join the network automatically
on start or after connection loss. \n
CS_AUTONETWORK = false implies that the user's application have to join the network
by itself. */
#ifndef CS_AUTONETWORK
#define CS_AUTONETWORK                        false
#endif

#ifdef AT86RF212
/* Channel number range
  Page 0 (BPSK modulation is used and supported IEEE 802.15.4 2003/2006 )
    channel  0: 868 MHz      | 20 Kbit/sec
    channels 1 - 10: 915 MHz | 40 Kbit/sec
  Page 2 (O-QPSK modulation is used and supported IEEE 802.15.4 2006)
    channel  0: 868 MHz      | 100 Kbit/sec
    channels 1 - 10: 915 MHz | 250 Kbit/sec
    
  BOOST mode is enabled automatically only for 11, 10, 9, 8, 7, 6 dBm. All other power values do not use BOOST mode.
*/
//! \brief Channel mask to be used by the application.
/*! Determines the channel(s) on which the device may operate*/
  #ifndef CS_CHANNEL_MASK
    #define CS_CHANNEL_MASK                       0x00000002L
  #endif
//! \brief Number of channel page to be used.
/*! 0 means BPSK modulation, 1 means O-QPSK */
  #ifndef CS_CHANNEL_PAGE
    #define CS_CHANNEL_PAGE                       0
  #endif
#else // AT86RF230/230B/231
//! \brief Channel mask to be used by the application.
/*! Determines the channel(s) on which the device may operate*/
  #ifndef CS_CHANNEL_MASK
    #define CS_CHANNEL_MASK                       0x00010000L
  #endif
//! \brief Number of channel page to be used. Ignored in the case of AT86RF230/230B/231 RF chip.
  #ifndef CS_CHANNEL_PAGE
    #define CS_CHANNEL_PAGE                       0
  #endif
#endif

//! \brief Determines the device UID.
/*! Should be unique for each device in a network.
If set to 0, the stack will use the value from the UID chip (if present).*/
#ifndef CS_UID
#define CS_UID                                0x0000000000000000LL
#endif
//! \brief Extended PAN ID of the network to which the device should join.
/*! For a coordinator, this is an extended PAN ID of a network to be started.*/
#ifndef CS_EXT_PANID
#define CS_EXT_PANID                          CS_UID                     
#endif
//! \brief Extended PAN ID used in commissioning feature.
/*! Determines the extended PAN ID of a network where a device may start without having to join.*/
#ifndef CS_NWK_EXT_PANID
#define CS_NWK_EXT_PANID                      0LL
#endif
//! \brief Determines whether or not the static addressing mode will be used.
/*! If set to true, the CS_NWK_ADDR will be used as the device's short address\n
Otherwise, the stochastic addressing mode will be employed.*/
#ifndef CS_NWK_UNIQUE_ADDR
#define CS_NWK_UNIQUE_ADDR                          false
#endif
//! \brief Device's short address if CS_NWK_UNIQUE_ADDR=true, otherwise neglected.
#ifndef CS_NWK_ADDR
#define CS_NWK_ADDR                       0xFFFF
#endif 
//! \brief End Device Active period.
/*! If 0, an Application should put the stack asleep.
Otherwise, the stack falls asleep by itself, informing an application.
In this case the period should be defined in the Application's Makefile*/
#ifndef CS_END_DEVICE_ACTIVE_PERIOD
#define CS_END_DEVICE_ACTIVE_PERIOD           0L
#endif
//! \brief End Device sleep period.
/*! It is used by a parent for tracking that an End Device lives.
For an End Device, this parameter sets its own sleep period.
For router, it should be maximum over all sleep periods in a network*/
#ifndef CS_END_DEVICE_SLEEP_PERIOD
#define CS_END_DEVICE_SLEEP_PERIOD            10000L
#endif

//! \brief Encryption time of maximum-size packet in ms. Decryption time is equal to encryption time.
#ifndef CS_ENCRYPTION_TIME
#if defined(_SECURITY_)
  #ifdef _MAC_HW_AES_
    #define CS_ENCRYPTION_TIME 18     // HW encryption
  #else
    #define CS_ENCRYPTION_TIME 119    // SW encryption
  #endif
#else
  #define CS_ENCRYPTION_TIME 0ul
#endif
#endif

#ifdef AT86RF212
/* 20 Kbit/s    - 53.2 ms
 * 40 Kbit/sec  - 26.6 ms
 * 100 Kbit/sec - 10.64 ms
 * 250 Kbit/sec - 4.256 ms
*/
//! \brief Duration of the maximum-size packet transmission.
#define CS_MAX_AIR_SPEED 54 
#else
//! \brief Duration of the maximum-size packet transmission.
#define CS_MAX_AIR_SPEED 5
#endif

//! \brief Duration of internal processing of the maximum-size packet (without encryption)
#define CS_PACKET_PROCESS_INSIDE 7

//! \brief APS acknowledgement timeout.
#ifndef CS_ACK_TIMEOUT
#define CS_ACK_TIMEOUT  (3ul * CS_MAX_NETWORK_DEPTH * (CS_MAX_AIR_SPEED + CS_PACKET_PROCESS_INSIDE + (CS_ENCRYPTION_TIME * 2)))
#endif 

//! \brief Time of polling own parent by end device.
/*! The parameter should be at least 2 times less than CS_ACK_TIMEOUT*/
#ifndef CS_INDIRECT_POLL_RATE
#define CS_INDIRECT_POLL_RATE                 (CS_ACK_TIMEOUT >> 1)
#endif
//BOOST mode is enabled automatically only for 11, 10, 9, 8, 7, 6 dBm(s) all other power valuses do not use BOOST mode.
#ifndef CS_RF_TX_POWER
/* It was TX_PWR_3_0DBM. */
#define CS_RF_TX_POWER                        3
#endif
#ifndef CS_SCAN_DURATION
#define CS_SCAN_DURATION                      0x05
#endif
/*! \brief The Permit duration parameter directly affect the asscociation permit on 
 MAC layer. 0xff means "always on", 0x00 means "always off" */
#ifndef CS_PERMIT_DURATION
#define CS_PERMIT_DURATION                    0xff
#endif
#ifndef CS_SOFT_RESET_REASON
#define CS_SOFT_RESET_REASON                  0
#endif
//! \brief Determines the value of nwkUseMulticast attribute in NIB.
/*! Enables or disables the multicast transmission mode on NWK layer. Recommended to be set to false.*/
#ifndef CS_NWK_USE_MULTICAST
#define CS_NWK_USE_MULTICAST                  false
#endif
// \cond
// by default in MAC = 7680L
#ifndef CS_MAC_TRANSACTION_TIME               
#define CS_MAC_TRANSACTION_TIME               (CS_END_DEVICE_SLEEP_PERIOD + (CS_INDIRECT_POLL_RATE * 3))
#endif
// \endcond
//! \brief Size of the APS Duplicate Rejection Table. According to ZigBee standard, should be not less than 1.
#ifndef CS_DUPLICATE_REJECTION_TABLE_SIZE
#define CS_DUPLICATE_REJECTION_TABLE_SIZE     5
#endif  
//! \brief Maximum amount of end points in one record in the APS Group Table.
#ifndef CS_APS_GROUP_TABLE_ENDPOINTS_AMOUNT    
#define CS_APS_GROUP_TABLE_ENDPOINTS_AMOUNT   1
#endif
//! \brief Maximum amount of groups in the APS Group Table.
#ifndef CS_APS_GROUP_TABLE_GROUPS_AMOUNT    
#define CS_APS_GROUP_TABLE_GROUPS_AMOUNT      1
#endif
//! \brief Maximum amount of records in the NWK Route Table.
#ifndef CS_ROUTE_TABLE_SIZE                   
#define CS_ROUTE_TABLE_SIZE                   5
#endif
//! \brief Maximum amount of records in the NWK Address Map Table.
#ifndef CS_ADDRESS_MAP_TABLE_SIZE                   
#define CS_ADDRESS_MAP_TABLE_SIZE             5
#endif
//! \brief Maximum amount of records in the NWK Route Discovery Table.
#ifndef CS_ROUTE_DISCOVERY_TABLE_SIZE                   
#define CS_ROUTE_DISCOVERY_TABLE_SIZE         3
#endif
// \cond internal
#ifndef CS_NWK_DATA_REQ_BUFFER_SIZE
#define CS_NWK_DATA_REQ_BUFFER_SIZE           2
#endif
// Minimum value is 3
#ifndef CS_NWK_DATA_IND_BUFFER_SIZE
#ifdef _SECURITY_
#define CS_NWK_DATA_IND_BUFFER_SIZE           4
#else
#define CS_NWK_DATA_IND_BUFFER_SIZE           3
#endif // _SECURITY_
#endif // CS_NWK_DATA_IND_BUFFER_SIZE
#ifndef CS_APS_DATA_REQ_BUFFER_SIZE
#define CS_APS_DATA_REQ_BUFFER_SIZE           2
#endif
#ifndef CS_APS_ACK_FRAME_BUFFER_SIZE
#define CS_APS_ACK_FRAME_BUFFER_SIZE          2
#endif
#ifndef CS_MAC_FRAME_RX_BUFFER_SIZE
#define CS_MAC_FRAME_RX_BUFFER_SIZE           1
#endif
#ifndef CS_APS_GROUP_TABLE_SIZEOF
#define CS_APS_GROUP_TABLE_SIZEOF             (CS_APS_GROUP_TABLE_GROUPS_AMOUNT * \
                                              (sizeof(APS_GroupTableEntry_t) +    \
                                              ((CS_APS_GROUP_TABLE_ENDPOINTS_AMOUNT - 1) * sizeof(Endpoint_t))))
#endif
#ifndef CS_DTR_WAKEUP
#define CS_DTR_WAKEUP                         false
#endif 

#ifndef CS_MAX_FRAME_TRANSMISSION_TIME
#define CS_MAX_FRAME_TRANSMISSION_TIME         5
#endif
// \endcond

/*****************************************************************************
  Security related defines
*****************************************************************************/
// \cond internal
#ifdef _SECURITY_  
//Amount of Aps Security Manager buffers
/*Should be no less than 2*/
#ifndef CS_APS_SECURITY_BUFFERS_AMOUNT
#define CS_APS_SECURITY_BUFFERS_AMOUNT			1
#endif
#ifndef CS_APS_SECURITY_TIMEOUT_PERIOD
#define CS_APS_SECURITY_TIMEOUT_PERIOD        CS_ACK_TIMEOUT
#endif
// \endcond
//! \brief Default address of the Trust Center.
#ifndef CS_APS_TRUST_CENTER_ADDRESS
#define CS_APS_TRUST_CENTER_ADDRESS           0xAAAAAAAAAAAAAAAALL
#endif
//! \brief ZDO security status.
/*! May be chosen among: \n
0 - preconfigured network key \n
3 - not preconfigured. */
#ifndef CS_ZDO_SECURITY_STATUS
#define CS_ZDO_SECURITY_STATUS                PRECONFIGURED_NETWORK_KEY
#endif
//! \brief Default value of the network key.
#ifndef CS_NETWORK_KEY
#define CS_NETWORK_KEY                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
#endif
// \cond internal
// Default security level.
#ifndef CS_SECURITY_LEVEL
#define CS_SECURITY_LEVEL             0x05
#endif
// Default nwkSecureAllFrames attribute value in NIB.
#ifndef CS_SECURITY_ALL_FRAMES
#define CS_SECURITY_ALL_FRAMES        true
#endif
#ifndef CS_MAX_TC_AUTHENTIC_PROCESS_AMOUNT     
#define CS_MAX_TC_AUTHENTIC_PROCESS_AMOUNT     1
#endif
// \endcond
#ifdef _TC_PERMISSION_TABLE_
//! \brief For a Trust Center, maximum amount of records in the Permission Table.
  #ifndef CS_MAX_TC_ALLOWED_DEVICES_AMOUNT
  #define CS_MAX_TC_ALLOWED_DEVICES_AMOUNT    5
  #endif
#endif
// \cond internal
#ifdef _HIGH_SECURITY_
//Maximum amount of Key-Pair Descriptors
#ifndef CS_APS_KEY_PAIR_DESCRIPTORS_AMOUNT
#define CS_APS_KEY_PAIR_DESCRIPTORS_AMOUNT  2
#endif
#ifndef CS_MASTER_KEY
#define CS_MASTER_KEY                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
#endif
#ifndef CS_LINK_KEY
#define CS_LINK_KEY                   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
#endif
#ifndef CS_MAX_TC_ESTABLISH_KEY_AMOUNT
#define CS_MAX_TC_ESTABLISH_KEY_AMOUNT      1
#endif
#endif
// \endcond

#endif

// \cond internal
#endif  //_MAC2_
// \endcond

/*!
\brief IDs of the parameters in Config Server
*/
typedef enum
{
#ifndef _MAC2_
  CS_NEIB_TABLE_SIZE_ID,
  CS_MAX_CHILDREN_AMOUNT_ID,
  CS_MAX_CHILDREN_ROUTER_AMOUNT_ID,
  CS_MAX_NETWORK_DEPTH_ID,
  CS_ADDRESS_ASSIGNMENT_METHOD_ID,
  CS_NWK_DATA_REQ_BUFFER_SIZE_ID,
  CS_NWK_DATA_IND_BUFFER_SIZE_ID,
  CS_APS_DATA_REQ_BUFFER_SIZE_ID,
  CS_APS_ACK_FRAME_BUFFER_SIZE_ID,
  CS_PROTOCOL_VERSION_ID,
  CS_STACK_PROFILE_ID,
  CS_SCAN_DURATION_ID,
  CS_PERMIT_DURATION_ID,
  CS_NWK_EXT_PANID_ID,      // eeprom
  CS_EXT_PANID_ID,          // eeprom
  CS_NWK_ADDR_ID,           // eeprom
  CS_NWK_UNIQUE_ADDR_ID,    // bool // eeprom
  CS_CHANNEL_MASK_ID,       // eeprom
  CS_CHANNEL_PAGE_ID,       // eeprom
#endif  // _MAC2_
  CS_UID_ID,                // eeprom
#ifndef _MAC2_
  CS_INDIRECT_POLL_RATE_ID,
  CS_AUTONETWORK_ID,        // eeprom 
  CS_DEVICE_TYPE_ID,        // eeprom   
  CS_DUPLICATE_REJECTION_TABLE_SIZE_ID,
  CS_ACK_TIMEOUT_ID,
#endif  // _MAC2_
  CS_MAC_FRAME_RX_BUFFER_SIZE_ID,
#ifndef _MAC2_
  CS_APS_GROUP_TABLE_ENDPOINTS_AMOUNT_ID,
  CS_APS_GROUP_TABLE_GROUPS_AMOUNT_ID,
  CS_END_DEVICE_ACTIVE_PERIOD_ID,
  CS_END_DEVICE_SLEEP_PERIOD_ID,
  CS_RX_ON_WHEN_IDLE_ID,            // eeprom
#endif  // _MAC2_
  CS_RF_TX_POWER_ID,                // eeprom
#ifndef _MAC2_
  CS_SOFT_RESET_REASON_ID,          // eeprom 
  CS_NWK_USE_MULTICAST_ID,
  CS_ROUTE_TABLE_SIZE_ID,
  CS_ADDRESS_MAP_TABLE_SIZE_ID,
  CS_ROUTE_DISCOVERY_TABLE_SIZE_ID,
#endif  // _MAC2_
  CS_MAC_TRANSACTION_TIME_ID,  
#ifndef _MAC2_
  CS_DTR_WAKEUP_ID,                 // eeprom  
  CS_NWK_LOGICAL_CHANNEL_ID,        // eeprom
  CS_NWK_PANID_ID,                  // eeprom
#endif  // _MAC2_
  CS_MAX_FRAME_TRANSMISSION_TIME_ID,
#ifndef _MAC2_

/***************************************************************************
    Security related ID's
***************************************************************************/
#ifdef _SECURITY_
  CS_NETWORK_KEY_ID,                    // eeprom
  CS_SECURITY_LEVEL_ID,
  CS_SECURITY_ALL_FRAMES_ID,
  CS_APS_SECURITY_BUFFERS_AMOUNT_ID,
  CS_APS_SECURITY_TIMEOUT_PERIOD_ID,
  CS_APS_TRUST_CENTER_ADDRESS_ID,
  CS_ZDO_SECURITY_STATUS_ID,            // eeprom
  CS_MAX_TC_AUTHENTIC_PROCESS_AMOUNT_ID,
#ifdef _TC_PERMISSION_TABLE_
  CS_MAX_TC_ALLOWED_DEVICES_AMOUNT_ID,
#endif
#ifdef _HIGH_SECURITY_
  CS_APS_KEY_PAIR_DESCRIPTORS_AMOUNT_ID,
  CS_LINK_KEY_ID,                       // eeprom
  CS_MASTER_KEY_ID,                     // eeprom  
  CS_MAX_TC_ESTABLISH_KEY_AMOUNT_ID,
#endif
#endif
#endif // _MAC2_
} CS_ParameterId_t;

// \cond internal
/*!
\brief IDs of the memory area in Config Server
*/
typedef enum
{
#ifndef _MAC2_
  CS_NEIB_TABLE_ID,                   // eeprom
  CS_NWK_DATA_REQ_BUFFER_ID,
  CS_NWK_DATA_IND_BUFFER_ID,
  CS_APS_DATA_REQ_BUFFER_ID,
  CS_APS_ACK_FRAME_BUFFER_ID,
  CS_ASSOCIATE_RESPONSE_BUFFER_ID,
  CS_NWK_PAN_DESCRIPTOR_BUFFER_ID,
  CS_MAC_PAN_DESCRIPTOR_BUFFER_ID,
  CS_DUPLICATE_REJECTION_TABLE_ID,
#endif  // _MAC2_
  CS_MAC_FRAME_RX_BUFFER_ID,
#ifndef _MAC2_
  CS_APS_GROUP_TABLE_ID,            // eeprom
  CS_ROUTE_TABLE_ID,               // eeprom  
  CS_ADDRESS_MAP_TABLE_ID,         // eeprom
  CS_ROUTE_DISCOVERY_TABLE_ID,

  /***********************************************************************************
  Security related ID's
  *************************************************************************************/
#if defined(_SECURITY_)
  CS_NWK_SECURITY_IB_ID,             // eeprom
  CS_APS_SECURITY_BUFFERS_ID,
  CS_TC_AUTHENTIC_PROCESS_BUFFER_ID,
#ifdef _TC_PERMISSION_TABLE_
  CS_TC_PERMISSION_TABLE_ID,
#endif
#ifdef _HIGH_SECURITY_
  CS_APS_KEY_PAIR_DESCRIPTORS_ID,      // eeprom
  CS_TC_ESTABLISH_KEY_BUFFER_ID,
#endif
#endif
#endif // _MAC2_
} CS_MemoryId_t;

// \endcond
/************************************************************************************//*!
\brief Reads a parameter value specified by parameter identifier from Config Server

\param[in] parameterId - ID of the parameter being read
\param[out] parameterValue - Value of the parameter being read
*****************************************************************************/
extern void CS_ReadParameter(CS_ParameterId_t parameterId, void *parameterValue);

/***********************************************************************************//*!
\brief Writes a parameter value specified by parameter identifier to Config Server

If the parameter is in persistense data server it also is saved there.

\param[in] parameterId - ID of the parameter being written
\param[in] parameterValue - Value of the parameter being written
**************************************************************************************/
extern void CS_WriteParameter(CS_ParameterId_t parameterId, void *parameterValue);

// \cond internal
/***********************************************************************************//*!
\brief Inits the Config Server

Config server gets values from defines and reads from persistence data server
***************************************************************************************/
extern void CS_Init(void);

/***********************************************************************************//*!
\brief Gets allocated memory specified by memory identifier

  \param[in] memoryId - memory area Id
  \param[out] memoryPtr - pointer to the memory
***************************************************************************************/
extern void CS_GetMemory(CS_MemoryId_t memoryId, void **memoryPtr);

/**************************************************************************//*!
\brief Set persist default value
*****************************************************************************/
extern void CS_PdsDefaultValue(void);
// \endcond

#endif  //#ifndef _CONFIGSERVER_H

