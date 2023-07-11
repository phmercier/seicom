/***************************************************************************//**
\file  buttons.h

\brief
    Declaration of buttons interface.

\internal
  Copyright (c)Meshnetics.
  History:
    29/05/07 E. Ivanov - Created
*******************************************************************************/

#ifndef _BSPBUTTONS_H
#define _BSPBUTTONS_H

/******************************************************************************
                   Includes section
******************************************************************************/
// \cond
#include <types.h>
// \endcond

/******************************************************************************
                   Define(s) section
******************************************************************************/
// \cond
#define BSP_KEY0 ((uint8_t)1 << 0)
#define BSP_KEY1 ((uint8_t)1 << 1)
// \endcond

/******************************************************************************
                   Types section
******************************************************************************/

// \cond
typedef void (*BSP_ButtonsEventFunc_t)(uint8_t);
// \endcond

/******************************************************************************
                   Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Registers handlers for button events.
\param[in]
    pressed - the handler to process pressing of the button \n
    bn - button number.
\param[in]
    released - the handler to process releasing of the button \n
    bn - button number.
\return
  FAIL - buttons module is busy, \n
  SUCCESS - otherwise.
******************************************************************************/
result_t BSP_OpenButtons(void (*pressed)(uint8_t bn), void (*released)(uint8_t bn));

/**************************************************************************//**
\brief Cancel buttons handlers.
\return
  FAIL - buttons module was not opened, \n
  SUCCESS - otherwise.
******************************************************************************/
result_t BSP_CloseButtons();

/**************************************************************************//**
\brief Reads state of the buttons.
\return
    Current buttons state in a binary way. \n
    Bit 0 defines the state of button 1, bit 1 defines the state of button 2.
******************************************************************************/
uint8_t BSP_ReadButtonsState(void);

#endif	/* _BSPBUTTONS_H */
//eof buttons.h
