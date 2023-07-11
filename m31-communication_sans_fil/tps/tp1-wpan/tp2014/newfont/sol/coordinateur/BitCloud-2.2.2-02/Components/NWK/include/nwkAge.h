/******************************************************************************
  nib.h
  Copyright (c)Meshnetics.
  Description:
    NIB header file.
  History:
    14/06/07 S. Vladykin - Created.
******************************************************************************/
#ifndef _NWKAGE_H
#define _NWKAGE_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <nwk.h>
#include <appTimer.h>

/******************************************************************************
  define's
******************************************************************************/
#define NWK_AGE_PERMANENT 0xFF

/******************************************************************************
  types
******************************************************************************/
typedef struct _NwkAgeItem_t
{
  union 
  {
    uint8_t   timeStamp;
    struct
    {
      uint8_t notUsed  : 7;
      uint8_t veryOld  : 1;
    };
  };
} NwkAgeItem_t;

typedef struct _NwkAgeTable_t
{
  uint16_t      timeStamp;
  NwkAgeItem_t  *ageItemStart;
  uint8_t       ageItemSize;
  uint8_t       size;
} NwkAgeTable_t;

typedef struct _NwkAge_t
{
  HAL_AppTimer_t ageTimer;
} NwkAge_t;

/******************************************************************************
  prototypes
******************************************************************************/

/******************************************************************************
  reset routine
******************************************************************************/
void nwkResetAge(void);

/******************************************************************************
  init aging for any table
NwkAgeTable_t *table - table that needs aging (usualy field of table)
NwkAgeItem_t  *item1 - NwkAgeItem_t of first array element 
NwkAgeItem_t  *item2 - NwkAgeItem_t of second array element,
                       used to calc size of structure containing NwkAgeItem_t, 
                       even if alignment is used
uint8_t tableSize    - size of array
******************************************************************************/
void nwkInitAge(NwkAgeTable_t *table, NwkAgeItem_t *item1, NwkAgeItem_t *item2, uint8_t tableSize);

/******************************************************************************
  shall be called often than (max(timeStamp) / 2) time units
  maxTimeToLive shall be lower than (max(timeStamp) / 2)

NwkAgeTable_t *table  - table to process
uint16_t time         - system time in preferred units
******************************************************************************/
void nwkUpdateAge(NwkAgeTable_t *table, uint16_t time);

/******************************************************************************
  find most unused item
NwkAgeTable_t *table  - table to process
******************************************************************************/
NwkAgeItem_t* nwkFindOldestAge(NwkAgeTable_t *table);

/******************************************************************************
  mark item of table as new, reset its time to live counter
NwkAgeTable_t *table  - table to process
NwkAgeItem_t *item    - item of this table
uint16_t time         - system time in preferred units
******************************************************************************/
void nwkResetItemAge(NwkAgeTable_t *table, NwkAgeItem_t *item, uint16_t time);

/******************************************************************************
  get item age
NwkAgeTable_t *table  - table to process
NwkAgeItem_t *item    - item of this table
uint16_t time         - system time in preferred units
******************************************************************************/
uint8_t nwkGetItemAge(NwkAgeTable_t *table, NwkAgeItem_t *item, uint16_t time);

#endif
//eof
