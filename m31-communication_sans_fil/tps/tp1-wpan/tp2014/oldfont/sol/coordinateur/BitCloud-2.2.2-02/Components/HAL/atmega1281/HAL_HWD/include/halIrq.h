/*********************************************************************************
\file  halirq.h
  
\brief Declaration of HWD IRQ interface.
  
\internal  
  Copyright (c)Meshnetics.     
  History:
    5/12/07 A. Khromykh - Created
**********************************************************************************/

#ifndef _HALIRQ_H
#define _HALIRQ_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <types.h>
#include <halTaskManager.h>
#include <irq.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
/** \brief number valid interrupt. */
#define HAL_NUM_IRQ_LINES 2
/** \brief first valid interrupt. */
#define HAL_FIRST_VALID_IRQ IRQ_6

/******************************************************************************
                   Types section
******************************************************************************/
/** \brief user's callback type. */
typedef void (* IrqCallback_t)(void);

/******************************************************************************
                   Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Sets configuration of pins and the registers.
\param[in]
  irqNumber - number of interrupt.
\param[in]
  irqMode - mode of interrupt.   
******************************************************************************/
void halSetIrqConfig(uint8_t irqNumber, uint8_t irqMode);

/**************************************************************************//**
\brief Clears configuration of pins and the registers.
\param[in]
  irqNumber - number of interrupt. 
******************************************************************************/
void halClrIrqConfig(uint8_t irqNumber);

/******************************************************************************
                   Inline static functions section 
******************************************************************************/
/**************************************************************************//**
\brief Enables external interrupt
\param[in]
  irqNumber - number of external interrupt.
******************************************************************************/
INLINE void halEnableIrqInterrupt(uint8_t irqNumber)
{
  // Enable external interrupt request
  EIMSK |= (1 << irqNumber);
}

/**************************************************************************//**
\brief Disables external interrupt
\param[in]
  irqNumber - number of external interrupt.
******************************************************************************/
INLINE void halDisableIrqInterrupt(uint8_t irqNumber)
{
  // Disable external interrupt request
  EIMSK &= ~(1 << irqNumber);
}

#endif /* _HALIRQ_H */
//eof halirq.h

