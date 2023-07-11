/*************************************************************************//**
\file  calibration.c

\brief
  Description:
    Interface to calibrate the internal RC generator.

\internal
  Copyright (c)Meshnetics.
  History:
    29/06/07 E. Ivanov - Created
******************************************************************************/

#ifndef _CALIBRATION_H
#define _CALIBRATION_H
/**************************************************************************//**
\brief Performs calibration of the main clock generator \n
(only for AVR and internal RC oscillator).
******************************************************************************/
void HAL_CalibrateMainClock(void);

#endif /* _CALIBRATION_H */
// eof calibration.h
