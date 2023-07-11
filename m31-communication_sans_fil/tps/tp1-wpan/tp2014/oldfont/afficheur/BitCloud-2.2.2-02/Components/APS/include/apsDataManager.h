/*****************************************************************************
  apsDataManager.h 

  Copyright (c)Meshnetics.

  Description:
    APS Data Manager header file.
          
  History:
    06/06/07 A. Potashov - Created.
*****************************************************************************/


#ifndef _APS_DATAMANAGER_H
#define _APS_DATAMANAGER_H

/******************************************************************************
                   Includes section
******************************************************************************/

#include <aps.h>
#include <nwk.h>
#include <appTimer.h>
#include <apsBindManager.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
#define APS_BROADCAST_MAC_RX_ON_SHORT_ADDRESS           0xfffd

//APDU Frame Format

//Frame control field - ApduFrameControlField_t

//Frame Type subfield values
#define APDU_FRAME_CONTROL_FIELD_DATA_FRAME_TYPE                  0x00
#define APDU_FRAME_CONTROL_FIELD_COMMAND_FRAME_TYPE               0x01
#define APDU_FRAME_CONTROL_FIELD_ACK_FRAME_TYPE                   0x02
#define APDU_FRAME_CONTROL_FIELD_RESERVED_FRAME_TYPE              0x03

//Delivery Mode subfield values
#define APDU_FRAME_CONTROL_FIELD_UNICAST_MODE                     0x00
#define APDU_FRAME_CONTROL_FIELD_INDIRECT_MODE                    0x01
#define APDU_FRAME_CONTROL_FIELD_BROADCAST_MODE                   0x02
#define APDU_FRAME_CONTROL_FIELD_GROUP_ADDRESSIND_MODE            0x03

//Ack Format subfiel values
#define APDU_FRAME_CONTROL_FIELD_DATA_ACK_FORMAT                  0x00
#define APDU_FRAME_CONTROL_FIELD_COMMAND_ACK_FORMAT               0x01

//Security subfield values
#define APDU_FRAME_CONTROL_FIELD_NOTSECURED                       0x00
#define APDU_FRAME_CONTROL_FIELD_SECURED                          0x01

//Acknowledgement Request subfield values
#define APDU_FRAME_CONTROL_FIELD_NOACK                            0x00
#define APDU_FRAME_CONTROL_FIELD_ACK                              0x01

//Extended Header Present subfield values                         
#define APDU_FRAME_CONTROL_FIELD_EXTENDED_HEADER_NOT_PRESENT      0x00
#define APDU_FRAME_CONTROL_FIELD_EXTENDED_HEADER_PRESENT          0x01


//Extended Frame Control field - ApduExtendedFrameControlField_t
//Fragmentation subfield values
#define APDU_EXT_FRAME_CONTROL_FIELD_FRAGMENTATION_NOT_FRAGMENTED   0x00
#define APDU_EXT_FRAME_CONTROL_FIELD_FRAGMENTATION_FIRST_FRAGMENT   0x01
#define APDU_EXT_FRAME_CONTROL_FIELD_FRAGMENTATION_FRAGMENT         0x02
#define APDU_EXT_FRAME_CONTROL_FIELD_FRAGMENTATION_RESERVED         0x03


//State field values for ApsDataManagerMemoryPoolEntry_t
#define APS_DEFAULT_STATE                   0x00
#define APS_NLDE_DATA_CONF_WAIT_STATE       0x01
#define APS_ACK_WAIT_STATE                  0x02
#define APS_RETRANSMISSION_STATE            0x03
#define APS_TIMEOUT_STATE                   0x04

/******************************************************************************
                   Types section
******************************************************************************/
typedef enum
{
  NO_MEMORY,
  RESPONSE,
  NO_RESPONSE
} ApsResult_t;

//APDU Frame Format

//Frame control field
BEGIN_PACK
typedef struct PACK
{
  uint8_t frameType               :2;
  uint8_t deliveryMode            :2;
  uint8_t ackFormat               :1;
  uint8_t security                :1;
  uint8_t ackRequest              :1;
  uint8_t extendedHeaderPresent   :1;
} ApduFrameControlField_t;

//Extended Frame Control field
typedef struct PACK
{
  uint8_t fragmentation   :2;
  uint8_t reserved        :6;
} ApduExtendedFrameControlField_t;

typedef struct PACK
{
  ApduExtendedFrameControlField_t extendedFrameControl;
  uint8_t blockNumber;
  uint8_t ackBitfield;
} ApduFragmentedAckExtendedHeaderSubframe_t;

typedef struct PACK
{
  ApduExtendedFrameControlField_t extendedFrameControl;
} ApduNotFragmentedAckExtendedHeaderSubframe_t;

