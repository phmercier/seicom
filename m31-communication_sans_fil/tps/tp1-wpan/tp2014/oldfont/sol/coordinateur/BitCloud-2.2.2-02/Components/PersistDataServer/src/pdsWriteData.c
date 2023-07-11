/*****************************************************************************
  pdsWriteData.c

 Copyright (c)Meshnetics.

  Description:
    Periodic data save implementation

  History:
    22/01/08 A. Khromykh - Created
*****************************************************************************/
/******************************************************************************
                   Includes section
******************************************************************************/
#include <eeprom.h>
#include <appTimer.h>
#include <pdsCrcService.h>
#include <pdsAuxService.h>
#include <leds.h>

/******************************************************************************
                   Types section
******************************************************************************/
typedef struct
{
  uint16_t offset;
  uint16_t size;
} AuxType_t;

/******************************************************************************
                   Prototypes section
******************************************************************************/
/*******************************************************************************
Callback for timer and eeprom. Work with config server data step by step.
Parameters:
  none.
Returns:
  none.
*******************************************************************************/
void pdsOnTimerSave(void);

/*******************************************************************************
Look at current parameter id and set next.
Parameters:
  none.
Returns:
  none.
*******************************************************************************/
void pdsGetId(uint8_t index);

/******************************************************************************
                   Global variables section
******************************************************************************/
HAL_AppTimer_t  pdsEepromSaveServiceTimer;
PDS_CurrentState_t pdsCurrentState;
HAL_EepromParams_t pdsStackEepromParams;
uint8_t            savingIsStarted = SAVE_IS_STOPED;

PROGMEM_DECLARE(const uint8_t pdsIdForEeprom[PARAMETER_NUMBER]) =
{
 CS_UID_ID,
#ifndef _MAC2_
 CS_EXT_PANID_ID,
 CS_CHANNEL_MASK_ID,
 CS_CHANNEL_PAGE_ID,
 CS_DEVICE_TYPE_ID,
 CS_AUTONETWORK_ID,
 CS_RX_ON_WHEN_IDLE_ID,
#endif // _MAC2_
 CS_RF_TX_POWER_ID,
#ifndef _MAC2_
 CS_SOFT_RESET_REASON_ID,
#if defined(_POWER_FAILURE_)
 CS_NWK_EXT_PANID_ID,
#endif
 CS_NWK_ADDR_ID,
 CS_NWK_UNIQUE_ADDR_ID,
 CS_DTR_WAKEUP_ID,
#if defined(_POWER_FAILURE_)
 CS_NWK_LOGICAL_CHANNEL_ID,
 CS_NWK_PANID_ID,
#endif
#if defined(_SECURITY_)
 CS_NETWORK_KEY_ID,
#ifdef _HIGH_SECURITY_
 CS_LINK_KEY_ID,
 CS_MASTER_KEY_ID,
#endif
 CS_ZDO_SECURITY_STATUS_ID,
#endif
#if defined(_POWER_FAILURE_)
 CS_NEIB_TABLE_ID,
#if defined(_SECURITY_)
 CS_NWK_SECURITY_IB_ID,
#endif
#endif
 CS_APS_GROUP_TABLE_ID,
#if defined(_SECURITY_)
#ifdef _HIGH_SECURITY_
 CS_APS_KEY_PAIR_DESCRIPTORS_ID,
#endif
#endif
 NIB_INT_PARENT_SHORT,
 NIB_INT_DEPTH,
#endif //_MAC2_
};

