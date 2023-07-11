/*****************************************************************************
  apsDbg.h

  Copyright (c)Meshnetics.

  Description:
    APS Debug Module header file.
         
  History:
    09/11/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSDBG_H
#define _APSDBG_H

/******************************************************************************
                   Includes section
******************************************************************************/

/******************************************************************************
                   Define(s) section
******************************************************************************/

/******************************************************************************
                   Types section
******************************************************************************/

/******************************************************************************
                   Constants section
******************************************************************************/
typedef enum
{
  /***********************************
    APS section. Range 0x4000 - 0x4FFF
  ************************************/

  //APS Data Manager Id (0x4000 - 0x40ff)
  APSDATAMANAGER_NWKDATACONFPROCESS_0         = 0x4000,
  APS_DM_UNKNOWN_BUFFER_TYPE_0                = 0x4001,
  APS_DM_MEMORY_FAULT_0                       = 0x4002,

  //APS Security Manager Id (0x4100 - 0x41ff)
  APS_SM_OWN_EXTADDR_ERROR 							      = 0x4100,
  APS_SM_UNKNOWN_COMPONENT_ID						      = 0x4101,
  DBG_SM_MEMORY_FAULT_1,
  APS_SM_COMMAND_DATA_REQ_MEMORY_FAULT_1			= 0x4106,
  APS_SM_COMMAND_DATA_REQ_MEMORY_FAULT_2      = 0x4107,
  DBG_APS_SM_GET_PARENT_EXT_ADDR_FAULT,

  //APS Security Manager Key Establish Router (0x4200 - 0x42ff)
  DBG_APS_SM_KERO_INVALID_STATE_1             = 0x4200,
  DBG_APS_SM_KERO_INVALID_STATE_2,
  DBG_APS_SM_KERO_INVALID_STATE_3,
  DBG_APS_SM_KERO_MEMORY_FAULT_1,
  DBG_APS_SM_KERO_MEMORY_FAULT_2,


  DBG_APS_SM_KEREQ_INVALID_REQUEST,
  DBG_APS_SM_KEREQ_INVALID_STATE_1,
  DBG_APS_SM_KEREQ_INVALID_STATE_2,
  DBG_APS_SM_KEREQ_MEMORY_FAULT_1,
  DBG_APS_SM_KEREQ_MEMORY_FAULT_2,

  DBG_APS_SM_KERESP_INVALID_STATE_1, 
  DBG_APS_SM_KERESP_INVALID_STATE_2,
  DBG_APS_SM_KERESP_MEMORY_FAULT_1,
  DBG_APS_SM_KERESP_MEMORY_FAULT_2,
  DBG_APS_SM_KERESP_MEMORY_FAULT_3,
  DBG_APS_SM_KERESP_MEMORY_FAULT_4,
  DBG_APS_SM_KERESP_MEMORY_FAULT_5,
  DBG_APS_SM_KERESP_MEMORY_FAULT_6,
  DBG_APS_SM_KERESP_MEMORY_FAULT_7,
  DBG_APS_SM_KERESP_MEMORY_FAULT_8,

  DBG_APS_SM_TKR_INVALID_REQUEST,
  DBG_APS_SM_TKR_INVALID_STATE_1,
  DBG_APS_SM_TKR_INVALID_STATE_2,
  DBG_APS_SM_TKR_MEMORY_FAULT_1,
  DBG_APS_SM_TKR_MEMORY_FAULT_2,

  DBG_APS_SM_UDR_INVALID_REQUEST,
  DBG_APS_SM_UDR_INVALID_STATE_1,
  DBG_APS_SM_UDR_INVALID_STATE_2,

  DBG_APS_SM_TRANSACTION_MEMORY_FAULT_1,

  //DBG_APS_SM_ENCRYPTION_MEMORY_FAULT_1,
  //DBG_APS_SM_ENCRYPTION_MEMORY_FAULT_2,

  //DBG_APS_SM_DECRYPTION_MEMORY_FAULT_1,

  //DBG_SM_INVALID_SSP_SKKE_CONF,

  /* APS_SM_SSPE */
  DBG_APS_SM_SSPE_INVALID_BUFFER_TYPE,

  //DBG_APS_SM_EKREQ_MEMORY_FAULT_1,
  //DBG_APS_SM_EKREQ_MEMORY_FAULT_1,
  DBG_APS_SM_EKREQ_INVALID_IND,

  DBG_APS_SM_EKRESP_INVALID_RESP,
  DBG_APS_SM_EKRESP_INVALID_NWK_CONF,
  DBG_APS_SM_EKRESP_INVALID_STATE_1,
  DBG_APS_SM_EKRESP_INVALID_STATE_2,

  DBG_APS_SM_AUI_INVALID_REQ,

  //APS_DM_UNKNOWN_BUFFER_TYPE_0,
  //APS_DM_MEMORY_FAULT_0,


} ApsDbgCodeId_t;

/******************************************************************************
                   External variables section
******************************************************************************/

/******************************************************************************
                   Prototypes section
******************************************************************************/

/******************************************************************************
                   Inline static functions section 
******************************************************************************/


#endif  //#ifndef _APSDBG_H

//eof apsDbg.h
