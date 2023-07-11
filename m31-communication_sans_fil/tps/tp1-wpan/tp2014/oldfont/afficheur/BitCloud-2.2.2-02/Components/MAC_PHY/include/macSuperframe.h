/**************************************************************************//**
  \file        
    macSuperframe.h
  \brief 
    Superframe types' declarations.
  \internal
    Copyright (c)Meshnetics.
    History:     
      18/06/07 ALuzhetsky - Created.
******************************************************************************/

#ifndef _MACSUPERFRAME_H
#define _MACSUPERFRAME_H

/******************************************************************************
                        Include section.
******************************************************************************/
#include <types.h>
#include <macAddr.h>

/******************************************************************************
                        Types section.
******************************************************************************/
//! MAC GTS characteristics. IEEE 802.15.4-2006 Figure 65.
typedef struct
{
  uint8_t    length : 4;
  uint8_t direction : 1;
  uint8_t      type : 1;
  uint8_t  reserved : 2;
}  MAC_GtsCharacteristics_t;

//! Superframe specification. IEEE 802.15.4-2006 Figure 47.
typedef struct
{
  uint16_t beaconOrder       : 4;
  uint16_t superframeOrder   : 4;
  uint16_t finalCapSlot      : 4;
  uint16_t battLifeExt       : 1;
  uint16_t reserved          : 1;
  uint16_t panCoordinator    : 1;
  uint16_t associationPermit : 1;
}  MAC_SuperframeSpec_t;

//! GTS specification field. IEEE 802.15.4-2006 Figure 48.
typedef struct
{
  uint8_t count    : 3;
  uint8_t reserved : 4;
  uint8_t permit   : 1;
}  MAC_GtsSpec_t;

//! GTS descriptor. IEEE 802.15.4-2006  Figure 50.
typedef struct
{
  ShortAddr_t shortAddr;
  struct
  {
    uint8_t startSlot : 4;
    uint8_t length    : 4;
  } gts;
}  MAC_GtsDescr_t;

/******************************************************************************
                        Defines section.
******************************************************************************/
//! Max of GTS.
#define MAC_GTS_MAX 7 

//! MAC GTS direction type. IEEE 802.15.4-2006 7.3.9.2 GTS Characteristics field.
typedef enum
{
  MAC_GTS_DIRECTION_TRANSMIT = 0,
  MAC_GTS_DIRECTION_RECEIVE  = 1
} MAC_GtsDirection_t;

#endif // _MACSUPERFRAME_H

// eof macSuperframe.h
