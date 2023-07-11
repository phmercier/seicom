/******************************************************************************
  halSleepTimerClock.h
  Copyright (c)Meshnetics.

  Description:
    Definition for count out requested sleep interval.

  History:
    29/06/07 E. Ivanov - Created
	26/09/07 A.Khromykh - optimization interrupt handler "halAdjustSleepInterval"
*******************************************************************************/

#ifndef _SLEEPTIMERCLOCK_H
#define _SLEEPTIMERCLOCK_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <types.h>
#include <halTaskManager.h>
#include <avr/io.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
#define SLEEPTIMER_CLOCK 32768lu
#define SLEEPTIMER_PRESCALER_1    (1u << CS20)                  // No prescaling
#define SLEEPTIMER_PRESCALER_8    (1u << CS21)                  // clk/8
#define SLEEPTIMER_PRESCALER_32   (1u << CS20 | 1u << CS21)     // clk/32
#define SLEEPTIMER_PRESCALER_64   (1u << CS22)                  // clk/64
#define SLEEPTIMER_PRESCALER_128  (1u << CS20 | 1u << CS22)     // clk/128
#define SLEEPTIMER_PRESCALER_256  (1u << CS21 | 1u << CS22)     // clk/256
#define SLEEPTIMER_PRESCALER_1024 (1u << CS20 | 1u << CS21 | 1u << CS22) // clk/1024

#if SLEEPTIMER_PRESCALER == SLEEPTIMER_PRESCALER_1
  #define ADJUST_DATA_SYSTEM_COUNTER(data)   (data >> 5)
#elif SLEEPTIMER_PRESCALER == SLEEPTIMER_PRESCALER_8   
  #define ADJUST_DATA_SYSTEM_COUNTER(data)   (data >> 2)
#elif SLEEPTIMER_PRESCALER == SLEEPTIMER_PRESCALER_32 
  #define ADJUST_DATA_SYSTEM_COUNTER(data)   (data)
#elif SLEEPTIMER_PRESCALER == SLEEPTIMER_PRESCALER_64 
  #define ADJUST_DATA_SYSTEM_COUNTER(data)   (data << 1)
#elif SLEEPTIMER_PRESCALER == SLEEPTIMER_PRESCALER_128
  #define ADJUST_DATA_SYSTEM_COUNTER(data)   (data << 2)
#elif SLEEPTIMER_PRESCALER == SLEEPTIMER_PRESCALER_256
  #define ADJUST_DATA_SYSTEM_COUNTER(data)   (data << 3)
#elif SLEEPTIMER_PRESCALER == SLEEPTIMER_PRESCALER_1024
  #define ADJUST_DATA_SYSTEM_COUNTER(data)   (data << 5)
#endif

/******************************************************************************
                   Prototypes section
******************************************************************************/
/******************************************************************************
Test if sleep timer clock is used?
Parameters:
Returns:
  true - sleep timer clock is unused, else false.
******************************************************************************/
bool halSleepTimerClockUnUsed(void);

/******************************************************************************
Stops the application timer. Sets the sleep control flag.
Parameters: 
  enableSleep - if true system will be shutdown after
                the wake up if the interval is still not counted.
Returns:
  none.
******************************************************************************/
void halSleepControl(bool enableSleep);

/*****************************************************************************
Initializes the component.
Parameters:
  none.
Returns:
  none.
*****************************************************************************/
void halInitSleepTimeClock(void);

/******************************************************************************
Starts the sleep timer clock.
Parameters:
  none.
Returns:
  none.
******************************************************************************/
void halStartSleepTimerClock(void);

/******************************************************************************
Sets    interval.
Parameters:
  value - contains number of ticks which the timer must count out.
Returns:
  none.
******************************************************************************/
void halSetSleepTimerInterval(uint32_t value);

/******************************************************************************
Returns interval in ticks.
Parameters:
  none.
Returns:
  number of ticks from moment of halSetSleepTimerInterval call.
******************************************************************************/
uint32_t halSleepTimerCounter(void);

/******************************************************************************
Returns the sleep timer frequency in Hz.
Parameters:
  none.
Returns:
  the sleep timer frequency in Hz.
******************************************************************************/
uint32_t halSleepTimerFrequency(void);

/******************************************************************************
                   Inline static functions section 
******************************************************************************/
/******************************************************************************
Stops the sleep timer clock.
Parameters:
  none.
Returns:
  frequency.
******************************************************************************/
INLINE void halStopSleepTimeClock(void)
{
  TCCR2B &= ~(1 << CS20 | 1 << CS21 | 1 << CS22);  // Stops the timer
}

/******************************************************************************
Disables the sleep timer interrupt.
Parameters:
  none.
Returns:
  none.
******************************************************************************/
INLINE void halDisableSleepTimerInt(void)
{
  TIMSK2 &= ~(1 << OCIE2A); // Disables 8-bit Timer/Counter2 compare interrupt
}

/******************************************************************************
Enables the sleep timer interrupt.
Parameters:
  none.
Returns:
  none.
******************************************************************************/
INLINE void halEnableSleepTimerInt(void)
{
  TIMSK2 |= (1 << OCIE2A); // Sets 8-bit Timer/Counter0 compare interrupt enable
}

/******************************************************************************
  Interrupt handler signal implementation
******************************************************************************/
INLINE void halInterruptSleepClock(void)
{
  halDisableSleepTimerInt();
  halPostTask1(HAL_TIMER2_COMPA);
}

#endif /* _SLEEPTIMERCLOCK_H */
// eof halSleepTimerClock.h
