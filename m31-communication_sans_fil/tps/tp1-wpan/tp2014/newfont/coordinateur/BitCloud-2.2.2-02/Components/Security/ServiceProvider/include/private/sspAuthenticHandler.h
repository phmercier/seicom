/**************************************************************************//**
  \file
    sspAuthenticHandler.h
  \brief
    Mutual Symmetric-Key Entity Authentication routine handler's header file.
  \internal
    Copyright (c)Meshnetics.
    History:     
      17/12/07 ALuzhetsky - Created.
******************************************************************************/
#ifndef _SSPAUTHENTICHANDLER_H
#define _SSPAUTHENTICHANDLER_H

#ifdef _HIGH_SECURITY_
/******************************************************************************
                        Includes section.
******************************************************************************/
#include "types.h"
#include "sspManager.h"
#include "sspHashHandler.h"
#include "sspAesHandler.h"

/******************************************************************************
                        Types section.
******************************************************************************/
/******************************************************************************
  TBD
******************************************************************************/
typedef struct PACK
{
  SspKeyedHashMacReq_t keyedHashMacParams;
  struct PACK
  {
    uint8_t keyExpander[SECURITY_KEY_SIZE];
    uint8_t macData[MAX_HASH_TEXT_SIZE];
    uint8_t bitsExpander[16];
  };
} SspAuthenticHandlerMem_t;
/******************************************************************************
                        Prototypes section.
******************************************************************************/
/*******************************************************************************
  Calculates parameters (MacTag1) for Mutual Symmetric-Key Entity Authentication 
  procedure.
  Parameters:
    none.
  Return:
    none.
********************************************************************************/
void sspCalculateAuthenticMacTag1ReqHandler(void);

/*******************************************************************************
  Calculates parameters (MacTag2) for Mutual Symmetric-Key Entity Authentication 
  procedure.
  Parameters:
    none.
  Return:
    none.
********************************************************************************/
void sspCalculateAuthenticMacTag2ReqHandler(void);

#endif // _HIGH_SECURITY_

#endif //_SSPAUTHENTICHANDLER_H

// eof sspAuthenticHandler.h

