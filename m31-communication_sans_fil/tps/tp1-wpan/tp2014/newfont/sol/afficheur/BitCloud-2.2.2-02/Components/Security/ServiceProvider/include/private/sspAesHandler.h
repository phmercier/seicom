/**************************************************************************//**
  \file
    sspAesHandler.h
  \brief
    The header file contains AES128 functions' declarations.
  \internal
    Copyright (c)Meshnetics.
    History:
      2006 - MCherkashin created.
      2006 - VGrybanovsky optimized.
      207.11.29 ALuzhetsky API corrected.
******************************************************************************/
#ifndef _SSPAES_H
#define _SSPAES_H
#include <types.h>
#include <sspCommon.h>
#ifdef _MAC_HW_AES_
  #include <rfEncrypt.h>
  #define AES_ENCRYPT_REQ_T RF_EncryptReq_t
  #define AES_ENCRYPT_REQ   RF_EncryptReq
  #define AES_SET_KEY_REQ_T RF_EncryptReq_t
  #define AES_SET_KEY_REQ   RF_EncryptReq
#else //_MAC_HW_AES_
  #define AES_ENCRYPT_REQ_T SspAesEncryptReq_t
  #define AES_SET_KEY_REQ_T uint8_t
  #define AES_ENCRYPT_REQ   sspAesEncryptReq
#endif // _MAC_HW_AES_

/******************************************************************************
                        Definitions section.
******************************************************************************/
//#define AES_KEY_SIZE        16  // Bytes.
//#define AES_TEXT_BLOCK_SIZE 16  // Bytes.
#define AES_TEMP_BUF_SIZE   176 // Bytes.

/******************************************************************************
                        Prototypes section.
******************************************************************************/
/******************************************************************************
  TBD
******************************************************************************/
typedef struct PACK
{
  uint8_t status;
} SspAesEncryptConf_t;

/******************************************************************************
  TBD
******************************************************************************/
typedef struct PACK
{
  uint8_t (*key)[SECURITY_KEY_SIZE];
  uint8_t (*text)[SECURITY_BLOCK_SIZE];
  uint8_t temp[AES_TEMP_BUF_SIZE];
  void (*sspAesEncryptConf)(void);//(SspAesEncryptConf_t *confirm);
} SspAesEncryptReq_t;

/******************************************************************************
  TBD
******************************************************************************/
typedef struct PACK
{
  union
  {
    AES_SET_KEY_REQ_T  setKeyReq;
    AES_ENCRYPT_REQ_T  encryptReq;
  };
  uint8_t            textBuf[SECURITY_BLOCK_SIZE];
} SspAesMem_t;

/******************************************************************************
                        Prototypes section.
******************************************************************************/
/**************************************************************************//**
  \brief Encrypts a block of text with particular key. Needs temp buffer for 
         the operating.
  \param 
******************************************************************************/
void sspAesEncryptReq(SspAesEncryptReq_t *param);

/**************************************************************************//**
  \brief TBD
         
  \param TBD
  \return TBD
******************************************************************************/
void sspAesReqHandler(void);
#endif // _SSPAES_H
//eof sspAesHandler.h