typedef struct PACK
{
  ApduExtendedFrameControlField_t extendedFrameControl;
  uint8_t blockNumber;
} ApduFragmentedDataExtendedHeaderSubframe_t;

typedef struct PACK
{
  ApduExtendedFrameControlField_t extendedFrameControl;
} ApduNotFragmentedDataExtendedHeaderSubframe_t;

typedef struct PACK
{
  ApduFrameControlField_t frameControl;
  uint8_t dstEndpoint;
  uint16_t clusterId;
  uint16_t profileId;
  uint8_t srcEndpoint;
  uint8_t apsCounter;
  union PACK
  {
    ApduNotFragmentedDataExtendedHeaderSubframe_t notFragmentedExtHeaderSubframe;
    ApduFragmentedDataExtendedHeaderSubframe_t fragmentedExtHeaderSubframe;    //Extended header subframe
  };
} ApduDataFrameNongroup_t;

typedef struct PACK
{
  ApduFrameControlField_t frameControl;
  uint16_t groupAddress;
  uint16_t clusterId;
  uint16_t profileId;
  uint8_t srcEndpoint;
  uint8_t apsCounter;
} ApduDataFrameGroup_t;

typedef struct PACK _ApduCommandHeader_t
{
  ApduFrameControlField_t frameControl;
  uint8_t apsCounter;
  uint8_t commandId;
} ApduCommandHeader_t;

typedef struct PACK
{
  ApduFrameControlField_t frameControl;                 //Frame Control field
  uint8_t dstEndpoint;                                  //Destination endpoint
  uint16_t clusterId;                                   //Cluster identifier
  uint16_t profileId;                                   //Profile identifier
  uint8_t srcEndpoint;                                  //Source endpoint
  uint8_t apsCounter;                                   //APS counter
  union PACK
  {
    ApduNotFragmentedAckExtendedHeaderSubframe_t notFragmentedExtHeaderSubframe;
    ApduFragmentedAckExtendedHeaderSubframe_t fragmentedExtHeaderSubframe;    //Extended header subframe
  };
} ApduAcknowledgementFrame_t;

typedef struct PACK
{
  ApduFrameControlField_t frameControl;                 //Frame Control field
  uint8_t apsCounter;                                   //APS counter
} ApduCommandAcknowledgementFrame_t;
END_PACK

typedef struct
{
  struct
  {
    uint8_t busy      :1;
    uint8_t indirect  :1;
    uint8_t index     :6;
  };

BEGIN_PACK
  struct PACK
  {
    uint8_t lowLevelHeader[NWK_NSDU_OFFSET];
    union  PACK
    {
      ApduAcknowledgementFrame_t dataAck;                     //Acknowledgement frame for data
      ApduCommandAcknowledgementFrame_t commandAck;           //Acknowledgement frame for command
    } frame;
    #if (NWK_AFFIX_LENGTH - NWK_NSDU_OFFSET)
      uint8_t lowLevelFooter[NWK_AFFIX_LENGTH - NWK_NSDU_OFFSET];
    #else
      #ifndef __GNUC__
        uint8_t lowLevelFooter[1];
      #else
        uint8_t lowLevelFooter[0];
      #endif
    #endif
  };
END_PACK
} ApsAcknowledgementEntry_t;

typedef struct
{
  uint8_t size;
  ApsAcknowledgementEntry_t *entries;
} ApsAcknowledgementFramePool_t;

typedef enum
{
  APS_NLDE_DATA_REQ_BUFFER_TYPE = 0x00,
  APS_NLDE_DATA_REQ_WITH_ACK_BUFFER_TYPE = 0x01,
  APS_NLDE_DATA_REQ_ACK_BUFFER_TYPE = 0x02,
  APS_FRAGMENTED_TRANSMISSION_DESCRIPTOR_TYPE = 0x03
} ApsNldeDataReqType_t;

typedef struct
{
  uint8_t busy        /*:1*/;     //busy/free - 0 - free; 1 - busy
  uint8_t entryType   /*:2*/;     //00b - NLDE-DATA.request primitive, 01b - NLDE-DATA.request primitive for Acknowledgement,
                                  
  uint8_t state       /*:5*/;     

  uint32_t timeout;               //timeout

  union
  {
    uint8_t retriesCounter;       //if request with ack requested data frame then it is a retries counter
    uint8_t index;                //if request with ack frame then it is a index of entry in APSAcknowledgementFramePool_t
  };                        
  
  void *link;                     //pointer to appropriate object linked with
  NWK_DataReq_t dataReq;          //NLDE-DATA.request primitive
#ifdef _BINDING_
  ApsBindingDescriptor_t bindDescriptor;
#endif
} ApsDataManagerMemoryPoolEntry_t;


