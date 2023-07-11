/*****************************************************************************
  apsStateMachine.h

  Copyright (c)Meshnetics.

  Description:
    APS State Machine header file.  
          
  History:
    06/06/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSSTATEMASHINE_H
#define _APSSTATEMASHINE_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <apsComponentId.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/

/******************************************************************************
                   Types section
******************************************************************************/

typedef enum
{
  APS_INITIAL_STATE,
  APS_RESETTING_STATE,
  APS_RESET_STATE,
  APS_START_STATE,
  APS_STOPPING_STATE,
  APS_STOP_STATE
} ApsState_t;


/******************************************************************************
                   Constants section
******************************************************************************/

/******************************************************************************
                   External variables section
******************************************************************************/


/******************************************************************************
                   Prototypes section
******************************************************************************/

/*****************************************************************************
  APS State Machine API
*****************************************************************************/

/*****************************************************************************
  Peforms the setting of APS State Machine current state to specified state
  Parameters: state - state will be set
  Returns: None
*****************************************************************************/
void apsSetState(ApsState_t state);


/*****************************************************************************
  Returns the APS State Machine current state
  Parameters: None
  Returns: APS State Machine current state
*****************************************************************************/
extern ApsState_t apsGetState(void);
extern ApsState_t apsGetPrevState(void);


/*****************************************************************************
  The function performs checking the certain layer component availability 
  in depending on the APS State Machine
  Parameters: componentId - component ID
  Returns: TRUE - component specified is available
           FALSE - component specified is unavailable 
*****************************************************************************/
bool apsCheckState(ApsComponentId_t componentId);


/*****************************************************************************
  Make a reset of APS State Machine
  Parameters: None
  Returns:    None
*****************************************************************************/
void apsResetStateMachine(uint8_t options);

//============================================================================


/******************************************************************************
                   Inline static functions section 
******************************************************************************/


#endif  //#ifndef _APSSTATEMASHINE_H


//eof apsStateMachine.h
