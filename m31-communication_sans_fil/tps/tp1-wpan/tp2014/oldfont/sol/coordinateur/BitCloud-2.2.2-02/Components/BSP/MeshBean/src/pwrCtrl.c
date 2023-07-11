/***************************************************************************//**
\file  pwrCtrl.c
  Copyright (c)Meshnetics.

\brief 
  Description:
    The module to control the power on periphery.

\internal          
  History:
    29/05/07 E. Ivanov - Created
*******************************************************************************/
/******************************************************************************
                   Includes section
******************************************************************************/
#include <types.h>
#include <pwrCtrl.h>
#include <gpio.h>

/******************************************************************************
                   Global variables section
******************************************************************************/
uint8_t bspPowerControl = 0;

/******************************************************************************
                   Implementations section
******************************************************************************/
/**************************************************************************//**
\brief  Powers on periphery.

\param[in]
  id - periphery id.
******************************************************************************/
void bspOnPeriphery(uint8_t id)
{
  if (!bspPowerControl)
  {
    halOnPeriphery();
  }
  bspPowerControl |= (1 << id);
}


/**************************************************************************//**
\brief  Powers off periphery.

\param[in]
  id - periphery id.
******************************************************************************/
void bspOffPeriphery(uint8_t id)
{
  bspPowerControl &= ~(1 << id);
  if (bspPowerControl) 
    return;
  halOffPeriphery();
}

// eof pwrCtrl.c
