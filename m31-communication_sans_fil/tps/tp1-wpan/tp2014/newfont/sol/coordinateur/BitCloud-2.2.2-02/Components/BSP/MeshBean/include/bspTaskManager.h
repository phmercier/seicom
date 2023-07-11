/**************************************************************************//**
\file  bspTaslManager.h
  Copyright (c)Meshnetics.

\brief
  Description:
    Declarations of enums and functions of BSP task manager.

\internal          
  History:
    29/05/07 E. Ivanov - Created
*******************************************************************************/

#ifndef _BSPTASKHANDLER_H
#define _BSPTASKHANDLER_H

/******************************************************************************
                   Includes section
******************************************************************************/
// \cond
#include <types.h>
#include <taskManager.h>
// \endcond

/******************************************************************************
                   Define(s) section
******************************************************************************/
enum 
{
  BSP_BUTTONS      = (uint8_t)1 << 0,
  BSP_TEMPERATURE  = (uint8_t)1 << 1,
  BSP_LIGHT        = (uint8_t)1 << 2,
  BSP_BATTERY      = (uint8_t)1 << 3,
};

/******************************************************************************
                   External variables section
******************************************************************************/
extern uint8_t bspTaskFlags0 ;

/******************************************************************************
                   Inline static functions section 
******************************************************************************/
/***************************************************************************//**
\brief posting bsp task for task manager.
\param[in]
  flag - task number
*******************************************************************************/
INLINE void bspPostTask0(uint8_t flag)
{
  bspTaskFlags0 |= flag;
  SYS_PostTask(BSP_TASK_ID);
}

#endif /* _BSPTASKHANDLER_H */
// eof bspTaskManager.h
