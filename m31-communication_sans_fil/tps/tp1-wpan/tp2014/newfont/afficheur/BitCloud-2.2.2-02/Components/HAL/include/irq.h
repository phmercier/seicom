/******************************************************************************/
/** \file  irq.h

\brief
    Declaration of the IRQ interface.

\internal  
  Copyright (c)Meshnetics.
  History:
    5/12/07 A. Khromykh - Created
*******************************************************************************/

#ifndef _IRQ_H
#define _IRQ_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <types.h>

/******************************************************************************
                   Types section
******************************************************************************/
/** \brief numbers of possible interrupt. */
typedef enum
{
/** \brief number of valid interrupt for arm. */
  IRQ_0 = 0,
/** \brief number of valid interrupt for arm. */
  IRQ_1 = 1,
  IRQ_2 = 2,
  IRQ_3 = 3,
  IRQ_4 = 4,
  IRQ_5 = 5,
/** \brief number of valid interrupt for avr. */
  IRQ_6 = 6,
/** \brief number of valid interrupt for avr. */
  IRQ_7 = 7
} HAL_IrqNumber_t;

/** \brief interrupt activation condition. */
typedef enum
{
/** \brief The low level generates an interrupt request. */  	
  IRQ_LOW_LEVEL, 
/** \brief The high level generates an interrupt request (valid only for arm). */  
  IRQ_HIGH_LEVEL,
/** \brief Any edge generates an interrupt request (valid only for avr). */  
  IRQ_ANY_EDGE,
/** \brief Falling edge generates an interrupt request. */  
  IRQ_FALLING_EDGE,
/** \brief Rising edge generates an interrupt request. */  
  IRQ_RISING_EDGE
} HAL_IrqMode_t;

/******************************************************************************
                   Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Registers the user's irqNumber external interrupt

\param[in]
   irqNumber - IRQ number. Must be chosen from: \n
            IRQ_0 (for arm)  \n
            IRQ_1 (for arm) \n 
            IRQ_6 (for avr) \n
            IRQ_7 (for avr) \n                                                    
\param[in]
   irqMode - Controls the sort of interrupt. Must be chosen from: \n
            IRQ_LOW_LEVEL         // The low level generates an interrupt request. \n
            IRQ_HIGH_LEVEL        // The high level generates an interrupt request (valid only for arm). \n   
            IRQ_ANY_EDGE          // Any edge generates an interrupt request (valid only for avr).  \n
            IRQ_FALLING_EDGE      // Falling edge generates an interrupt request. \n
            IRQ_RISING_EDGE       // Rising edge generates an interrupt request. \n  
\param[in]
   f         - user's interrupt handler. Handler must be executed less than 100 us. 
\return
  -1 - if irqNumber is out of range, \n 
       not valid irq mode, \n
       such interrupt has been already registered. \n
   0 - otherwise.   
******************************************************************************/
int HAL_RegisterIrq(HAL_IrqNumber_t irqNumber, HAL_IrqMode_t irqMode, void (*f)(void));

/******************************************************************************
\brief Enables the irqNumber interrupt
\param[in]
   irqNumber - IRQ number
\return
   -1 - if irqNumber is out of range or has not been registered yet. \n
    0 - otherwise.   
******************************************************************************/
int HAL_EnableIrq(HAL_IrqNumber_t irqNumber);

/******************************************************************************
\brief Disables the irqNumber interrupt
\param[in]
   irqNumber - IRQ number
\return
   -1 - if irqNumber is out of range or has not been registered yet. \n
    0 - otherwise.   
******************************************************************************/
int HAL_DisableIrq(HAL_IrqNumber_t irqNumber);

/******************************************************************************
\brief Unregisters the user's irqNumber interrupt
\param[in]
   irqNumber - IRQ number
\return
   -1 - if irqNumber is out of range or has not been registered yet. \n
    0 - otherwise.   
******************************************************************************/
int HAL_UnregisterIrq(HAL_IrqNumber_t irqNumber);

#endif /* _IRQ_H */ 
//eof irq.h
