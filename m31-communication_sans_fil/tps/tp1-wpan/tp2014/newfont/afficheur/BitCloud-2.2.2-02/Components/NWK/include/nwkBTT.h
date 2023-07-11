/******************************************************************************
  nwkBTT.h
  Copyright (c)Meshnetics.
  Description: 
    broadcast transaction table.
  History:
    01/09/07 V. Panov - Created.
******************************************************************************/
#ifndef _NWKBTT_H
#define _NWKBTT_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <nwk.h>
#include <nwkAge.h>
#include <nwkConfig.h>

/******************************************************************************
                   Types section
******************************************************************************/
typedef struct _NwkBTR_t
{
  ShortAddr_t  addr;
  uint8_t      seqNu;
  NwkAgeItem_t age;
} NwkBTR_t;

typedef struct _NwkBTT_t
{
  NwkBTR_t      table[NWK_BTT_SIZE];
  uint8_t       tableSize;
  NwkAgeTable_t age;
} NwkBTT_t;

/******************************************************************************
                   Prototypes section
******************************************************************************/

/******************************************************************************
  reset routine
******************************************************************************/
void nwkResetBTT(void);

/******************************************************************************
  chech entry for addr and sequence number
  return false if frame shall not be processed
******************************************************************************/
bool nwkCheckBTT(ShortAddr_t addr, uint8_t seqNu);

/******************************************************************************
  called periodicaly to update age
******************************************************************************/
void nwkUpdateAgeBTT(void);

#endif //_NWKBTT_H
//eof nwkBTT.h
