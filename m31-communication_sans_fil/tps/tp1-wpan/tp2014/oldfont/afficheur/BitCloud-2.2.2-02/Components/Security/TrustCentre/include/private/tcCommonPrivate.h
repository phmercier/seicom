/**************************************************************************//**
  \file
    tcCommonPrivat.h
  \brief
    Trust Centre privat common definnitions header file.
  \internal
    Copyright (c)Meshnetics.
    History:
      2007.12 - ALuzhetsky created.
******************************************************************************/
#ifndef _TCCOMMONPRIVATH
#define _TCCOMMONPRIVATH

/******************************************************************************
                             Includes section.
******************************************************************************/
#include <configServer.h>
#include <nwk.h>

/******************************************************************************
                             Definitions section.
******************************************************************************/
#define FIELD_OFFSET(struct_type, field_name) ((uint16_t) &((struct_type *)(NULL))->field_name)
#define GET_STRUCT_BY_FIELD_POINTER(struct_type, field_name, field_pointer) ((struct_type *) (((uint8_t *) field_pointer) - FIELD_OFFSET(struct_type, field_name)))

/******************************************************************************
                        Global functions prototypes section.
******************************************************************************/
NWK_SecurityIB_t* tcGetSecurityIb(void);

/******************************************************************************
                             Inline functions prototypes section.
******************************************************************************/
/**************************************************************************//**
  \brief TBD.
  
  \param TBD.
  \return TBD.
******************************************************************************/
/*INLINE uint8_t tcGetSecurityMode(void)
{
  uint8_t securityMode;

  CS_ReadParameter(CS_SECURITY_MODE_ID, (void*)&securityMode);
  return securityMode;
}*/

/**************************************************************************//**
  \brief TBD.
  
  \param TBD.
  \return TBD.
******************************************************************************/
INLINE uint8_t tcGetDeviceType(void)
{
  DeviceType_t deviceType;

  CS_ReadParameter(CS_DEVICE_TYPE_ID, (void*)&deviceType);
  return (uint8_t) deviceType;
}

#endif // _TCCOMMONPRIVATH
// eof tcCommonPrivat.h
