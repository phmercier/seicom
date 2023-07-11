/**************************************************************************//**
\file  sliders.h

\brief
    Interface of sliders.

\internal
  Copyright (c)Meshnetics.
  History:
    29/06/07 E. Ivanov - Created
******************************************************************************/

#ifndef _SLIDERS_H
#define _SLIDERS_H

/******************************************************************************
                   Define(s) section
******************************************************************************/
// \cond
#define SLIDER0 (1 << 0)
#define SLIDER1 (1 << 1)
#define SLIDER2 (1 << 2)
#define SLIDER3 (1 << 3)
// \endcond

/******************************************************************************
                   Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Reads the sliders.
\return
   state onboard DIP switches. User can use SLIDER0, SLIDER1, SLIDER2, SLIDER3*
   constants to check state. Value 1 indicates that the corresponding slider 
   is on.
   * - there is the SLIDER3 on arm turbo board only. 
******************************************************************************/
uint8_t BSP_ReadSliders(void);

#endif /* _SLIDERS_H */
// eof sliders.h
