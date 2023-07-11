/**************************************************************************//**
\file  sliders.h
  Copyright (c)Meshnetics.

\brief
  Description:
    Implementation of the sliders.

\internal
  History:
    29/06/07 E. Ivanov - Created
******************************************************************************/
/******************************************************************************
                   Includes section
******************************************************************************/
#include <types.h>
#include <gpio.h>
#include <sliders.h>

/******************************************************************************
                   Implementations section
******************************************************************************/
/**************************************************************************//**
\brief Reads the sliders.

\return
   state of 3 on�board DIP�switches.User can uses SLIDER0, SLIDER1, SLIDER2
   defines to test state. Value 1 indicates that slider is on.
******************************************************************************/
uint8_t BSP_ReadSliders(void)
{
  uint8_t result;

  GPIO_3_make_in(); GPIO_3_make_pullup();
  GPIO_4_make_in(); GPIO_4_make_pullup();
  GPIO_5_make_in(); GPIO_5_make_pullup();
  /* NOP was added for correct work on 8 MHz frequency.
     clck i\o is not equal clck cpu.
     CPU must wait for I\O system 1 clock for synchronization. */
  NOP;
  result  = GPIO_3_read() * SLIDER0;
  result |= GPIO_4_read() * SLIDER1;
  result |= GPIO_5_read() * SLIDER2;
  GPIO_3_make_in();
  GPIO_4_make_in();
  GPIO_5_make_in();

  return (~result) & 0x07;
}
// end of sliders.c
