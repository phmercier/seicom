/**************************************************************************//**
  \file
    tcAuthentic.h
  \brief
    Security Trust Centre authentic primitive header file.
  \internal
   Copyright (c)Meshnetics.
    History:
      2007.12 - ALuzhetsky created.
******************************************************************************/
#ifndef _TCAUTHENTICH
#define _TCAUTHENTICH

/******************************************************************************
                             Include section.
******************************************************************************/
#include <aps.h>

/******************************************************************************
                             Types section.
******************************************************************************/
/**************************************************************************//**
  \brief Authentic handler memory object.

  This struct declares memory wichshould be reserved for the Trust Centre 
  Authentication proceure.
******************************************************************************/
typedef struct PACK
{
  union
  { //! Memory for APS_TransportKeyReq.
    APS_TransportKeyReq_t transportKey;
#ifdef _TC_PERMISSION_TABLE_
    APS_RemoveDeviceReq_t removeDevice;
#endif // _TC_PERMISSION_TABLE_
#ifdef _HIGH_SECURITY_
    //! Memory for APS_EstablishKeyReq.
    APS_EstablishKeyReq_t establishKey;
#endif // _HIGH_SECURITY_
  } buffer;
  //! Memory to store source address of APS_UpdateDeviceInd command. 
  ExtAddr_t updateIndSrcAddr;
  //! Current state for Trust Centre authentic handler.
  uint8_t state;
} TC_AuthenticObj_t;

#endif // _TCAUTHENTICH

// eof tcAuthentic.h
