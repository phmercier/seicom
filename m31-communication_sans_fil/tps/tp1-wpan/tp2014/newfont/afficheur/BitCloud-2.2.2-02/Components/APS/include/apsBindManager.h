 /*****************************************************************************
  apsBindManager.h

  Copyright (c)Meshnetics.

  Description:  
    APS BINDING feature header file. 
         
  History:
    11/03/08 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSBINDMANAGER_H
#define _APSBINDMANAGER_H
#ifdef _BINDING_

#include <aps.h>

#define APS_INVALID_BINDING_TABLE_ENTRY_INDEX   0xff

#ifndef CS_APS_BINDING_TABLE_ENTRIES_AMOUNT
#define CS_APS_BINDING_TABLE_ENTRIES_AMOUNT     1   
#endif

#ifndef CS_APS_BINDING_TABLE_ENTRY_SIZE
#define CS_APS_BINDING_TABLE_ENTRY_SIZE         2
#endif

typedef struct
{
  APS_AddrMode_t addrMode;
  APS_Address_t addr;
  Endpoint_t endpoint;
} ApsBindingTableDestinationEntry_t;

typedef struct
{
  ExtAddr_t addr;
  Endpoint_t endpoint;
  uint16_t clusterId;
} ApsBindingTableSourceEntry_t;

typedef struct
{
  ApsBindingTableSourceEntry_t        src;
  ApsBindingTableDestinationEntry_t   dst[0];
} ApsBindingTableEntry_t;

typedef struct
{
  uint8_t entriesAmount;
  uint8_t entrySize;
  uint16_t entrySizeof;
  ApsBindingTableEntry_t *entries;  
} ApsBindingTable_t;

typedef struct
{
  ApsBindingTableEntry_t *entry;
  uint8_t index;
} ApsBindingDescriptor_t;


#ifndef CS_APS_BINDING_TABLE_SIZEOF
#define CS_APS_BINDING_TABLE_SIZEOF ((sizeof(ApsBindingTableDestinationEntry_t) * CS_APS_BINDING_TABLE_ENTRY_SIZE + \
                                      sizeof(ApsBindingTableSourceEntry_t)) * CS_APS_BINDING_TABLE_ENTRIES_AMOUNT)
#endif


extern void apsResetBindManager(uint8_t options);
extern ApsBindingTableEntry_t *apsFindBindSrcEntry(ApsBindingTableSourceEntry_t *src);
extern uint8_t apsGetNextBindDestEntryIndex(ApsBindingTableEntry_t *entry, uint8_t index);

#endif //#ifdef _BINDING_
#endif //#ifndef _APSBINDMANAGER_H
//eof apsBindManager.h
