/******************************************************************************
  halMacIsr.h
  
 Copyright (c)Meshnetics.

  Description: 
    TBD.

  History:         
    14/01/08 A. Mandychev - Created. 
******************************************************************************/

#ifndef _HALMACISR_H
#define _HALMACISR_H

/******************************************************************************
                        Includes section.
******************************************************************************/
#include <inttypes.h>
#include <types.h>
#include <avr/io.h>

/******************************************************************************
                        Types section.
******************************************************************************/
typedef enum
{
  HAL_RTIMER_REPEAT_MODE  =  0,
  HAL_RTIMER_ONE_SHOT_MODE = 1,
} HAL_RTimerMode_t;

typedef enum
{
#ifdef AT86RF230
  HAL_RX_FRAME_DELAY_ID,
#endif // AT86RF230
  HAL_ED_DELAY_ID,
  HAL_RF_STATE_POLL_DELAY_ID
} HAL_RTimerSource_t;

typedef struct // Timer description.
{
  HAL_RTimerSource_t  source;     // Source of timer invocation
  HAL_RTimerMode_t    mode;       // Mode.
  uint16_t               period;     // Period of the timer.
  uint16_t               nextEvent;  // Counter of periods.
} RTimerDescr_t;

/******************************************************************************
                        External variables.
******************************************************************************/
// Do not use it in othere files.
extern RTimerDescr_t __rtimer;
extern uint8_t __freqDivisor;

/******************************************************************************
                        Prototypes section.
******************************************************************************/
/******************************************************************************
  Initializes Rtimer and RF ext. interrupts.
******************************************************************************/
void HAL_InitMacIsr(void);

/******************************************************************************
                 Inline static functions prototypes section.
******************************************************************************/
/******************************************************************************
  Starts RTimer. Function should be invoked in critical section.
  Parmeters:
    source  - source of invocation.
    mode    - RTimer mode.
    period  - RTimer period.
******************************************************************************/
INLINE void HAL_StartRtimer(HAL_RTimerSource_t source, 
                            HAL_RTimerMode_t mode, uint16_t period)
{
  __rtimer.source = (uint8_t) source;
  __rtimer.period = (uint16_t) period * __freqDivisor;
  __rtimer.mode = mode;
  *((uint16_t *) &OCR1AL) = __rtimer.nextEvent = TCNT1 + __rtimer.period;
  // clear possible interrupt by setting logical one.
  TIFR1 = (1 << OCF1A);
  // enable interrupt
  TIMSK1 |= (1 << OCIE1A);
}

/******************************************************************************
  Stops RTimer. Function should be invoked in critical section.
******************************************************************************/
INLINE void HAL_StopRtimer(void)
{
  // clear possible interrupt
  TIFR1 &= ~(1 << OCF1A);
  // disable interrupt
  TIMSK1 &= ~(1 << OCIE1A);
}

#endif /* _HALMACISR_H */

// eof halMacIsr.h
