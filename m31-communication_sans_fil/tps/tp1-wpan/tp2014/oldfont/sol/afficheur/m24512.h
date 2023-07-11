
#ifndef M24512_H_
#define M24512_H_

#include <types.h>
#include "globaldef.h"

/*******************************************************************************
  Description:  Opens the component to use.

  Parameters:   none.

  Returns:      SUCCESS - the component is ready to been use.
                FAIL - otherwise.
*******************************************************************************/
result_t m24512__open();

/*******************************************************************************
  Description:  Performs the test if the component have completed request.

  Parameters:   none.

  Returns:      FAIL - the previous request is not completed.
                SUCCES - otherwise.
*******************************************************************************/
result_t m24512__close();

/*******************************************************************************
  Description:  Gets data from m24512 sensor.

  Parameters:   f - callback.

  Returns:      FAIL -  the previous request has not been completed yet,
                        the address of callback is 0, i2c interface is busy,
	                    there is error on i2c interface.
                SUCCESS - other case.
*******************************************************************************/
result_t m24512__getData( void (*f)(bool error, uint16_t data) );
result_t m24512__getData8( void (*f)(bool error, uint8_t data) );
result_t m24512__getDataFonts( void (*f)(bool error),uint8_t tailleFont);
result_t m24512__setData( void (*f)(bool result, uint16_t data),uint16_t datas );
result_t m24512__setTabData( void (*f)(bool result),uint8_t * datas,uint8_t lenDatas );
void m24512__initforce();
uint16_t lireEeprom(uint16_t data);
void ecrireEeprom(uint16_t adresse, uint8_t data);
uint8_t lireEeprom8(uint16_t data);
void lireEepromFonts(uint16_t data, uint8_t tailleFont);


#endif

// eof m24512.h