PROGMEM_DECLARE(const AuxType_t pdsAuxArray[PARAMETER_NUMBER]) =
{
  {PDS_UID_OFFSET, sizeof(uint64_t)},                 // CS_UID_ID
#ifndef _MAC2_
  {PDS_EXT_PANID_OFFSET, sizeof(uint64_t)},           // CS_EXT_PANID_ID
  {PDS_CHANNEL_MASK_OFFSET, sizeof(uint32_t)},        // CS_CHANNEL_MASK_ID
  {PDS_CHANNEL_PAGE_OFFSET, sizeof(uint8_t)},         // CS_CHANNEL_PAGE_ID
  {PDS_DEVICE_TYPE_OFFSET, sizeof(DeviceType_t)},     // CS_DEVICE_TYPE_ID
  {PDS_AUTONETWORK_OFFSET, sizeof(bool)},             // CS_AUTONETWORK_ID
  {PDS_RX_ON_WHEN_IDLE_OFFSET, sizeof(bool)},         // CS_RX_ON_WHEN_IDLE_ID
#endif //_MAC2_
  {PDS_RF_TX_POWER_OFFSET, sizeof(int8_t)},          // CS_RF_TX_POWER_ID
#ifndef _MAC2_
  {PDS_SOFT_RESET_REASON_OFFSET, sizeof(uint8_t)},    // CS_SOFT_RESET_REASON_ID
#if defined(_POWER_FAILURE_)
  {PDS_NWK_EXT_PANID_OFFSET, sizeof(uint64_t)},       // CS_NWK_EXT_PANID_ID
#endif
  {PDS_NWK_ADDR_OFFSET, sizeof(ShortAddr_t)},
  {PDS_NWK_UNIQUE_ADDR_OFFSET, sizeof(bool)},
  {PDS_DTR_WAKEUP_OFFSET, sizeof(bool)},              // CS_DTR_WAKEUP_ID
#if defined(_POWER_FAILURE_)
  {PDS_NWK_LOGICAL_CHANNEL_OFFSET, sizeof(uint8_t)},  // CS_NWK_LOGICAL_CHANNEL_ID
  {PDS_NWK_PANID_OFFSET, sizeof(uint16_t)},           // CS_NWK_PANID_ID
#endif
#if defined(_SECURITY_)
  {PDS_NETWORK_KEY_OFFSET, SECURITY_KEY_SIZE},
#ifdef _HIGH_SECURITY_
  {PDS_LINK_KEY_OFFSET, SECURITY_KEY_SIZE},
  {PDS_MASTER_KEY_OFFSET, SECURITY_KEY_SIZE},
#endif
  {PDS_ZDO_SECURITY_STATUS_OFFSET, sizeof(uint8_t)},  // CS_ZDO_SECURITY_STATUS_ID
#endif
#if defined(_POWER_FAILURE_)
  {PDS_NEIB_TABLE_OFFSET, (CS_NEIB_TABLE_SIZE * sizeof(Neib_t))},
#if defined(_SECURITY_)
  {PDS_NWK_SECURITY_IB_OFFSET, sizeof(NWK_SecurityIB_t)},
#endif
#endif
  {PDS_APS_GROUP_TABLE_OFFSET, (CS_APS_GROUP_TABLE_SIZEOF * sizeof(uint8_t))},
#if defined(_SECURITY_)
#ifdef _HIGH_SECURITY_
  {PDS_APS_KEY_PAIR_DESCRIPTORS_OFFSET, (CS_APS_KEY_PAIR_DESCRIPTORS_AMOUNT * sizeof(ApsKeyPairDescriptor_t))},
#endif
#endif
  {PDS_PARENT_ADDR_OFFSET, sizeof(uint16_t)},
  {PDS_CURRENT_DEPTH_OFFSET, sizeof(uint8_t)},
#endif //_MAC2_
};


/*******************************************************************************
Start global data save timer.
Parameters:
  callback - The callback method starts when timer fired
  typeInterval - set timer interval. Must be chosen from:
     PDS_LONG_INTERVAL  - 5 minutes
     PDS_SHORT_INTERVAL - 50 msec
Returns:
  none.
*******************************************************************************/
void pdsStartPdsTimer(void (*callback)(void), uint8_t typeInterval)
{
  pdsEepromSaveServiceTimer.callback = callback;
  if (PDS_LONG_INTERVAL ==  typeInterval)
    pdsEepromSaveServiceTimer.interval = STORE_TIMER_TIMEOUT;
  else
    pdsEepromSaveServiceTimer.interval = SHORT_TIMEOUT;
  pdsEepromSaveServiceTimer.mode = TIMER_ONE_SHOT_MODE;
  HAL_StartAppTimer(&pdsEepromSaveServiceTimer);
}

/*******************************************************************************
Start server work.
Parameters:
  none.
Returns:
  none.
*******************************************************************************/
void pdsStartPersistServer(void)
{
  pdsCurrentState.currentAction = PDS_CS_PARAMETER;
  pdsStartPdsTimer(pdsOnTimerSave, PDS_LONG_INTERVAL);
}

bool pdsCsVariableCompare(void)
{
  static PDS_Default_t fromMemory;
  PDS_Default_t fromEeprom;

  pdsStackEepromParams.data = &(fromEeprom.uint8);
  CS_ReadParameter(pdsCurrentState.id, &fromMemory);

  pdsWaitMemoryFree();

  HAL_ReadEeprom(&pdsStackEepromParams, NULL);

  pdsWaitMemoryFree();

  if (0 != memcmp(&(fromMemory.uint8), &(fromEeprom.uint8), pdsStackEepromParams.length)) /* equal */
  {
    pdsStackEepromParams.data = &(fromMemory.uint8);
    HAL_WriteEeprom(&pdsStackEepromParams, pdsOnTimerSave);
    return true;
  }

  return false;
}

