/**************************************************************************//**
  \file
    sspChallengeGen.h
  \brief
    Challenge genrator header file.
  \internal
    Copyright (c)Meshnetics.
    History:     
      07/12/07 ALuzhetsky - Created.
******************************************************************************/
#ifndef _SSPCHALLENGEGEN_H
#define _SSPCHALLENGEGEN_H

/******************************************************************************
                        Includes section.
******************************************************************************/
#include "types.h"
#include "sspCommon.h"

/******************************************************************************
                        Definitions section.
******************************************************************************/
#define CHALLENGE_SEQUENCE_SIZE 16

/******************************************************************************
                        Types' definition section.
******************************************************************************/

/******************************************************************************
                        Prototypes section.
******************************************************************************/
/*******************************************************************************
  Generates challenge.
  Parameters:
    chellange - space to store generated challenge.
  Return:
    none.
********************************************************************************/
void SSP_GenerateChallenge(uint8_t chellange[/*CHALLENGE_SEQUENCE_SIZE*/]);

#endif //_SSPCHALLENGEGEN_H

// eof sspChellenge.h

