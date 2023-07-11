/******************************************************************************
  nwkAddrMap.h
  Copyright (c)Meshnetics.
  Description: 
    ext sh map
  History:
    02/10/07 V. Panov - Created.
******************************************************************************/
#ifndef _NWKADDRMAP_H
#define _NWKADDRMAP_H

/******************************************************************************
                        Includes section
******************************************************************************/
#include <nwk.h>
#include <nwkAge.h>
#include <nwkStatusCommand.h>
#include <nwkConfig.h>

/******************************************************************************
                   Types section
******************************************************************************/
typedef struct _NwkAddrMapItem_t
{
  union {
    ExtAddr_t      ext;
    ShortAddr_t    conflictInfo;
  };
  ShortAddr_t      sh;
  NwkAgeItem_t     age;
} NwkAddrMapItem_t;

typedef struct _NwkAddrMapTable_t 
{
  NwkAddrMapItem_t      *table;
  uint8_t               size;
  NwkAgeTable_t         age;
  NwkStatusCommandReq_t statusReq;
  bool                  statusReqActive;
} NwkAddrMapTable_t;

/******************************************************************************
                        Prototypes section
******************************************************************************/

/******************************************************************************
  reset routine
******************************************************************************/
void nwkResetAddrMap(void);

/******************************************************************************
  add new entry (check conflicts)
******************************************************************************/
void nwkAddrMapAdd(ShortAddr_t sh, ExtAddr_t ext);

/******************************************************************************
  beat timer to allow aging
******************************************************************************/
void nwkUpdateAgeAddrMap(void);

/******************************************************************************
******************************************************************************/
void nwkAddrMapRemoveShort(uint16_t sh);

/******************************************************************************
  find ext by short
******************************************************************************/
ExtAddr_t* NWK_FindExtByShort(ShortAddr_t *addr);

/******************************************************************************
  find short by ext
******************************************************************************/
ShortAddr_t* NWK_FindShortByExt(ExtAddr_t *addr);

#endif //_NWKADDRMAP_H
//eof nwkAddrMap.h
