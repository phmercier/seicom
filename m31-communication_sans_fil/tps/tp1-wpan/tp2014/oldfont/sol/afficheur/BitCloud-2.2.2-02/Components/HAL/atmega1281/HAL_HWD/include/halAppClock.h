/******************************************************************************
\file  halAppClock.h
    
\brief Declarations of appTimer hardware-dependent module.

\internal 
  Copyright (c)Meshnetics.
  History:
    5/12/07 A. Khromykh - Created
******************************************************************************/
#ifndef _HALAPPCLOCK_H
#define _HALAPPCLOCK_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <halClkCtrl.h>
#include <halTaskManager.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
/** \brief system timer interval in ms */
#define HAL_APPTIMERINTERVAL 10ul

/******************************************************************************
                   External variables section
******************************************************************************/
/** \brief system time */
extern volatile uint32_t halSystemTime;

/******************************************************************************
                   Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Enables appTimer clock.
******************************************************************************/
void halStartAppClock(void);

/**************************************************************************//**
\brief Disables appTimer clock.
******************************************************************************/
void halStopAppClock(void);

/**************************************************************************//**
\brief Return system time in us
\param[out]
  mem - memory for system time
******************************************************************************/
void halGetSystemTimeUs(uint64_t *mem);

/******************************************************************************
                   Inline static functions section 
******************************************************************************/
/**************************************************************************//**
\brief Interrupt handler signal implementation
******************************************************************************/
INLINE void halInterruptAppClock(void)
{
  halSystemTime += HAL_APPTIMERINTERVAL;
  halPostTask4(HAL_TIMER4_COMPA);
}

/**************************************************************************//**
\brief Takes account of the sleep interval.

\param[in]
  interval - time of sleep
******************************************************************************/
INLINE void halAdjustSleepInterval(uint32_t interval)
{
  halSystemTime += interval;
  halPostTask4(HAL_TIMER4_COMPA);
}

#endif /*_HALAPPCLOCK_H*/

// eof halAppClock.h