typedef struct
{
  uint8_t size;
  uint8_t maxAckCounter;
  uint8_t maxReqCounter;
  uint8_t ackCounter;
  uint8_t reqCounter;
  ApsDataManagerMemoryPoolEntry_t *entries;
} ApsDataManagerMemoryPool_t;


enum
{
  APS_FRAGMENTED_RECEIVE_FREE_STATE =           0x00,
  APS_FRAGMENTED_RECEIVE_BUSY_STATE =           0x01,
  APS_FRAGMENTED_RECEIVE_FAIL_STATE =           0x02,
  APS_FRAGMENTED_RECEIVE_INDICATION_STATE =     0x03
};  

#ifdef _APS_FRAGMENTATION_

#define APS_PERMIT    0x00    // - permitted
#define APS_REJECT    0x01    // - must be rejected
#define APS_INDICATE  0x02    // - must be indicated

typedef struct _ApsFragmentedReceiveDescriptor_t
{
  uint8_t state;
  uint8_t buffers[APS_MAX_BLOCKS_AMOUNT][APS_MAX_ASDU_SIZE];
  uint8_t bufferLengths[APS_MAX_BLOCKS_AMOUNT];
  uint8_t totalLength;
  uint32_t timeout;
  uint8_t blocksAmount;
  uint8_t blocksReceived;
  uint8_t currentWindowStartBlockNumber;
  uint8_t ackBitfield;
  uint16_t srcAddress;
  uint8_t dstEndpoint;
  uint16_t clusterId;
  uint16_t profileId;
  uint8_t srcEndpoint;
  uint8_t apsCounter;

BEGIN_PACK
  struct PACK
  {
    uint8_t lowLevelHeader[NWK_NSDU_OFFSET];
    ApduAcknowledgementFrame_t ackFrame;                     //Acknowledgement frame

    #if (NWK_AFFIX_LENGTH - NWK_NSDU_OFFSET)
      uint8_t lowLevelFooter[NWK_AFFIX_LENGTH - NWK_NSDU_OFFSET];
    #else
      #ifndef __GNUC__
        uint8_t lowLevelFooter[1];
      #else
        uint8_t lowLevelFooter[0];
      #endif
    #endif
  };    
END_PACK
  NWK_DataReq_t nwkDataReq;
} ApsFragmentedReceiveDescriptor_t;

#endif

typedef struct
{
  uint16_t shortAddress;
  uint8_t apsCounter;
  uint32_t timeout;
} ApsDuplicateRejectionTableElement_t;


/******************************************************************************
                   Constants section
******************************************************************************/

/******************************************************************************
                   External variables section
******************************************************************************/

/******************************************************************************
                   Prototypes section
******************************************************************************/

/*****************************************************************************
  Make a reset of APS Data Manager
  Parameters: options - reset options
  Returns:    None
*****************************************************************************/
void apsResetDataManager(uint8_t options);


/*****************************************************************************
  APS Stop Event Handler
  Parameters: options - options field APS_StopReq value
  Returns:    None
******************************************************************************/
void apsStopDataManager(void);

/*****************************************************************************
  APS Start after Stop Event Handler
  Parameters: options - options field APS_StartReq value
  Returns:    None
******************************************************************************/
void apsStartAfterStopDataManager(void);

/*****************************************************************************
  APS Data Manager Process function
  Parameters: None
  Returns: None
*****************************************************************************/
void apsDataManagerProcess(void);

/*****************************************************************************
  APS Data Manager apsCounter get function
  Parameters: None
  Returns: apsCounter value
*****************************************************************************/
extern uint8_t apsGetApsCounter(void);

/*****************************************************************************
  APS Data Manager nsduHandle get function
  Parameters: None
  Returns: nsduHandle value
*****************************************************************************/
extern uint8_t apsGetNsduHandle(void);

/*****************************************************************************
  Routine for IEEE addressing. Extended address by NWK short address 
  mapping function.
  Parameters: shortAddr - NWK short address pointer
  Returns: valid IEEE 64-bit address pointer if success
           NULL in other case
*****************************************************************************/
extern ExtAddr_t *apsFindExtByShort(ShortAddr_t *shortAddr);

/*****************************************************************************
  Routine for IEEE addressing. NWK address by Extended 64-bit address 
  mapping function.
  Parameters: extAddr - extended 64-bit IEEE address pointer
  Returns: valid unicast NWK short address pointer
           NULL in other case
*****************************************************************************/
extern ShortAddr_t *apsFindShortByExt(ExtAddr_t *extAddr);

extern void apsMakeNwkDataResp(NWK_DataInd_t *ind);

extern ExtAddr_t *apsGetOwnExtAddress(void);

extern void apsDmHotReset(void);

/******************************************************************************
                   Inline static functions section 
******************************************************************************/


#endif  //#ifndef _APSDATAMANAGER_H

//eof apsDataManager.h
