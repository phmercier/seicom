/**************************************************************************//**
  \file
    sspSfp.h
  \brief
    Security Frame Processor header file.
  \internal
    Copyright (c)Meshnetics.
    History:
      2006 - VGribanovsky created.
      29/11/2007 - ALuzhetsky.
******************************************************************************/

#ifndef _SSPSFP_H
#define _SSPSFP_H

/******************************************************************************
                        Includes section.
******************************************************************************/
#include <types.h>
#include <macAddr.h>
#include <sspCommon.h>


/******************************************************************************
                        Definitions section.
******************************************************************************/
#define SSP_MAX_AUXILIARY_HEADER_LENGTH 14

/**************************************************************************//**
  \brief Possible key types.
******************************************************************************/
enum
{
  SSP_DATA_KEY_ID           = 0x00,
  SSP_NETWORK_KEY_ID        = 0x01,
  SSP_KEY_TRANSPORT_KEY_ID  = 0x02,
  SSP_KEY_LOAD_KEY_ID       = 0x03
};

/**************************************************************************//**
  \brief Possible levels of security.
******************************************************************************/
enum
{
  SSP_NONE_SECURITY_LEVEL        = 0x00,
  SSP_MIC_32_SECURITY_LEVEL      = 0x01,
  SSP_MIC_64_SECURITY_LEVEL      = 0x02,
  SSP_MIC_128_SECURITY_LEVEL     = 0x03,
  SSP_ENC_SECURITY_LEVEL         = 0x04,
  SSP_ENC_MIC_32_SECURITY_LEVEL  = 0x05,
  SSP_ENC_MIC_64_SECURITY_LEVEL  = 0x06,
  SSP_ENC_MIC_128_SECURITY_LEVEL = 0x07
};

/******************************************************************************
                        Types' definition section.
******************************************************************************/
/**************************************************************************//**
  \brief Confirm parameters of SSP_EncryptFrame.
******************************************************************************/
typedef struct PACK
{
  //! Status of frame encoding.
  SSP_Status_t status;
} SSP_EncryptFrameConf_t;

typedef struct PACK
{
  //! Status of frame encoding.
  SSP_Status_t status;

  //! Type of the used key.
  uint8_t keyIdentifier;
} SSP_DecryptFrameConf_t;

/**************************************************************************//**
  \brief Declaration of Encrypt Frame primitive's parameters structure.
******************************************************************************/
typedef struct PACK
{
  //! Service field - for internal needs.
  SSP_Service_t service;
  //! The sequence number of active network key in nwkSecurityMaterialSet.
  uint8_t nwkActiveKeySeqNumber;
  //! The actual value of the key.
  uint8_t (*key)[SECURITY_KEY_SIZE];
  //! Identifies the type of the key which is used to protect the frame.
  uint8_t keyIdentifier;
  //! Outgoing frame counter used only for outgoing frames.
  uint32_t *outFrameCounter; 
  //! The security level for outgoing and incoming NWK and APS frames.
  uint8_t nwkSecurityLevel;
  //! Detects whether the extended address is present in the nonce or not.
  uint8_t extendedNonce;
  //! Extended (64-bit) device address responsible for securing of the frame.
  ExtAddr_t *extAddr;
  //! Layer protocol data unit pointer. There is should be allocated memory for auxiliary header before pdu.
  uint8_t  *pdu/*[headerLength + payloadLength]*/;
  //! Length of the header.
  uint8_t  headerLength;
  //! Payload length.
  uint8_t  payloadLength;
  //! Security Service Provider SSP_EncryptFrame confirm parameters' structure.
  SSP_EncryptFrameConf_t confirm;
  //! Encrypt frame confirm callback function.
  void (*SSP_EncryptFrameConf)(SSP_EncryptFrameConf_t *conf);
} SSP_EncryptFrameReq_t;

/**************************************************************************//**
  \brief Declaration of Encrypt Frame primitive's parameters structure.
******************************************************************************/
typedef struct PACK
{
  //! Service field - for internal needs.
  SSP_Service_t service;
  //! The actual value of the key.
  uint8_t (*key)[SECURITY_KEY_SIZE];
  //! The security level for outgoing and incoming NWK and APS frames.
  uint8_t securityLevel;
  //! Extended (64-bit) source device address.
  ExtAddr_t *extAddr;
  //! Layer protocol data unit pointer.
  uint8_t  *pdu;
  //! Length of the header.
  uint8_t  headerLength;
  //! Payload length.
  uint8_t  payloadLength;

  //! Encrypt frame confirm callback function.
  void (*SSP_DecryptFrameConf)(SSP_DecryptFrameConf_t *conf);
  //! Security Service Provider SSP_DecryptFrame confirm parameters' structure.
  SSP_DecryptFrameConf_t confirm;
} SSP_DecryptFrameReq_t;

/**************************************************************************//**
  \brief Declaration of Parse Auxiliary Header primitive's parameters structure.
******************************************************************************/
typedef struct PACK
{
  //! Layer protocol data unit pointer - should be initialized by user.
  uint8_t  *pdu;
  //! Length of the header.
  uint8_t  headerLength;
  //! The sequence number of active network key in nwkSecurityMaterialSet.
  //! This parameter will be initialized during ParseAuxiliaryHeader function executing.
  uint8_t nwkActiveKeySeqNumber;
  //! Received frame counter.
  //! This parameter will be initialized during ParseAuxiliaryHeader function executing.
  uint32_t *receivedFrameCounter; 
  //! Extended (64-bit) source device address.
  //! This parameter will be initialized during ParseAuxiliaryHeader function executing.
  ExtAddr_t *sourceExtAddr;
  //! Identifies the type of the key which is used to protect the frame.
  uint8_t keyIdentifier;
} SSP_ParseAuxiliaryHeader_t;

/******************************************************************************
                        Functions' prototypes section.
******************************************************************************/
/**************************************************************************//**
  Performs frame encrypting based on incoming parameters.
  Parameters:
    param - encrypt frame procedure parameters (for detailed description look at 
             SSP_EncryptFrameReq_t declaration).
  Return:
    none.
******************************************************************************/
void SSP_EncryptFrameReq(SSP_EncryptFrameReq_t *param);

/**************************************************************************//**
  Performs frame decrypting based on incoming parameters.
  Parameters:
    param - decrypt frame procedure parameters (for detailed description look at 
             SSP_DecryptFrameReq_t declaration).
  Return:
    none.
******************************************************************************/
void SSP_DecryptFrameReq(SSP_DecryptFrameReq_t *param);

/**************************************************************************//**
  Extracts parameters from secured frame auxiliary header.
  Parameters:
    param - parse frame procedure parameters (for detailed description look at 
             SSP_ParseAuxiliaryHeader_t declaration).
  Return:
    none.
******************************************************************************/
void SSP_ParseAuxiliaryHeader(SSP_ParseAuxiliaryHeader_t *param);
#endif //_SSPSFP_H

// eof sspSfp.h
