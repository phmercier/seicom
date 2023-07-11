/** \file appFramework.h
\brief The header file describes the ZigBee profile elements 

\internal
Copyright (c)Meshnetics.
*******************************************************************/ 

/******************************************************************************
* 		The header file contains ZIGBEE type definitions	     			 */

#ifndef _APPFRAMEWORK_H
#define _APPFRAMEWORK_H

#include <types.h>
#include <macAddr.h>

/********************************************************************************
* Base types
********************************************************************************/
typedef uint8_t  Endpoint_t;
typedef uint16_t ProfileId_t;
typedef uint16_t ClusterId_t;
typedef uint16_t GroupAddr_t;


/********************************************************************************
* Zigbee APFW types definition
********************************************************************************/

// MAC capability flags
typedef struct {
	uint8_t     altPANcoord : 1;
	uint8_t     devType : 1;
	uint8_t		pwrSrc : 1;
	uint8_t     rxOnWhenIdle :1;
	uint8_t		rsvd : 2;
	uint8_t     secCapb : 1;
	uint8_t		allocAddr : 1;
} MacCapabilityFlags_t;

// Node descriptor
typedef struct
{
  //device type: DEVICE_TYPE_COORDINATOR, DEVICE_TYPE_ROUTER, DEVICE_TYPE_END_DEVICE	
  uint8_t   logicalType : 3;
  uint8_t   complexDescriptorAvailable: 1;
  uint8_t   userDescriptorAvailable: 1;
  uint8_t   reserved: 3;
  uint8_t   apsFlags : 3;
  uint8_t   frequencyBand : 5;
  uint8_t 	macCapbFlags;
  uint16_t 	manufacturerCode;
  uint8_t 	maxBufferSize;
  uint16_t 	maxTransferSize;
  uint16_t 	serverMask;
  uint16_t 	maxOutcTransferSize;
  uint8_t 	descriptorCapabilityField;
} NodeDescriptor_t;

typedef enum
{
  DEVICE_TYPE_COORDINATOR = 0x00,
  DEVICE_TYPE_ROUTER      = 0x01,
  DEVICE_TYPE_END_DEVICE  = 0x02
} DeviceType_t;

enum
{
  FREQUENCY_BAND_868 = 0x01,
  FREQUENCY_BAND_902 = 0x04,
  FREQUENCY_BAND_2400 = 0x08,
};

enum
{
  MAC_CAP_ALTERNATE_PAN_COORDINATOR = 0x01,
  MAC_CAP_DEVICE_TYPE_FFD = 0x02,
  MAC_CAP_POWER_SOURCE_MAINS = 0x04,
  MAC_CAP_RX_ON_WHEN_IDLE = 0x08,
  MAC_CAP_SECURITY_CAPABLE = 0x40,
  MAC_CAP_ALLOCATE_ADDRESS = 0x80 // always set for rev13
};

enum
{
  SERVER_MASK_NO_SERVER = 0x0000,
  SERVER_MASK_PRIMARY_TRUST_CENTER = 0x0001,
  SERVER_MASK_BACKUP_TRUST_CENTER = 0x0002,
  SERVER_MASK_PRIMARY_BINDING_TABLE_CACHE = 0x0004,
  SERVER_MASK_BACKUP_BINDING_TABLE_CACHE = 0x0008,
  SERVER_MASK_PRIMARY_DISCOVERY_CACHE = 0x0010,
  SERVER_MASK_BACKUP_DISCOVERY_CACHE = 0x0020,
  SERVER_MASK_NETWORK_MANAGER = 0x0040
};

enum
{
  EXT_LIST_ACTIVE_EP = 0x01,
  EXT_LIST_SIMPLE_DESC = 0x02
};

// Power descriptor
typedef struct
{
  uint8_t currentPowerMode : 4;
  uint8_t availablePowerSources : 4;
  uint8_t currentPowerSource : 4;
  uint8_t currentPowerSourceLevel : 4;
} PowerDescriptor_t;


typedef enum
{
  RECEIVER_SYNCRONIZED_WHEN_ON_IDLE = 0,
  RECEIVER_COMES_PERIODICALLY = 1,
  RECEIVER_COMES_WHEN_STIMULATED = 2
  //RESERVED = 0xF /* all other values */
} PowerMode_t;

typedef enum
{
  MAINS_POWER = 0x1,
  RECHARGEABLE_BATTERY = 0x2,
  DISPOSABLE_BATTERY = 0x4,
  //RESERVED
} PowerSource_t;

typedef enum
{
  CRITICAL_0 = 0,
  PERCENT_33 = 4,
  PERCENT_66 = 8,
  PERCENT_100 = 0xC
  //RESERVED = 0xFF;  /* all over values */
} PowerSourceLevel_t;


// Simple Descriptor
typedef struct
{
  Endpoint_t   endpoint;
  ProfileId_t  AppProfileId;
  uint16_t     AppDeviceId;
  uint8_t      AppDeviceVersion : 4;
  uint8_t      Reserved         : 4;
  uint8_t      AppInClustersCount;
  ClusterId_t* AppInClustersList;
  uint8_t      AppOutClustersCount;
  ClusterId_t* AppOutClustersList;
} SimpleDescriptor_t;

// User descriptor
typedef struct
{
  uint8_t FieldName[16];
} UserDescriptor_t;


// Complex Descriptor
enum
{
  TAG_LANGUAGE_AND_CHARACTER_SET = 0001,
  TAG_MANUFACTURER_NAME = 0010,
  TAG_MODEL_NAME = 0011,
  TAG_SERIAL_NUMBER = 0100,
  TAG_DEVICE_URL = 0101,
  TAG_ICON = 0110,
  TAG_ICON_URL = 0111,
};


typedef struct
{
  uint8_t CompressedXMLTag;
  uint8_t* pDataField;
} ComplexDescriptorField_t;


typedef struct
{
  uint8_t FieldCount;
  ComplexDescriptorField_t* pFields;
} ComplexDescriptor_t;

// Direct Join device descriptor
typedef struct {
	ExtAddr_t addrIEEE;
	uint8_t   macCapbInfo;
	uint8_t   masterKey[16];
}AddressesDirectJoin_t;

#endif  /* _APPFRAMEWORK_H */

