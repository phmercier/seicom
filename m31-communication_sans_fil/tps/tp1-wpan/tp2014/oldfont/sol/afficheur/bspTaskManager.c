/**************************************************************************//**
\file  bspTaskManager.c
  Copyright (c)Meshnetics.

\brief
  Description:
   Implemenattion of BSP task manager.

\internal
  History:
    29/05/07 E. Ivanov - Created
******************************************************************************/
/******************************************************************************
                   Includes section
******************************************************************************/
#include <bspTaskManager.h>
#include <atomic.h>

/******************************************************************************
                   Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief BSP button handler.
******************************************************************************/
void bspButtonsHandler(void);

/**************************************************************************//**
\brief BSP lm73 handler.
******************************************************************************/
//void bspLM73Handler(void);

/**************************************************************************//**
\brief BSP lm73 handler.
******************************************************************************/
//void bspPCF8575Handler(void);

/**************************************************************************//**
\brief BSP tsl2550 handler.
******************************************************************************/
//void bspTsl2550Handler(void);

/**************************************************************************//**
\brief BSP battery handler.
******************************************************************************/
//void bspBatteryHandler(void);

/******************************************************************************
                   Global variables section
******************************************************************************/
uint8_t bspTaskFlags0 = 0;

/******************************************************************************
                   Implementations section
******************************************************************************/
/**************************************************************************//**
\brief BSP task handler.
******************************************************************************/
void BSP_TaskHandler(void)
{
//#ifdef _BUTTONS_
  if (bspTaskFlags0 & BSP_BUTTONS)
  {
    bspTaskFlags0 &= (~BSP_BUTTONS);
    bspButtonsHandler();
  }
//#else
//  if (0)
//  {
//  }
//#endif
//#ifdef _TEMPERATURE_SENSOR_
//  if (bspTaskFlags0 & BSP_PCF8575)
//  {
//    bspTaskFlags0 &= (~BSP_PCF8575);
//    bspPCF8575Handler();
//  }
//#endif
//#ifdef _LIGHT_SENSOR_
//  if (bspTaskFlags0 & BSP_LIGHT)
//  {
//    bspTaskFlags0 &= (~BSP_LIGHT);
//    bspTsl2550Handler();
//  }
//#endif
//#ifdef _BATTERY_SENSOR_
//  if (bspTaskFlags0 & BSP_BATTERY)
//  {
//    bspTaskFlags0 &= (~BSP_BATTERY);
//    bspBatteryHandler();
//  }
//#endif

  if (bspTaskFlags0)
  {
    SYS_PostTask(BSP_TASK_ID);
  }
}
// eof bspTaskManager.c
