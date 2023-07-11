/**************************************************************************//**
  \file
    tc.h
  \brief
    Security Trust Centre main header file - includes all others TC public 
    header files.
  \internal
    Copyright (c)Meshnetics.
    History:
      2008.01 - ALuzhetsky created.
******************************************************************************/
#ifndef _TCH
#define _TCH

/******************************************************************************
                             Include section.
******************************************************************************/
#include <tcAuthentic.h>
#include <tcCommon.h>
#include <tcDbg.h>
#include <tcDeviceTableCtrl.h>
#include <tcIndInput.h>
#include <tcKeyUpdate.h>
#include <tcRemove.h>
#include <tcReset.h>
#ifdef _HIGH_SECURITY
  #include <tcKeyEstablish.h>
#endif // _HIGH_SECURITY

#endif // _TCH

// eof tc.h