bool pdsCsMemoryCompare(void)
{
  uint8_t *fromMemory;
  uint8_t fromEeprom;
  uint16_t length;
  uint16_t address;

  pdsStackEepromParams.data = &fromEeprom;
  length = pdsStackEepromParams.length;
  address = pdsStackEepromParams.address;
  pdsStackEepromParams.length = 1;
  CS_GetMemory(pdsCurrentState.id, (void *)(&fromMemory));

  uint16_t inc;
  for (inc = 0; inc < length; inc++)
  {
  	pdsWaitMemoryFree();

    HAL_ReadEeprom(&pdsStackEepromParams, NULL);

    pdsWaitMemoryFree();

    if (fromMemory[inc] != fromEeprom)
    {
      pdsStackEepromParams.data = fromMemory;
      pdsStackEepromParams.length = length;
      pdsStackEepromParams.address = address;
      HAL_WriteEeprom(&pdsStackEepromParams, pdsOnTimerSave);
      return true;
    }

    pdsStackEepromParams.address++;
  }
  return false;
}

#ifndef _MAC2_
  bool pdsNwkMemoryCompare(void)
  {
    uint8_t * fromMemory = NULL;
    uint8_t fromEeprom;
    uint16_t length;
    uint16_t address;
    NWK_GetReq_t getReq;

    pdsStackEepromParams.data = &fromEeprom;
    length = pdsStackEepromParams.length;
    address = pdsStackEepromParams.address;
    pdsStackEepromParams.length = 1;
    getReq .nibAttribute = pdsCurrentState.id;
    NWK_GetReq(&getReq);
    fromMemory = (uint8_t *)(getReq.confirm.nibAttributeValue);

    if (NULL == fromMemory)
      return false;

    uint16_t inc;
    for (inc = 0; inc < length; inc++)
    {
  	  pdsWaitMemoryFree();

      HAL_ReadEeprom(&pdsStackEepromParams, NULL);

      pdsWaitMemoryFree();

      if (fromMemory[inc] != fromEeprom)
      {
        pdsStackEepromParams.data = fromMemory;
        pdsStackEepromParams.length = length;
        pdsStackEepromParams.address = address;
        HAL_WriteEeprom(&pdsStackEepromParams, pdsOnTimerSave);
        return true;
      }
      pdsStackEepromParams.address++;
    }
    return false;
  }
#endif // _MAC2_

/*******************************************************************************
Read data from eeprom, read data from config server.
If they are not equally starts saving.
Parameters:
  none.
Returns:
  true - saving starts
  false - data equally
*******************************************************************************/
bool pdsNeedSaveParam(void)
{
  static uint8_t index = 0;

  pdsGetId(index);

  if (PDS_CS_PARAMETER == pdsCurrentState.currentAction)
  {
    if (pdsCsVariableCompare())
      return true;
  }

  if (PDS_CS_MEMORY == pdsCurrentState.currentAction)
  {
  	if (pdsCsMemoryCompare())
  	  return true;
  }

  if (PDS_NWK_MEMORY == pdsCurrentState.currentAction)
  {
  	#ifndef _MAC2_
      if (pdsNwkMemoryCompare())
  	    return true;
  	#endif // _MAC2_
  }

  index++;

  if (PARAMETER_NUMBER_CS == index)
    pdsCurrentState.currentAction = PDS_CS_MEMORY;

  if (MEMORY_NUMBER_CS == index)
    pdsCurrentState.currentAction = PDS_NWK_MEMORY;

  if (PARAMETER_NUMBER == index)
  {
  	index = 0;
    pdsCurrentState.currentAction = PDS_STOP_SAVE;
    return true;
  }

  return false;
}

/*******************************************************************************
Callback for timer and eeprom. Work with config server data step by step.
Parameters:
  none.
Returns:
  none.
*******************************************************************************/
void pdsOnTimerSave(void)
{
#ifdef USE_LED
  BSP_OnLed(LED_YELLOW);
#endif
  savingIsStarted = SAVE_IS_STARTED;

  while (!pdsNeedSaveParam());

  if (PDS_STOP_SAVE == pdsCurrentState.currentAction)
  {
  	if (PDS_EEPROM_ERROR == pdsWriteCrc())
  	{
  	  pdsStartPdsTimer(pdsOnTimerSave, PDS_SHORT_INTERVAL);
  	}
  	else
  	{
  	  pdsStartPersistServer();

#ifdef USE_LED
  	  BSP_OffLed(LED_YELLOW);
#endif

      savingIsStarted = SAVE_IS_STOPED;
  	}
  }
}

/*******************************************************************************
Look at current parameter id and set next.
Parameters:
  none.
Returns:
  none.
*******************************************************************************/
void pdsGetId(uint8_t index)
{
  AuxType_t auxTmp;

  memcpy_P(&(pdsCurrentState.id), &pdsIdForEeprom[index], sizeof(uint8_t));
  memcpy_P(&auxTmp, &pdsAuxArray[index], sizeof(AuxType_t));
  pdsStackEepromParams.address = auxTmp.offset;
  pdsStackEepromParams.length = auxTmp.size;
}

// eof pdsDataServer.c
