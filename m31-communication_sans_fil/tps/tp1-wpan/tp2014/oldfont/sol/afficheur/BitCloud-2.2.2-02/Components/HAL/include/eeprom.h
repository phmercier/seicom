/******************************************************************************/
/** \file  eeprom.h    

\brief
    Provides access to EEPROM.

\internal  
  Copyright (c)Meshnetics.
  History:
    5/12/07 A. Khromykh - Created
*******************************************************************************/

#ifndef _EEPROM_H
#define _EEPROM_H

// \cond
/******************************************************************************
                   Includes section
******************************************************************************/
#include <types.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
#if defined(AT91SAM7X256)
  #define EEPROM_DATA_MEMORY_SIZE 0x400u
#elif defined(ATMEGA1281) || defined(ATMEGA2561)
  #define EEPROM_DATA_MEMORY_SIZE 0x1000u
  //#define USE_EEPROM_FOR_OLD_PERSIST_SERVER
#endif
// \endcond

/******************************************************************************
                   Types section
******************************************************************************/
/**************************************************************************//**
\brief eeprom access control structure
******************************************************************************/
typedef struct
{
  /** \brief EEPROM address */
  uint16_t address;        
  /** \brief pointer to data memory */
  uint8_t *data;           
  /** \brief number of bytes */
  uint16_t length;   
} HAL_EepromParams_t;

/******************************************************************************
                   Prototypes section
******************************************************************************/
/******************************************************************************
\brief Reads a number of bytes defined by HAL_EepromParams_t from the EEPROM.
\param[in]
  param - address of HAL_EepromParams_t structure. \n
  fields of structure set by user: \n 
  address - eeprom address \n
  data - pointer to data memory \n
  length - number of bytes        
\param[in]  
  readDone - pointer to the function that will notify about reading completion.
\return
  Number of bytes that were read from EEPROM - success, \n
  -1 - the number of bytes to write is too large, \n  
  -2 - the previous EEPROM request is not completed yet.           
******************************************************************************/
#if defined(USE_EEPROM_FOR_OLD_PERSIST_SERVER) && (defined(ATMEGA1281) || defined(ATMEGA2561))
  int HAL_ReadEeprom(HAL_EepromParams_t *params);
#else
  int HAL_ReadEeprom(HAL_EepromParams_t *params, void (*readDone)());
#endif

/******************************************************************************
\brief Writes a number of bytes defined by HAL_EepromParams_t to EEPROM.
By writeDone parameter user can control if write operation will be asynchronous 
or synchronous.
\param[in]
  param - address of HAL_EepromParams_t structure. \n
  fields of structure set by user: \n 
  address - eeprom address \n
  data - pointer to data memory \n
  length - number of bytes
\param[in]
  writeDone - pointer to the function that will notify about reading completion. \n
  Only for avr: \n 
  if writeDone is 0 write operation will be synchronous.
\return
  Number of bytes that were written to EEPROM - success (synchronous operation), \n
  0 - success  (asynchronous operation), \n
  -1 - the number of bytes to write is too large, \n  
  -2 - the previous EEPROM request is not completed yet.
******************************************************************************/
int HAL_WriteEeprom(HAL_EepromParams_t *params, void (*writeDone)());

/**************************************************************************//**
\brief Checks the eeprom state.

\return
  true  - eeprom is busy; \n
  false - eeprom is free;       
******************************************************************************/
bool HAL_IsEepromBusy(void);

#endif /*_EEPROM_H*/

//eof eeprom.h
