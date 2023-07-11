/**************************************************************************//**
  \file
    tcKeyUpdate.h
  \brief
    Security Trust Centre key update primitive header file.
  \internal
    Copyright (c)Meshnetics.
    History:
      2007.12 - ALuzhetsky created.
******************************************************************************/
#ifndef _TCKEYUPDATEH
#define _TCKEYUPDATEH

/******************************************************************************
                             Includes section.
******************************************************************************/
#include <types.h>
#include <tcCommon.h>
#include <tcKeyUpdate.h>

/******************************************************************************
                             Types section.
******************************************************************************/

/**************************************************************************//**
  \brief TBD.

  TBD
******************************************************************************/
typedef struct PACK
{
  uint8_t status;
} TC_KeyUpdateConf_t;

/**************************************************************************//**
  \brief TBD.

  TBD
******************************************************************************/
typedef struct PACK
{
  TC_Service_t service;
  void (*TC_KeyUpdateConf)(TC_KeyUpdateConf_t *conf);
  TC_KeyUpdateConf_t confirm;
} TC_KeyUpdateReq_t;

/******************************************************************************
                             Functions prototypes section.
******************************************************************************/
/**************************************************************************//**
  \brief Peforms trust centre key updating procedure in the network.
  
  \param reqParam - parameters of operation (for detailed description refer to 
                    TC_KeyUpdateReq_t type declaration).
  \return none.
******************************************************************************/
void TC_KeyUpdateReq(TC_KeyUpdateReq_t *reqParam);

#endif //_TCKEYUPDATEH
// eof tcKeyUpdate.h
