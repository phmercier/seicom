/******************************************************************************
  nwkFrame.h
  Copyright (c)Meshnetics.
  Description: 
    nwk frames header file.
  History:
    01/07/07 S. Vladykin - Created.
******************************************************************************/
#ifndef _NWKGROUP_H
#define _NWKGROUP_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <nwk.h>
#include <aps.h>

/******************************************************************************
  inline functions
******************************************************************************/

/******************************************************************************
  gate to APS group container
******************************************************************************/
static inline bool nwkIsGroupMember(ShortAddr_t addr)
{
#ifdef _APS_MULTICAST_
  return NULL != APS_FindGroup(addr, NULL);
#else
  addr = addr;
  return false;
#endif

}

#endif
//eof nwkGroups.h
