/******************************************************************************/
/** \file  sleepTimer.h

\brief
    Declarations of sleepTimer interface.

\internal
  Copyright (c)Meshnetics.
  History:
    29/05/07 E. Ivanov - Created
*******************************************************************************/
#ifndef _SLEEPTIMER_H
#define _SLEEPTIMER_H

// \cond
#include <timer.h>
// \endcond

/** \brief fields of structure \n
    \brief uint32_t interval - timer firing interval (set by user) \n
    \brief TimerMode_t mode - timer work mode (set by user). Must be chosen from: \n
           TIMER_REPEAT_MODE \n
           TIMER_ONE_SHOT_MODE \n
    \brief void (*callback)() - pointer to the timer callback function (set by user) \n */
typedef Timer_t HAL_SleepTimer_t;

/**************************************************************************//**
\brief Converts an interval from milliseconds to sleep timer ticks.
\param[in]
  interval - interval in milliseconds.
\return
  interval in sleep timer ticks.
******************************************************************************/
uint32_t HAL_ConvertToSleepInterval(uint32_t interval);

/**************************************************************************//**
\brief Starts sleep timer.
\param[in]
    sleepTimer - pointer to sleep timer structure.
\return
    -1 - bad interval. \n
     0 - otherwise.
******************************************************************************/
int HAL_StartSleepTimer(HAL_SleepTimer_t *sleepTimer);

/**************************************************************************//**
\brief Removes timer.
\param[in]
  sleepTimer - address of the timer to be removed from the list
\return
  -1 - there is no such timer in the list. \n
   0 - otherwise.
******************************************************************************/
int HAL_StopSleepTimer(HAL_SleepTimer_t *sleepTimer);

#endif /* _SLEEPTIMER_H */
// eof sleepTimer.h
