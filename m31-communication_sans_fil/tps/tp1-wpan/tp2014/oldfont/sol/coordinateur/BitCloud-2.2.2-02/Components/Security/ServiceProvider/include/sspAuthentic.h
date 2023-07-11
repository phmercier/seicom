/**************************************************************************//**
  \file
    sspAuthentic.h
  \brief
    Mutual Symmetric-Key Entity Authentication routine header file.
  \internal
    Copyright (c)Meshnetics.
    History:     
      29/11/07 ALuzhetsky - Created.
******************************************************************************/
#ifndef _SSPAUTHENTIC_H
#define _SSPAUTHENTIC_H

#ifdef _HIGH_SECURITY_
/******************************************************************************
                        Includes section.
******************************************************************************/
#include "types.h"
#include "sspCommon.h"
#include "sspChallengeGen.h"

/******************************************************************************
                        Definitions section.
******************************************************************************/
#define HASH_SIZE 16

/******************************************************************************
                        Types' definition section.
******************************************************************************/

/**************************************************************************//**
  \brief Declaration of CalculateAuthenticParamsConf primitive parameters structure.
******************************************************************************/
typedef struct PACK
{
  //! Calculated MacTag1.
  uint8_t macTag1[HASH_SIZE];
  //! Calculated MacTag2.
  uint8_t macTag2[HASH_SIZE];
} SSP_CalculateAuthenticParamsConf_t;

/**************************************************************************//**
  \brief Declaration of CalculateAuthenticParamsConf primitive parameters structure.
******************************************************************************/
typedef struct PACK
{
  //! Service field - for internal needs.
  SSP_Service_t service;
  //! Extended address of the device which initiated authnetication procedure.
  uint64_t *initiatorIEEEAddr;
  //! Extended address of the device which should response.
  uint64_t *responderIEEEAddr; 
  //! Initiator device frame counter.
  uint32_t *initiatorFrameCounter;
  //! Responder device frame counter.
  uint32_t *responderFrameCounter;
  //! Preset key which should be known by both devices (initiator and responder).
  uint8_t (*networkKey)[SECURITY_KEY_SIZE];   
  //! Initiator challenge sequence (just 128-bit random number).
  uint8_t qeu[CHALLENGE_SEQUENCE_SIZE];
  //! Responder challenge sequence (just 128-bit random number).
  uint8_t qev[CHALLENGE_SEQUENCE_SIZE];
  //! Security Service Provider CalculateAuthenticParams confirm callback function's pointer.
  void (*SSP_CalculateAuthenticParamsConf)(SSP_CalculateAuthenticParamsConf_t *conf);
  //! Security Service Provider CalculateAuthenticParams confirm parameters' structure.
  SSP_CalculateAuthenticParamsConf_t confirm;
} SSP_CalculateAuthenticParamsReq_t;

/******************************************************************************
                        Prototypes section.
******************************************************************************/
/*******************************************************************************
  Performs calculation of the parameters for Mutual Symmetric-Key Entity 
  Authentication procedure (MatTag1).
  Parameters:
    param - procedure parameters (for detailed description look at 
             SSP_CalculateAuthenticParamsReq_t declaration).
  Return:
    none.
********************************************************************************/
void SSP_CalculateAuthenticMacTag1Req(SSP_CalculateAuthenticParamsReq_t *param);

/*******************************************************************************
  Performs calculation of the parameters for Mutual Symmetric-Key Entity 
  Authentication procedure (MatTag2).
  Parameters:
    param - procedure parameters (for detailed description look at 
             SSP_CalculateAuthenticParamsReq_t declaration).
  Return:
    none.
********************************************************************************/
void SSP_CalculateAuthenticMacTag2Req(SSP_CalculateAuthenticParamsReq_t *param);

#endif // _HIGH_SECURITY_

#endif //_SSPAUTHENTIC_H

// eof sspAuthentic.h

