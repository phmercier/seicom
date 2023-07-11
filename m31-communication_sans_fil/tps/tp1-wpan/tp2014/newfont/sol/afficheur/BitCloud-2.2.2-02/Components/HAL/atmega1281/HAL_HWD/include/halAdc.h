/******************************************************************************
\file  halAdc.h
  
\brief Declaration of hardware depended ADC interface.

\internal
  Copyright (c)Meshnetics.
  History:
    5/12/07 A. Khromykh - Created
*******************************************************************************/

#ifndef _HALHWDADC_H
#define _HALHWDADC_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <avr/io.h>
#include <types.h>
#include <halTaskManager.h>
#include <halFCPU.h>
#include <adc.h>

/******************************************************************************
                   Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializations the ADC.
\param[in]
  param - pointer to parameter structure
******************************************************************************/
void halOpenAdc(HAL_AdcParams_t *param);

/**************************************************************************//**
\brief starts convertion on the ADC channel.
\param[in]
  channel - channel number.
******************************************************************************/
void halStartAdc(uint8_t channel);

/**************************************************************************//**
\brief Closes the ADC.
******************************************************************************/
void halCloseAdc(void);

/******************************************************************************
                   Inline static functions section 
******************************************************************************/
/**************************************************************************//**
\brief SIG_ADC interrupt handler signal implementation
******************************************************************************/
INLINE void halSigAdcInterrupt(void)
{
  halPostTask3(HAL_ADC);
}

#endif /* _HALHWDADC_H */

// eof halSdc.h
