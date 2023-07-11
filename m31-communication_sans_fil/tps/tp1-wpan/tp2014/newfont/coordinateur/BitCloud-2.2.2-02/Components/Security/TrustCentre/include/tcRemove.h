/**************************************************************************//**
  \file
    tcRemove.h
  \brief
    Security Trust Centre remove primitive header file.
  \internal
   Copyright (c)Meshnetics.
    History:
      2008.01.20 - ALuzhetsky created.
******************************************************************************/
#ifndef _TCREMOVEH
#define _TCREMOVEH

#include <tcCommon.h>
#include <macAddr.h>

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
} TC_RemoveDeviceConf_t;

/**************************************************************************//**
  \brief TBD.

  TBD
******************************************************************************/
typedef struct PACK
{
  TC_Service_t service;
  ExtAddr_t    deviceAddr;
  ExtAddr_t    parentAddr;
  void (*TC_RemoveDeviceConf)(TC_RemoveDeviceConf_t *conf);
  TC_RemoveDeviceConf_t confirm;
} TC_RemoveDeviceReq_t;

/******************************************************************************
                             Functions prototypes section.
******************************************************************************/
void TC_RemoveDeviceReq(TC_RemoveDeviceReq_t *param);

#endif // _TCREMOVEH

// eof tcRemove.h
