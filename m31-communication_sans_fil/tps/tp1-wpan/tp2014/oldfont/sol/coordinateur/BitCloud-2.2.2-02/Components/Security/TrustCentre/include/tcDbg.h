/**************************************************************************//**
  \file
    tcTaskManager.h
  \brief
    Security Trust Centre debug header file.
  \internal
    Copyright (c)Meshnetics.
    History:
      2007.12 - ALuzhetsky created.
******************************************************************************/
#ifndef _TCDBGH
#define _TCDBGH

/******************************************************************************
                             Includes section.
******************************************************************************/
#include <dbg.h>

/******************************************************************************
                             Types section.
******************************************************************************/
/**************************************************************************//**
  \brief Trust Centre debug codes declaration.

   These codes are used for debuging.
******************************************************************************/
typedef enum
{
  TCAUTHENTICHANDLERC_APSUPDATEDEVICEINDICATION_01    = 0x7000,
  TCAUTHENTICHANDLERC_APSUPDATEDEVICEINDICATION_02    = 0x7001,
  TCAUTHENTICHANDLERC_TCAUTHENTICTASKHANDLER_01       = 0x7002,
  TCKEYUPDATEHANDLER_TCKEYUPDATETASKHANDLER_00        = 0x7003,
  TCAUTHENTICHANDLERC_APSREMOVEDEVICECONF_00          = 0x7004,
  TCKEYUPDATEHANDLERC_ENDUPDATENETWORKKEYOPERATION_00 = 0x7005,
} TcDbgCodeId_t;
#endif // _TCDBGH

// eof tcDbg.h
