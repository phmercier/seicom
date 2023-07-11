/**************************************************************************//**
  \file
    sspSkkeHandler.h
  \brief
    SKKE routine handler header file.
  \internal
    Copyright (c)Meshnetics.
    History:     
      29/11/07 ALuzhetsky - Created.
******************************************************************************/
#ifndef _SSPSKKEHANDLER_H
#define _SSPSKKEHANDLER_H

#ifdef _HIGH_SECURITY_

/******************************************************************************
                        Includes section.
******************************************************************************/
#include "types.h"
#include "sspManager.h"
#include "sspAesHandler.h"

/******************************************************************************
                        Types section.
******************************************************************************/
typedef enum
{
  SKKE_STATE_IDLE,
  SKKE_STATE_CALCULATE_MACTAG1,
  SKKE_STATE_CALCULATE_MACTAG2,
  SKKE_STATE_CALCULATE_FINAL_MACTAG1,
  SKKE_STATE_CALCULATE_HASH1,
  SKKE_STATE_CALCULATE_HASH2,
} SspSkkeState_t;
/******************************************************************************
  TBD
******************************************************************************/
typedef struct PACK
{
  SspSkkeState_t skkeState;
  uint8_t        macKey[SECURITY_KEY_SIZE];
  struct PACK
  {
    uint8_t keyExpander[SECURITY_KEY_SIZE];
    uint8_t macData[MAX_HASH_TEXT_SIZE];
    uint8_t bitsExpander[16];
  };
  union
  {
    SspKeyedHashMacReq_t keyedHashMacParam;
    SspBcbHashReq_t      bcbHashReqParam;
  };
} SspSkkeHandlerMem_t;

/******************************************************************************
                        Prototypes section.
******************************************************************************/
/*******************************************************************************
  Calculates parameters of Security-Key Key Esteblishment procedure.
  Parameters:
    none.
  Return:
    none.
********************************************************************************/
void sspCalculateSkkeParamsReqHandler(void);

/***************************************************************************\\**
  \brief Copies with mirroring "length" bytes from "src" to "dst".
  
  \param
    dst - destination memory.
    src - source memory.
    length - number of bytes to copy.
  \return
    none.
********************************************************************************/
INLINE void mirrorMemcpy(uint8_t *dst, uint8_t *src, uint8_t length)
{
  while(length)
    *(dst++) = *(src + --length);
}

#endif // _HIGH_SECURITY_

#endif //_SSPSKKEHANDLER_H

// eof sspSkkeHandler.h

