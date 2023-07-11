/***************************************************************************//**
\file  joystick.h
  Copyright (c)Meshnetics.

\brief
  Description:
    Declaration of joystick interface.

\internal
  History:
    10/09/07 A. Khromykh - Created
*******************************************************************************/

#ifndef _BSPJOYSTICK_H
#define _BSPJOYSTICK_H

/******************************************************************************
                   Includes section
******************************************************************************/
// \cond
#include <types.h>
// \endcond

/******************************************************************************
                   Types section
******************************************************************************/
/*! \brief joystick states */
typedef enum
{
  JOYSTICK_LEFT,
  JOYSTICK_RIGHT,
  JOYSTICK_UP,
  JOYSTICK_DOWN,
  JOYSTICK_PUSH
} BSP_JoystickState_t;

/******************************************************************************
                   Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Opens component and registers handler for joystick events.
\param[in]
    generalHandler - the joystick handler
\param[in]
    state - joystick state 
\return
  FAIL - joystick module is busy, \n
  SUCCESS - joystick module is free.
******************************************************************************/
result_t BSP_OpenJoystick(void (*generalHandler)(BSP_JoystickState_t state));

/**************************************************************************//**
\brief closes joystick component.

\return
  FAIL - joystick module was not opened, \n
  SUCCESS - joystick module was closed.
******************************************************************************/
result_t BSP_CloseJoystick(void);

/**************************************************************************//**
\brief Reads state of joystick.

\return
    Joystick state.
******************************************************************************/
BSP_JoystickState_t BSP_ReadJoystickState(void);

#endif	/* _BSPJOYSTICK_H */
//eof joystick.h
