/*****************************************************************************
  pdsCrcService.c

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
#include <pdsCrcService.h>
#include <pdsAuxService.h>
#include <taskManager.h>

/*******************************************************************************
It is waiting when memory will be accessible for transaction
Parameters:
  none
Returns:
  none
*******************************************************************************/
void pdsWaitMemoryFree(void)
{
  while(HAL_IsEepromBusy())
  {
    SYS_ForceRunTask();	
  }	
}

/*******************************************************************************
check crc system area.
Parameters:
  poinetr to crc structure property.
Returns:
  none.
*******************************************************************************/
void pdsCheckCrc(PDS_ServiceCrc_t *crcStation)
{ 
  uint8_t tdata = 0;	 
  HAL_EepromParams_t pdsEepromParams;	
	
  if (NULL == crcStation)
    return;	
    
  crcStation->crc = 0;	
  pdsEepromParams.address = SYSTEM_BASE_EEPROM_ADDRESS;
  pdsEepromParams.length = 1;   
  while (pdsEepromParams.address < PDS_MAX_DATA_OFFSET)
  {  	
    pdsEepromParams.data = &tdata;	
    
    pdsWaitMemoryFree();
    
    if (EEPROM_ERROR == HAL_ReadEeprom(&pdsEepromParams, NULL))
    {
      crcStation->eepromState = PDS_EEPROM_ERROR; 	
      return;
    }
    
    pdsWaitMemoryFree();
      
  	crcStation->crc += tdata;
  	pdsEepromParams.address++;
  }	
  crcStation->eepromState = PDS_SUCCESS;
}	

/*******************************************************************************
read crc from eeprom.
Parameters:
  poinetr to crc structure property.
Returns:
  none
*******************************************************************************/
void pdsReadCrc(PDS_ServiceCrc_t *crcStation)
{   
  HAL_EepromParams_t eepromParams;
  
  if (NULL == crcStation)
    return;
    
  eepromParams.address = PDS_MAX_DATA_OFFSET;
  eepromParams.length = 1;  	
  while (eepromParams.address < USER_BASE_EEPROM_ADDRESS)
  {
  	eepromParams.data = &(crcStation->crc);
  	
  	pdsWaitMemoryFree();
  	
  	if (EEPROM_ERROR == HAL_ReadEeprom(&eepromParams, NULL))
  	{
  	  crcStation->eepromState = PDS_EEPROM_ERROR;
  	  return;
  	}         
  	
  	pdsWaitMemoryFree();
  	
    if (0xFF != crcStation->crc)
    {  
      crcStation->position = eepromParams.address;
      crcStation->eepromState = PDS_SUCCESS;	
      return; 
    }      
    eepromParams.address++;
  }  
  crcStation->position = PDS_MAX_DATA_OFFSET;
  crcStation->eepromState = PDS_SUCCESS;		
}

/*******************************************************************************
write crc to eeprom. (crc area 10 byte. next byte write. previous byte delete (write 0xFF)).
crc arae is ring buffer.
Parameters:
  none.
Returns:
  operation result.
*******************************************************************************/
PDS_DataServerState_t pdsWriteCrc(void)
{
  PDS_ServiceCrc_t crcRead, crcCheck; 
  HAL_EepromParams_t eepromParams;
  uint8_t datadelete = 0xFF;
  
  pdsReadCrc(&crcRead);	
  if (PDS_EEPROM_ERROR == crcRead.eepromState)
    return PDS_EEPROM_ERROR;
    
  pdsCheckCrc(&crcCheck);
  if (PDS_EEPROM_ERROR == crcCheck.eepromState)
    return PDS_EEPROM_ERROR; 

  if (0 == (uint8_t)(crcCheck.crc + crcRead.crc))
    return PDS_SUCCESS;
     
  crcCheck.crc = 0 - crcCheck.crc;
  eepromParams.address = crcRead.position;
  eepromParams.data = &datadelete;
  eepromParams.length = 1; 
  
  pdsWaitMemoryFree();
  
  if (EEPROM_ERROR == HAL_WriteEeprom(&eepromParams, pdsDummy))
    return PDS_EEPROM_ERROR;
  
  pdsWaitMemoryFree();
      
  if (++eepromParams.address >= USER_BASE_EEPROM_ADDRESS)
    eepromParams.address = PDS_MAX_DATA_OFFSET;    
  eepromParams.data = &(crcCheck.crc);  
  
  pdsWaitMemoryFree();
  
  if (EEPROM_ERROR == HAL_WriteEeprom(&eepromParams, pdsDummy))
    return PDS_EEPROM_ERROR;
  
  pdsWaitMemoryFree();
    
  return PDS_SUCCESS;  
}

#ifdef __DBG_PDS__
  uint8_t  eepromCopy[0x400u];

  void pdsDbgReadAllEeprom(void)
  {
    HAL_EepromParams_t tempEepromParams;	
  
    tempEepromParams.address = 0;
    tempEepromParams.data = eepromCopy;
    tempEepromParams.length = 0x400u; 
  
    pdsWaitMemoryFree();
  
    if (EEPROM_ERROR == HAL_ReadEeprom(&tempEepromParams, NULL))
      return;
  
    pdsWaitMemoryFree();
  }
#endif
// eof pdsDataServer.c
