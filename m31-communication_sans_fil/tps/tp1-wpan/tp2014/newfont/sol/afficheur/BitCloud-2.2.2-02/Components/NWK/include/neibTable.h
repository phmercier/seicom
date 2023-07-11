/******************************************************************************
  neibTable.h
  Copyright (c)Meshnetics.  
  Description: 
    Neighbor table header file
  History:
    14/06/07 S. Vladykin - Created.
******************************************************************************/
#ifndef _NEIBTABLE_H
#define _NEIBTABLE_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <nwk.h>
#include <nwkConfig.h>
#include <nwkSystem.h>
#include <macAddr.h>
#include <appFramework.h>
#include <appTimer.h>

/******************************************************************************
                   Types section
******************************************************************************/
typedef struct
{
  uint8_t   childrenCounter; 
  uint8_t   endDevicesCounter; 
  uint8_t   routersCounter; 
  union {
    Neib_t  *table;
    DEFINE_DBG_ARRAY(Neib_t);
  };
  uint8_t   tableSize;
  HAL_AppTimer_t ageTimer;
  uint16_t  maxEndDeviceAge;
} NeibTable_t;

/******************************************************************************
                   Prototypes section
******************************************************************************/

/******************************************************************************
  reset handler
******************************************************************************/
void nwkResetNeibTable(bool commission);

/******************************************************************************
  looking for free neighbor table entity 
  to mark this entity as busy, need to change relationship field
******************************************************************************/
Neib_t* nwkNeibTableAddNeib(void);

/******************************************************************************
  adding child into table. All required fields are filled. Addr is allocated.
ExtAddr_t           extAddr,        - ext addr of child
ShortAddr_t         addrRequested,  - addr that device selected for itself (trying to keep it)
MAC_CapabilityInf_t capability      - device capability
  returns NULL if fail, or pointer to created record otherwise
******************************************************************************/
Neib_t* nwkNeibTableAddChild(
                             ExtAddr_t           extAddr,
                             ShortAddr_t         addrRequested,
                             MAC_CapabilityInf_t capability
                            );

/******************************************************************************
  find first child
  used by Leave to remove this child
******************************************************************************/
Neib_t* nwkNeibTableFindAnyChild(void);

/******************************************************************************
  removing neighbor. 
  If child is removed beacon payload is corrected.
child - pointer to record to remove
******************************************************************************/
void NWK_NeibTableDeleteNeib(Neib_t* child);
#define nwkNeibTableDeleteNeib NWK_NeibTableDeleteNeib

/******************************************************************************
  find neighbor entry by ext addr. 
returns NULL if no records found, or entry with extAddr otherwise
******************************************************************************/
Neib_t* nwkNeibTableFindByExtAddr(ExtAddr_t extAddr); 

/******************************************************************************
  find neighbor entry by short addr. 
returns NULL if no records found, or entry with shortAddr otherwise
******************************************************************************/
Neib_t *nwkNeibTableFindByShortAddr(ShortAddr_t shortAddr);

/******************************************************************************
  find short addr of neighbor entry by extAddr addr. 
returns short addr if records found, or NWK_NO_SHORT_ADDR otherwise
******************************************************************************/
ShortAddr_t nwkNeibTableGetShortByExt(ExtAddr_t extAddr);

/******************************************************************************
  look for device with extPanid that is potential parent
******************************************************************************/
Neib_t* nwkNeibTableFindDeviceToJoin(ExtPanId_t extPanid, bool rejoin);

/******************************************************************************
  checks if shortAddr is route destination address
  return true if shortAddr is this device address 
       or address of rxonwhenidle==false child
******************************************************************************/
bool nwkIsRouteDestination(ShortAddr_t shortAddr, bool group);

/******************************************************************************
  find neighbor entry by ext panid. 
returns NULL if no records found, or entry with extAddr otherwise
******************************************************************************/
Neib_t* nwkNeibTableFindByExtPanId(ExtPanId_t extPanId);

void neibTableUpdate(ShortAddr_t addr);
void neibUpdateLQIAndAge(ShortAddr_t addr, uint8_t linkQuality, uint8_t rssi);
/******************************************************************************
  find rx off child
******************************************************************************/
Neib_t* nwkNeibTableFindRxOffChild(Neib_t* first,ShortAddr_t except);

#endif //_NEIBTABLE_H
//eof neibTable.h
