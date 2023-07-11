/**
 *  Copyright (C) 2007-2008 plegal (plegal@appert44.org)
 *  @file         printCom.c
 *  @brief        Gestion liaison série
 *  @version      1.0
 *  @date         26 sept 2008 18:02:31
 *  @author       P. Le Gal
 *
 *  Fabrication   avr-gcc 4.1.3
 *  @todo         Liste des choses restant a faire.
 *  @bug          26 juin 2008 18:02:31 - Aucun pour l'instant
 *
 *  Modifications :
 *
 *  Date     Modifications
 *
 */

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#include <uart.h>
#include <stdio.h>
#include <types.h>
#include "printCom.h"


static char data2StrBuf[60];
static int stringLength = 0;



// Temporary data received via network buffer
static uint8_t tmpDataBuffer[APP_TMP_DATA_BUFFER_SIZE];
static uint8_t tmpDataBufferActualLength = 0;

// UART related variables
HAL_UartDescriptor_t appUartDescriptor;                 // UART descriptor (required by stack)
static bool uartTxBusyFlag = false;                     // UART transmission transaction status
static uint8_t uartTxBuffer[APP_UART_TX_BUFFER_SIZE];   // UART Tx buffer
static uint8_t uartRxBuffer[APP_UART_RX_BUFFER_SIZE];

static uint8_t nbByteInRxBuffer;
static bool uartRxAllowed;


void printComMsgVersion(uint8_t version, uint8_t sousVersion)
{
    stringLength = sprintf(data2StrBuf, "V%d.%02d\r\n",version,sousVersion);
    sendDataToUart((uint8_t *)data2StrBuf, stringLength );
}

void printComMsg(const char *msg)
{
    stringLength = sprintf(data2StrBuf, "%s\r\n",msg);
    sendDataToUart((uint8_t *)data2StrBuf, stringLength );
}

void printComMsgData(const char *msg, uint16_t data)
{

    stringLength = sprintf(data2StrBuf, "%s %d\r\n",msg,data);
    sendDataToUart((uint8_t *)data2StrBuf, stringLength );
}

void printComMsgDataHex8(const char *msg, uint8_t data)
{

    stringLength = sprintf(data2StrBuf, "%s 0x%02X\r\n",msg,data);
    sendDataToUart((uint8_t *)data2StrBuf, stringLength );
}

void printComMsgDataHex16(const char *msg, uint16_t data)
{

    stringLength = sprintf(data2StrBuf, "%s 0x%04X\r\n",msg,data);
    sendDataToUart((uint8_t *)data2StrBuf, stringLength );
}


void printComData16(uint16_t data2)
{

    stringLength = sprintf(data2StrBuf, "0x%04X,\r\n",data2);
    sendDataToUart((uint8_t *)data2StrBuf, stringLength );
}

void printComData8(uint8_t data2)
{
    stringLength = sprintf(data2StrBuf, "0x%02X,\r\n",data2);
    sendDataToUart((uint8_t *)data2StrBuf, stringLength );
}

void printComOoops(uint8_t id)
{

    stringLength = sprintf(data2StrBuf, "Ooops %d\r\n",id);
    sendDataToUart((uint8_t *)data2StrBuf, stringLength );
}


/********************************************************************
  Description: Init UART, register UART callbacks.

  Parameters: none.

  Returns: nothing.
********************************************************************/
void initUART(void)
{
    uartTxBusyFlag = false;

    appUartDescriptor.tty             = APP_UART_CHANNEL;
    appUartDescriptor.mode            = ASYNC;
    appUartDescriptor.baudrate        = UART_BAUDRATE_38400;
    appUartDescriptor.dataLength      = UART_DATA8;
    appUartDescriptor.parity          = UART_PARITY_NONE;
    appUartDescriptor.stopbits        = UART_STOPBIT_1;
    appUartDescriptor.rxBuffer        = &uartRxBuffer;
    appUartDescriptor.rxBufferLength  = APP_UART_RX_BUFFER_SIZE;
    appUartDescriptor.txBuffer        = NULL; // use callback mode
    appUartDescriptor.txBufferLength  = 0;
    appUartDescriptor.rxCallback      = NULL;
    appUartDescriptor.txCallback      = writeConf;
    appUartDescriptor.flowControl     = UART_FLOW_CONTROL_NONE;

    HAL_OpenUart(&appUartDescriptor);
}

/********************************************************************
  Description: Send Data To Uart

  Parameters: data - pointer to frame being sent to UART
              length - length of the frame in bytes

  Returns: nothing.
********************************************************************/
void sendDataToUart(uint8_t* data, uint8_t length)
{
    if (APP_TMP_DATA_BUFFER_SIZE > tmpDataBufferActualLength + length)
    {
        memcpy(&tmpDataBuffer[tmpDataBufferActualLength], data, length);
        tmpDataBufferActualLength += length;
    }
    if (false == uartTxBusyFlag)
    {
        writeConf();
    }
}

/********************************************************************
  Description: Writing confirmation has been received. New message can be sent.

  Parameters: none.

  Returns: nothing.
********************************************************************/
void writeConf(void)
{
    int bytesWritten;

    if (0 < tmpDataBufferActualLength)  // data waiting to be written to UART
    {
        memcpy(uartTxBuffer, tmpDataBuffer, tmpDataBufferActualLength);
        bytesWritten = HAL_WriteUart(&appUartDescriptor, uartTxBuffer, tmpDataBufferActualLength);
        if (0 < bytesWritten)
        {
            tmpDataBufferActualLength -= bytesWritten;
            uartTxBusyFlag = true;
        }
    }
    else
    {
        uartTxBusyFlag = false;
    }
}

