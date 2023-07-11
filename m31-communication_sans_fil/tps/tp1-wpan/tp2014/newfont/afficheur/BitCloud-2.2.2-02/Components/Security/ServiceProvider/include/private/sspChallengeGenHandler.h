/**************************************************************************//**
  \file
    sspChallengeGenHandler.h
  \brief
    Challenge generator handler header file.
  \internal
    Copyright (c)Meshnetics.
    History:     
      17/12/07 ALuzhetsky - Created.
******************************************************************************/
#ifndef _SSPCHALLENGEGENHANDLER_H
#define _SSPCHALLENGEGENHANDLER_H

/******************************************************************************
                        Includes section.
******************************************************************************/

/******************************************************************************
                        Definition section.
******************************************************************************/

/******************************************************************************
                        Prototypes section.
******************************************************************************/
/*******************************************************************************
  Resets Security Service Provider entity.
  Parameters:
    challenge - pointer to the memory for saving generated challenge.
  Return:
    none.
********************************************************************************/
void sspGenerateChallengeHandler(uint8_t chellange[/*CHALLENGE_SEQUENCE_SIZE*/]);
#endif //_SSPCHALLENGEGENHANDLER_H

// eof sspChallengeGenHandler.h

