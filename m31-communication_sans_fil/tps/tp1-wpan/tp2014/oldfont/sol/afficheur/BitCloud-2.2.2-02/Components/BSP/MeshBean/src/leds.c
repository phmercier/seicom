/***************************************************************************//**
\file  leds.c
  Copyright (c)Meshnetics.
 
\brief 
  Description:
    The module to access to the leds.

\internal          
  History:
    29/05/07 E. Ivanov - Created
*******************************************************************************/
/******************************************************************************
                   Includes section
******************************************************************************/
#include <bspLeds.h>
#include <sensors.h>
#include <pwrCtrl.h> 

/******************************************************************************
                   Implementations section
******************************************************************************/
/**************************************************************************//**
\brief Inits�LEDs�control�module.
******************************************************************************/
static void initLeds(void) 
{         
  halInitRedLed();
  halInitYellowLed();
  halInitGreenLed();
}

/**************************************************************************//**
\brief Opens leds module to use.

\return 
    operation state
******************************************************************************/
result_t BSP_OpenLeds(void)
{
  initLeds();
  bspOnPeriphery(SENSOR_LED); 
  return SUCCESS;
}

/**************************************************************************//**
\brief Closes leds module.

\return 
    operation state
******************************************************************************/
result_t BSP_CloseLeds(void)
{
  bspOffPeriphery(SENSOR_LED); 
  halUnInitRedLed();
  halUnInitYellowLed();
  halUnInitGreenLed();
  return SUCCESS;
}

/**************************************************************************//**
\brief Turns�on the�LED.

\param[in]
    id - number of led
******************************************************************************/
void BSP_OnLed(uint8_t id)
{
  switch (id)
  {
    case LED_RED:
      halOnRedLed();
      break;
    case LED_GREEN:
      halOnGreenLed();
      break;
    case LED_YELLOW:
      halOnYellowLed();
      break;
  }
}

/**************************************************************************//**
\brief Turns�off the�LED.

\param[in]
      id - number of led
******************************************************************************/
void BSP_OffLed(uint8_t id)
{
  switch (id)
  {
    case LED_RED:
      halOffRedLed();
      break;
    case LED_GREEN:
      halOffGreenLed();
      break;
    case LED_YELLOW:
      halOffYellowLed();
      break;
  }
}

/**************************************************************************//**
\brief Changes the�LED state to opposite.

\param[in]
      id - number of led
******************************************************************************/
void BSP_ToggleLed(uint8_t id)
{
  switch (id)
  {
    case LED_RED:
      halToggleRedLed();
      break;
    case LED_GREEN:
      halToggleGreenLed();
      break;
    case LED_YELLOW:
      halToggleYellowLed();
      break;  
  }
}

// eof leds.c
