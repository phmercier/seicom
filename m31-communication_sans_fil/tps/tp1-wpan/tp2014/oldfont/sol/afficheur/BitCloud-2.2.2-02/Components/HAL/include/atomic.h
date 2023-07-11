/**************************************************************************//**
\file  atomic.h

\brief Header file defines the defines for working with atomic sections

\internal
  Copyright (c)Meshnetics.

  Description: 
    Declaration of atomic sections.
  History:     
    20/08/07 A. Khromykh - Created
******************************************************************************/

#ifndef _ATOMIC_H
#define _ATOMIC_H

/******************************************************************************
                   Includes section
******************************************************************************/
#if defined(AT91SAM7X256)
  #include <inttypes.h>
#elif defined(ATMEGA1281) || defined(ATMEGA2561)
  #include <halAtomic.h>
#endif

#if defined(AT91SAM7X256)
/******************************************************************************
                   Types section
******************************************************************************/
typedef  uint32_t atomic_t;

/******************************************************************************
                   Prototypes section
******************************************************************************/
void vPortEnterCritical(void);
void vPortExitCritical(void);

/******************************************************************************
                   Inline static functions section 
******************************************************************************/
/**************************************************************************//**
 Disables global interrupt. Enter atomic section.
******************************************************************************/
void halStartAtomic(atomic_t volatile *pAtomic);

/******************************************************************************
 Exit atomic section
******************************************************************************/
void halEndAtomic(atomic_t volatile *pAtomic);
#endif

#if defined(AT91SAM7X256)
  //! Marks the begin of atomic section
  #define ATOMIC_SECTION_ENTER  {volatile atomic_t __atomic; halStartAtomic(&__atomic);
  //! Marks the end of atomic section
  #define ATOMIC_SECTION_LEAVE  halEndAtomic(&__atomic);}
#elif defined(ATMEGA1281) || defined(ATMEGA2561)
  //! Marks the begin of atomic section
  #define ATOMIC_SECTION_ENTER {atomic_t __atomic = halStartAtomic();
  //! Marks the end of atomic section
  #define ATOMIC_SECTION_LEAVE halEndAtomic(__atomic);}
#endif

#endif
// eof atomic.h
