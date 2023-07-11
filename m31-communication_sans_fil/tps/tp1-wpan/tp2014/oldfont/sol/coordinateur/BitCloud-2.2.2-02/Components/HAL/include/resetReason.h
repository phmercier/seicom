/******************************************************************************/
/** \file  resetReason.h  

\brief
    Declaration of the reset reason interface.  

\internal  
  Copyright (c)Meshnetics.
  History:
    5/12/07 A. Khromykh - Created
*******************************************************************************/

#ifndef _RESETREASON_H
#define _RESETREASON_H

// \cond
/******************************************************************************
                   Define(s) section
******************************************************************************/
#define TEMP_WARM_RESET   0x12
// \endcond

/******************************************************************************
                   Types section
******************************************************************************/
/** \brief The reset reason types. */
#if defined(AT91SAM7X256)
  typedef enum
  {
  	/** \brief VDDCORE rising */ 
    POWER_ON_RESET   = 0x00,  
    /** \brief Watchdog fault occurred */
    WDT_RESET        = 0x02,  
    /** \brief Processor reset required by the software */
    WARM_RESET       = 0x03,  
    /** \brief NRST pin detected low */
    EXTERNAL_RESET   = 0x04,  
    /** \brief BrownOut reset occurred */  
    BROWN_OUT_RESET  = 0x05,  
    /** \brief unknown station */
    UNKNOWN_RESET    = 0x07     
  } HAL_ResetReason_t;
#elif defined(ATMEGA1281) || defined(ATMEGA2561)
  typedef enum
  {
  	/** \brief the supply voltage was below reset threshold. */
    POWER_ON_RESET  = 0x1,  
    /** \brief a low level was present on RESET pin. */
    EXTERNAL_RESET  = 0x2,  
    /** \brief the supply voltage was below Brown-out reset threshold. Set by fuses.*/
    BROWN_OUT_RESET = 0x4,  
    /** \brief Watch Dog Timer period expired. */
    WDT_RESET       = 0x8,  
    /** \brief MCU was reset by JTAG. */
    JTAG_RESET      = 0x10,
    /** \brief software reset. */
    WARM_RESET      = 0x11  
  } HAL_ResetReason_t;
#endif

/******************************************************************************
                   Prototypes section
******************************************************************************/
/******************************************************************************
Returns the reset reason.
Parameters:
  none.
Returns:
  The reason of reset.
  
\brief Returns the reset reason.

\return
  The reason of reset. 
******************************************************************************/
HAL_ResetReason_t HAL_ReadResetReason(void);

/**************************************************************************//**
\brief Software reset.
******************************************************************************/
void HAL_WarmReset(void);

#endif /*_RESETREASON_H*/
// resetReason.h
