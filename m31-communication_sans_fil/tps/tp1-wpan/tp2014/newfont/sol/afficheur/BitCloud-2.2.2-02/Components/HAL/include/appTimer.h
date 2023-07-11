/******************************************************************************/
/** \file  appTimer.h
  
\brief
    Declarations of the appTimer interface.

\internal  
  Copyright (c)Meshnetics.
  History:
    5/12/07 A. Khromykh - Created
*******************************************************************************/

#ifndef _APPTIMER_H
#define _APPTIMER_H

// \cond
/******************************************************************************
                   Includes section
******************************************************************************/
#include <types.h>
#include <timer.h>
#include <halAppClock.h>
// \endcond

/******************************************************************************
                   Types section
******************************************************************************/
/** \brief fields of structure: \n
    uint32_t interval - timer firing interval. Interval must be more than 10 ms (set by user) \n
    TimerMode_t mode - timer work mode (set by user). Must be chosen from: \n
           TIMER_REPEAT_MODE \n
           TIMER_ONE_SHOT_MODE \n 
    void (*callback)() - pointer to timer callback function (set by user). */
typedef Timer_t HAL_AppTimer_t;

// \cond
/******************************************************************************
                   External variables section
******************************************************************************/
extern volatile uint32_t halSystemTime;
// \endcond

/******************************************************************************
                   Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Starts to count an interval (starts user timer).

\param[in]
  appTimer - pointer to the timer structure (HAL_AppTimer_t is typedef Timer_t)

\return
 -1 - pointer is NULL
  0 - success
******************************************************************************/
int HAL_StartAppTimer(HAL_AppTimer_t *appTimer);

/**************************************************************************//**
\brief Stops the user timer.

\param[in]
  appTimer - pointer to the timer structure.

\return
 -1 - there is no appTimer started or pointer is NULL
  0 - success
******************************************************************************/
int HAL_StopAppTimer(HAL_AppTimer_t *appTimer);

/******************************************************************************
                   Inline static functions section 
******************************************************************************/
/**************************************************************************//**
\brief Gets system time.

\return
  time since power up in milliseconds.
******************************************************************************/
INLINE uint32_t HAL_GetSystemTime(void)
{
  return halSystemTime;
}

#endif /*_APPTIMER_H*/
//eof appTimer.h
