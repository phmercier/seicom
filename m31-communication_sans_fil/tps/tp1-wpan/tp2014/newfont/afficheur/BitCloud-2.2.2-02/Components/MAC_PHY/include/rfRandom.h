/**************************************************************************//**
  \file
    rfRandom.h
  \brief
    Prototype of random generation function.
  \internal
   Copyright (c)Meshnetics.
    History:     
      08/04/08 A. Mandychev - Created.
******************************************************************************/

#ifndef _RFRANDOM_H
#define _RFRANDOM_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <types.h>
#include <macCommon.h>

/******************************************************************************
                    Define(s) section
******************************************************************************/
 
/******************************************************************************
                    Types section
******************************************************************************/
//! Random confirm structure. 
typedef struct 
{
  uint16_t value;
} RF_RandomConf_t;

//! Random request structure.
typedef struct
{
  //! Service field - for internal needs.
  MAC_Service_t  service;
  //! Confirm structure on RF_RandomReq.
  RF_RandomConf_t confirm;
  //! Callback on RF_RandomReq.
  void (*RF_RandomConf)(RF_RandomConf_t *conf);
} RF_RandomReq_t;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
  \brief Requests random value from RF chip. 
  \param reqParams - request parameters structure pointer. 
  \return none.
******************************************************************************/
void RF_RandomReq(RF_RandomReq_t *reqParams);

#endif /*_RFRANDOM_H*/

// eof rfRandom.h
