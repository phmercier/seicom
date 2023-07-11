/***************************************************************************//**
\file  leds.h
  Copyright (c)Meshnetics.

\brief
    Declaration of leds defines.

\internal  
  History:
    29/05/07 E. Ivanov - Created
*******************************************************************************/

#ifndef _BSPLEDS_H
#define _BSPLEDS_H

/******************************************************************************
                   Includes section
******************************************************************************/
// \cond
#include <gpio.h>
#include <leds.h>
// \endcond

/******************************************************************************
                   Define(s) section
******************************************************************************/
#ifndef _STK500
  #define halInitRedLed()       GPIO_0_make_out()
  #define halUnInitRedLed()     GPIO_0_make_in()
  #define halOnRedLed()         GPIO_0_set()
  #define halOffRedLed()        GPIO_0_clr()
  #define halReadRedLed()       GPIO_0_read()
  #define halToggleRedLed()     GPIO_0_toggle()

  #define halInitYellowLed()    GPIO_1_make_out()
  #define halUnInitYellowLed()  GPIO_1_make_in()
  #define halOnYellowLed()      GPIO_1_set()
  #define halOffYellowLed()     GPIO_1_clr()
  #define halReadYellowLed()    GPIO_1_read()
  #define halToggleYellowLed()  GPIO_1_toggle()

  #define halInitGreenLed()     GPIO_2_make_out()
  #define halUnInitGreenLed()   GPIO_2_make_in()
  #define halOnGreenLed()       GPIO_2_set()
  #define halOffGreenLed()      GPIO_2_clr()
  #define halReadGreenLed()     GPIO_2_read()
  #define halToggleGreenLed()   GPIO_2_toggle()
#else
  #define halInitRedLed()       GPIO_9_make_out(); GPIO_9_set()
  #define halUnInitRedLed()     GPIO_9_make_in()
  #define halOnRedLed()         GPIO_9_clr()
  #define halOffRedLed()        GPIO_9_set()
  #define halReadRedLed()       GPIO_9_read()
  #define halToggleRedLed()     GPIO_9_toggle()

  #define halInitYellowLed()    GPIO_10_make_out(); GPIO_10_set()
  #define halUnInitYellowLed()  GPIO_10_make_in()
  #define halOnYellowLed()      GPIO_10_clr()
  #define halOffYellowLed()     GPIO_10_set()
  #define halReadYellowLed()    GPIO_10_read()
  #define halToggleYellowLed()  GPIO_10_toggle()

  #define halInitGreenLed()     GPIO_11_make_out(); GPIO_11_set()
  #define halUnInitGreenLed()   GPIO_11_make_in()
  #define halOnGreenLed()       GPIO_11_clr()
  #define halOffGreenLed()      GPIO_11_set()
  #define halReadGreenLed()     GPIO_11_read()
  #define halToggleGreenLed()   GPIO_11_toggle()
#endif //_STK500 

#endif /*_BSPLEDS_H*/
// eof bspLeds.h
