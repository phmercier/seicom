/**************************************************************************//**
  \file
    tcKeyEstablish.h
  \brief
    Security Trust Centre End to End Key Establish primitive header file.
  \internal
    Copyright (c)Meshnetics.
    History:
      2008.01.17 - ALuzhetsky created.
******************************************************************************/
#ifndef _TCKEYESTABLISH
#define _TCKEYESTABLISH

/******************************************************************************
                             Types section.
******************************************************************************/
/**************************************************************************//**
  \brief TBD.

  TBD
******************************************************************************/
typedef struct PACK
{
  union
  {
    APS_TransportKeyReq_t transportKeyReq;
  };
  //ExtAddr_t updateIndSrcAddr;
  uint8_t state;
} TC_KeyEstablishObj_t;

/******************************************************************************
                             Functions prototypes section.
******************************************************************************/
/**************************************************************************//**
  \brief TBD.
  
  \param TBD.
  \return TBD.
******************************************************************************/
#ifdef _HIGH_SECURITY_
void APS_RequestKeyInd(APS_RequestKeyInd_t *indParams);
#endif // _HIGH_SECURITY_

#endif // _HIGH_SECURITY_

// eof tcKeyEstablish.h
