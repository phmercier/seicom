/*****************************************************************************
  pdsDataServer.c

  Copyright (c)Meshnetics.
  
  Description:
    Persistence Data Server implementation
    
  History:
    22/01/08 A. Khromykh - Created
*****************************************************************************/
/******************************************************************************
                   Includes section
******************************************************************************/ 
#include <eeprom.h>
#include <appTimer.h>
#include <pdsDataServer.h>
#include <pdsCrcService.h>
#include <pdsAuxService.h>
#include <leds.h>

/******************************************************************************
                   Prototypes section
******************************************************************************/
/*******************************************************************************
Read data from eeprom and set to config server.
Parameters:
  none.
Returns:
  operation result.
*******************************************************************************/
PDS_DataServerState_t PDS_ReadParamFromEeprom(void);

/*******************************************************************************
set default value system area and check new crc
Parameters:
  none.
Returns:
  operations result.
*******************************************************************************/
PDS_DataServerState_t PDS_SetToDefault(void);

/*******************************************************************************
Look at current parameter id and set next. 
Parameters:
  none. 
Returns:
  none.
*******************************************************************************/
void pdsGetId(uint8_t index);

/*******************************************************************************
Start server work.
Parameters:
  none.
Returns:
  none.
*******************************************************************************/
void pdsStartPersistServer(void);

/*******************************************************************************
Callback for timer and eeprom. Work with config server data step by step.
Parameters:
  none. 
Returns:
  none.
*******************************************************************************/
void pdsOnTimerSave(void);

/******************************************************************************
                   External global variables section
******************************************************************************/
extern PDS_CurrentState_t pdsCurrentState;
extern HAL_EepromParams_t pdsStackEepromParams;
extern HAL_AppTimer_t     pdsEepromSaveServiceTimer;
extern uint8_t            savingIsStarted;

/******************************************************************************
                   Implementations section
******************************************************************************/
/*******************************************************************************
Read and check crc system area.
Parameters:
  none.
Returns:
  operation result.
*******************************************************************************/
PDS_DataServerState_t PDS_Init(void)
{    
  PDS_ServiceCrc_t crcRead, crcCheck; 

#ifdef USE_LED  
  BSP_OpenLeds();
#endif
     
  pdsCheckCrc(&crcCheck);
  if (PDS_EEPROM_ERROR == crcCheck.eepromState)
    return PDS_EEPROM_ERROR;  
 	
  pdsReadCrc(&crcRead);
  if (PDS_EEPROM_ERROR == crcRead.eepromState)
    return PDS_EEPROM_ERROR;
         	  
  if (0x00 == (uint8_t)(crcCheck.crc + crcRead.crc))  
  {
  	if (PDS_EEPROM_ERROR == PDS_ReadParamFromEeprom())
  	{
  	  return PDS_EEPROM_ERROR;
  	}
  	else
  	{
  	  pdsStartPersistServer();
  	  return PDS_SUCCESS;
  	}
  }  
  else   
  {
  	if (PDS_EEPROM_ERROR == PDS_SetToDefault())
  	{
      return PDS_EEPROM_ERROR;
  	}  
    else
    {  
      pdsStartPersistServer();	
      return PDS_CRC_ERROR;
    }  
  }                
}

/*******************************************************************************
Read data from eeprom and set to config server.
Parameters:
  none.
Returns:
  operation result.
*******************************************************************************/
PDS_DataServerState_t PDS_ReadParamFromEeprom(void)
{
  PDS_Default_t memory;	
  uint8_t index = 0;
  #ifndef _MAC2_
    NWK_GetReq_t getReq;
  #endif // _MAC2_
	
  pdsCurrentState.currentAction = PDS_CS_PARAMETER; 	
	
  while (PARAMETER_NUMBER > index)			  
  {  	
  	pdsGetId(index);
  	  
  	if (PDS_CS_PARAMETER == pdsCurrentState.currentAction)  	
  	  pdsStackEepromParams.data = &(memory.uint8); 
  	
  	if (PDS_CS_MEMORY == pdsCurrentState.currentAction)
  	  CS_GetMemory(pdsCurrentState.id, (void *)(&(pdsStackEepromParams.data)));
  	
  	if (PDS_NWK_MEMORY == pdsCurrentState.currentAction)
  	{
  	  #ifndef _MAC2_	
  	    getReq.nibAttribute = pdsCurrentState.id;
  	    NWK_GetReq(&getReq);
  	    pdsStackEepromParams.data = getReq.confirm.nibAttributeValue;
  	  #endif //_MAC2_ 
  	}      
  	
  	pdsWaitMemoryFree();
  	
  	if (EEPROM_ERROR == HAL_ReadEeprom(&pdsStackEepromParams, NULL))  	
      return PDS_EEPROM_ERROR;
  	
  	pdsWaitMemoryFree();
  	
  	if (PDS_CS_PARAMETER == pdsCurrentState.currentAction)
      CS_WriteParameter(pdsCurrentState.id, &(memory.uint8));	

  	index++;  	   
  	
  	if (PARAMETER_NUMBER_CS == index)
  	  pdsCurrentState.currentAction = PDS_CS_MEMORY;
  	  
  	if (MEMORY_NUMBER_CS == index)
  	  pdsCurrentState.currentAction = PDS_NWK_MEMORY;  
  }	
  
  return PDS_SUCCESS;
}

