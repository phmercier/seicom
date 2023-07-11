/*********************************************************************************
  dbg.h 
  Copyright (c)Meshnetics.

  Description:
    A module should use the SYS_writeLog define and should not use writeLog() directly
    Module should define own #define on SYS_WriteLog() to have an opportunity
    to turn on/off logging by setting special define during compilation

    The LOG is turned on by the SYS_LOG_ON define defined in Makefile
          
  History:
    29/05/07 D. Ovechkin - Created
**********************************************************************************/
#ifndef _DBG_H
#define _DBG_H

#include <types.h>

typedef enum
{
  SYS_LOG_LEVEL_1 = 1, // The highest level, all levels bellow are included
  SYS_LOG_LEVEL_2,    // different auxiliary events related with network, 
                      // starting, stopping, resetting layers
  SYS_LOG_LEVEL_3,    // Actions related with children and power management 
  SYS_LOG_LEVEL_4,    // Data request & data indication on all layers
  SYS_LOG_LEVEL_5,    // Starting, stopping, recovering network
  SYS_LOG_LEVEL_6,    // Can be used only during debugging and after should be removed
  SYS_LOG_LEVEL_7     // Can be used only user
} SYS_LogLevel_t;

#ifdef SYS_LOG_ON

/*********************************************************************************
  Write log information to defined destination. The destination can be
  UART, EEPROM, Ethernet... The destination is determed dy the define 
  during compilation
  Parameters: 
    moduleID - Module Id
    logID    - log Id
    extraParamsAmount - number of extra bytes describing parameters of log message
    ... - any parameters determing by caller
  Returns: 
    SUCCESSE - log is accepted
    FAIL     - no enough memory for buffering
**********************************************************************************/
extern void SYS_WriteLog(uint8_t message, SYS_LogLevel_t level);
extern void SYS_InitLog();
#else
inline void SYS_WriteLog(uint8_t message, SYS_LogLevel_t level);
inline void SYS_InitLog();
#endif


/*********************************************************************************
 ASSERT is used for debugging wrong conditions
 Dbg codes are in each layers.
*********************************************************************************/
#ifdef SYS_ASSERT_ON
#include <halAssert.h>

extern void assert(bool condition, uint16_t dbgCode);


// Inline Assert
/*
  dbgCode ranges
  0x1000 - 0x1fff - MAC
  0x2000 - 0x2fff - HAL
  0x3000 - 0x3fff - NWK
  0x4000 - 0x4fff - APS
  0x5000 - 0x5fff - ZDO
  0x7000 - 0x7fff - SSP/TC
  0xf000 - 0xfffe - APL
*/
#define ASSERT(condition, dbgCode)     halAssert(condition, dbgCode);

#else
#define ASSERT(condition, dbgCode) {if(condition){}}
#define assert(condition, dbgCode) {if(condition){}}
#endif

#endif 
//end of dbg.h

