/*****************************************************************************
  apsTimer.h

  Copyright (c)Meshnetics.

  Description:
    APS Timer header file.
          
  History:
    03/12/07 A. Potashov - Created
*****************************************************************************/


#ifndef _APSTIMER_H
#define _APSTIMER_H


/******************************************************************************
                   Includes section
******************************************************************************/
#include <appTimer.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/

/******************************************************************************
                   Types section
******************************************************************************/

typedef enum
{
  APS_TIMER_STOPPED =           0x00,
  APS_TIMER_STARTED =           0x01
} ApsAppTimerStatus_t;

typedef struct
{
  ApsAppTimerStatus_t status;
  HAL_AppTimer_t timer;
} ApsAppTimer_t;
/******************************************************************************
                   Constants section
******************************************************************************/

/******************************************************************************
                   External variables section
******************************************************************************/

/******************************************************************************
                   Prototypes section
******************************************************************************/

/*****************************************************************************
  Start the APS Application Timer
  Parameters: appTimer - timer pointer will be started
  Returns:    None
*****************************************************************************/
extern void apsStartAppTimer(ApsAppTimer_t *appTimer);

/*****************************************************************************
  Stop the APS Application Timer
  Parameters: appTimer - timer pointer will be stopped
  Returns:    None
*****************************************************************************/
extern void apsStopAppTimer(ApsAppTimer_t *appTimer); 

/*****************************************************************************
  Initialize the APS Application Timer
  Parameters: appTimer - timer pointer will be initialized
              mode - timer mode:  TIMER_ONE_SHOT_MODE
                                  TIMER_REPEAT_MODE
              interval - timer interval (milliseconds)
              handler - timer handler function pointer
  Returns:    None
*****************************************************************************/
extern void apsInitAppTimer(ApsAppTimer_t *appTimer, TimerMode_t mode, 
                            uint32_t interval, void (*handler)(void)); 


#endif  //#ifndef _APSTIMER_H

//eof apsTimer.h

