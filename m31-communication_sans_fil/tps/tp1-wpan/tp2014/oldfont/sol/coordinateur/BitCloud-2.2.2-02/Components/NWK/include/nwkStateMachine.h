/******************************************************************************
  nwkStateMachine.h
  
  Copyright (c)Meshnetics.

  Description: 
    header file.

  History:     
    14/06/07 V. Panov - Created.
******************************************************************************/
#ifndef _NWKSTATEMACHINE_H
#define _NWKSTATEMACHINE_H

/******************************************************************************
                        Includes section
******************************************************************************/
#include <types.h>

/******************************************************************************
                        Types section
******************************************************************************/
typedef enum
{
  NWK_MODULE_ID_DATA_REQ,
  NWK_MODULE_ID_COMMAND_REQ,
  NWK_MODULE_ID_DATA_IND,
  NWK_MODULE_ID_COMMAND_IND,
  NWK_MODULE_ID_DISCOVERY,
  NWK_MODULE_ID_FORMATION,
  NWK_MODULE_ID_JOIN_REQ,
  NWK_MODULE_ID_JOIN_IND,
  NWK_MODULE_ID_LEAVE,
  NWK_MODULE_ID_LINK_STATUS,
  NWK_MODULE_ID_SYNC,
  NWK_MODULE_ID_NETWORK_COMMAND,
  NWK_MODULE_ID_PANID_CONFLICT,
} NwkStateMachineModuleID_t;

typedef enum 
{
  NWK_EVENT_RESET_REQ,
  NWK_EVENT_FORMATION_SUCCESS,
  NWK_EVENT_JOIN_SUCCESS,
  NWK_EVENT_LEAVE_REQ,
  NWK_EVENT_LEAVE_SUCCESS,
  NWK_EVENT_REJOIN_REQ,
  NWK_EVENT_REJOIN_SUCCESS,
} NwkStateMachineEvent_t;

typedef enum _NwkState_t
{
  NWK_STATE_INITIAL,
  NWK_STATE_RESET,
  NWK_STATE_IN_NETWORK,
  NWK_STATE_LEAVING,
  NWK_STATE_LEFT,
  NWK_STATE_REJOIN,
} NwkState_t;

typedef struct _NwkStateMachine_t
{
  NwkState_t state;
  uint8_t    busy;
} NwkStateMachine_t;
/******************************************************************************
                        Prototypes section
******************************************************************************/

/******************************************************************************
  return true, if module with moduleID is allowed to work
******************************************************************************/
bool nwkCheckStateMachine(NwkStateMachineModuleID_t moduleID);

/******************************************************************************
  modules that can switch state machine shall send events
event - id of event
  state machine may swith state depend on events
******************************************************************************/
void nwkSwitchStateMachine(NwkStateMachineEvent_t event);

void nwkSetBusy(void);
void nwkClearBusy(void);

#endif //_NWKSTATEMACHINE_H
// eof nwkStateMachine.h