/*******************************************************************************
set default value system area and check new crc
Parameters:
  none.
Returns:
  operations result.
*******************************************************************************/
PDS_DataServerState_t PDS_SetToDefault(void)
{
  PDS_Default_t listData;  
  PDS_ServiceCrc_t crcCheck;	
  uint8_t index = 0;
  
  CS_PdsDefaultValue();  
  while (index < PARAMETER_NUMBER_CS)
  {
    pdsGetId(index);    
    CS_ReadParameter(pdsCurrentState.id, &listData);
    pdsStackEepromParams.data = &(listData.uint8);
    
    pdsWaitMemoryFree();
    
    if (EEPROM_ERROR == HAL_WriteEeprom(&pdsStackEepromParams, pdsDummy))
      return PDS_EEPROM_ERROR;
    
    pdsWaitMemoryFree();
      
    index++;    
  }
    
  memset(listData.resetCRC, 0xFF, PDS_CRC_AREA); 
  pdsStackEepromParams.data = listData.resetCRC;   	  
  pdsStackEepromParams.address = PDS_MAX_DATA_OFFSET;
  pdsStackEepromParams.length = PDS_CRC_AREA;
  
  pdsWaitMemoryFree();
      
  if (EEPROM_ERROR == HAL_WriteEeprom(&pdsStackEepromParams, pdsDummy))
    return PDS_EEPROM_ERROR; 
  
  pdsWaitMemoryFree();
  
  pdsCheckCrc(&crcCheck);
  if (PDS_EEPROM_ERROR == crcCheck.eepromState)
    return PDS_EEPROM_ERROR; 
     
  crcCheck.crc = 0 - crcCheck.crc;
  pdsStackEepromParams.address = PDS_MAX_DATA_OFFSET;
  pdsStackEepromParams.data = &crcCheck.crc;
  pdsStackEepromParams.length = 1;
  
  pdsWaitMemoryFree();
   
  if (EEPROM_ERROR == HAL_WriteEeprom(&pdsStackEepromParams, pdsDummy))
    return PDS_EEPROM_ERROR;
  
  pdsWaitMemoryFree();
            
  return PDS_SUCCESS;  
}

/*******************************************************************************
Data save to eeprom immediately
Parameters:
  none
Returns:
  none
*******************************************************************************/
void PDS_FlushData(void)
{
  if (SAVE_IS_STOPED == savingIsStarted)  
  { /* Data isn't saving now. Timer is working. */
  	HAL_StopAppTimer(&pdsEepromSaveServiceTimer);
  	pdsOnTimerSave();
  }	/* Data isn't saving now. Timer is working. */
  
  while(SAVE_IS_STARTED == savingIsStarted)
  {
    SYS_ForceRunTask();	
  }
}

/*******************************************************************************
Dummy function for callback. 
*******************************************************************************/
void pdsDummy(void)
{}

/*******************************************************************************
Read data from user area.
Parameters:
  offset - data offset
  data - pointer to configserver data area
  length - data length
Returns:
  operations result.
*******************************************************************************/
PDS_DataServerState_t PDS_ReadUserData(uint16_t offset, uint8_t *data, uint16_t length, void (*callback)(void))
{
  HAL_EepromParams_t pdsUserEepromParams;
   	
  pdsUserEepromParams.address = USER_BASE_EEPROM_ADDRESS + offset;
  pdsUserEepromParams.length = length;
  pdsUserEepromParams.data = data;
  
  while(SAVE_IS_STARTED == savingIsStarted)
  {
    SYS_ForceRunTask();	
  }
  
  if (NULL == callback)
    callback = pdsDummy;
  
  pdsWaitMemoryFree();
  
  if (EEPROM_ERROR == HAL_ReadEeprom(&pdsUserEepromParams, callback))
    return PDS_EEPROM_ERROR;
    
  if (callback == pdsDummy)
  {
    pdsWaitMemoryFree();
  }
    
  return PDS_SUCCESS;
}

/*******************************************************************************
Write data to user area.
Parameters:
  offset - data offset
  data - pointer to configserver data area
  length - data length
Returns:
  operations result.
*******************************************************************************/
PDS_DataServerState_t PDS_WriteUserData(uint16_t offset, uint8_t *data, uint16_t length, void (*callback)(void))
{  	
  HAL_EepromParams_t pdsUserEepromParams;
	
  pdsUserEepromParams.address = USER_BASE_EEPROM_ADDRESS + offset;
  pdsUserEepromParams.length = length;
  pdsUserEepromParams.data = data;
  
  while(SAVE_IS_STARTED == savingIsStarted)
  {
    SYS_ForceRunTask();	
  }
  
  if (NULL == callback)
    callback = pdsDummy;
  
  pdsWaitMemoryFree();  	  
  
  if (EEPROM_ERROR == HAL_WriteEeprom(&pdsUserEepromParams, callback))
    return PDS_EEPROM_ERROR;
  
  if (callback == pdsDummy)
  {
    pdsWaitMemoryFree();
  }
          
  return PDS_SUCCESS;	
}

// eof pdsDataServer.c
