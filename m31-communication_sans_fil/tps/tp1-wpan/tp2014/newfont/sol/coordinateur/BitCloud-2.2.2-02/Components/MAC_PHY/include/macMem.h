/******************************************************************************
  macMem.c
  
  Copyright (c)Meshnetics.

  Description: 
    MAC variable's memory.

  History:     
    23/04/08 A. Mandychev - Created.
******************************************************************************/

#ifndef _MACMEM_H
#define _MACMEM_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <machwiMem.h>
#include <machwdMem.h>
#include <macenvMem.h>

/******************************************************************************
                    Define(s) section
******************************************************************************/
 
/******************************************************************************
                    Types section
******************************************************************************/
typedef struct
{
  MachwiMem_t hwi;
  MachwdMem_t hwd;
  MacenvMem_t env;
} MAC_Mem_t;

/******************************************************************************
                   Extern variables section
******************************************************************************/
extern MAC_Mem_t macMem;

/******************************************************************************
                    Prototypes section
******************************************************************************/

#endif /*_MACMEM_H*/

// eof macMem.h