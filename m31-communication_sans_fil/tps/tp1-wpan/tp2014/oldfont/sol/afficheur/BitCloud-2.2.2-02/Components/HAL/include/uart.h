/******************************************************************************/
/** \file  uart.h
  
\brief
    Declaration of the uart interface.

\internal
  Copyright (c)Meshnetics.      
  History:
    22/08/07 A. Khromykh - Created
*******************************************************************************/

#ifndef _UART_H
#define _UART_H

/******************************************************************************
                   Includes section
******************************************************************************/
// \cond
#include <halUart.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
#define UART_FLOW_CONTROL_NONE 0
#define UART_FLOW_CONTROL_HARDWARE 1
#define UART_DTR_CONTROL 2

#ifndef NUM_USART_CHANNELS
  #define NUM_USART_CHANNELS 2 // Number USART channels
#endif
  
#if defined(ATMEGA1281) || defined(ATMEGA2561)
  // this define is used only by HAL.
  #define USART_SPI_MODE 16
#endif
// \endcond

/******************************************************************************
                   Types section
******************************************************************************/
/** \brief Uart descriptor*/
typedef struct
{
  /** \brief tty - One of the defines UART_CHANNEL_0 or UART_CHANNEL_1.    
  Which defines a number of UART. */
  uint8_t tty;
  /** \brief Sets synchronous or asynchronous routine. \n
  Must be chosen from: \n
    ASYNC \n
    SYNC  \n */
  UartMode_t mode;
  /** \brief baudrate - UART baud rate. Must be chosen from: \n
    UART_BAUDRATE_1200  \n
    UART_BAUDRATE_2400  \n
    UART_BAUDRATE_4800  \n
    UART_BAUDRATE_9600 \n
    UART_BAUDRATE_19200 \n
    UART_BAUDRATE_38400 \n
    UART_SYNC_BAUDRATE_1200 \n
    UART_SYNC_BAUDRATE_2400 \n
    UART_SYNC_BAUDRATE_4800 \n
    UART_SYNC_BAUDRATE_9600 \n
    UART_SYNC_BAUDRATE_38400 \n
    UART_SYNC_BAUDRATE_57600 \n
    UART_SYNC_BAUDRATE_115200  \n */ 
  UartBaudRate_t baudrate;  
  /** \brief data -  UART data length. Must be chosen from: \n
    UART_DATA5 \n
    UART_DATA6 \n
    UART_DATA7 \n
    UART_DATA8 \n */
  UartData_t dataLength;          
  /** \brief parity -  UART parity mode. Must be chosen from: \n
    UART_PARITY_NONE \n
    UART_PARITY_EVEN \n
    UART_PARITY_ODD \n  */
  UartParity_t parity;       
  /** \brief stopbits - UART stop bits number. Must be chosen from: \n
    UART_STOPBIT_1 \n
    UART_STOPBIT_2 \n */
  UartStopBits_t stopbits;  
  /** \brief edge - data received edge (only for usart). Must be chosen from: \n
    RISING_EDGE \n
    FALLING_EDGE \n */
  UartSyncMode_t edge;
  /** \brief master or slave on usart (only for usart)*/
  UartClckMode_t syncMode;  
  /** \brief It's pointer to receive buffer. \n
   If rxBuffer is NULL then transactions are discarded. \n
   Size of buffer depends on user application. */
  uint8_t *rxBuffer; 
  /** \brief length of receive buffer */
  uint16_t rxBufferLength; 
  /** \brief It's pointer to transmit buffer. \n
   If txBuffer is NULL then callback method is used. \n
   If txBuffer isn't NULL then polling method is used. */
  uint8_t *txBuffer; 
  /** \brief length of transmit buffer */
  uint16_t txBufferLength; 
  /** \brief It's receive uart callback. \n
   If rxCallback is NULL then polling method is used. \n
   If rxCallback isn't NULL then callback method is used.*/
  void (*rxCallback)(uint8_t);
  /** \brief It's transmitting was completed uart callback. \n
   If txBuffer isn't NULL then txCallback notify about end of bytes sending.  */ 
  void (*txCallback)();
  /** \brief flow control of uart. One of the defines UART_FLOW_CONTROL_NONE, UART_FLOW_CONTROL_HARDWARE, UART_DTR_CONTROL, it is possible to combine by logical OR. */ 
  uint8_t flowControl;
} HAL_UartDescriptor_t;

/******************************************************************************
                   Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Registers uart's event handlers. Performs configuration 
of uart registers. Performs configuration of RTS, CTS and DTR pins.

\param[in]
  descriptor - pointer to HAL_UartDescriptor_t structure

\return
  Returns positive uart descriptor on success or -1 in cases: \n
    - bad uart channel; \n
    - there are not enough resources; \n
******************************************************************************/
int HAL_OpenUart(HAL_UartDescriptor_t *descriptor);

/*************************************************************************//**
\brief Releases the uart channel and pins, if hardware flow control was used.

\param[in]
  descriptor - pointer to HAL_UartDescriptor_t structure

\return
 -1 - bad descriptor; \n
  0 - success.
*****************************************************************************/
int HAL_CloseUart(HAL_UartDescriptor_t *descriptor);

/**************************************************************************//**
\brief Writes a number of bytes to uart channel.
txCallback function will be used to notify when the transmission is finished.
If hardware flow control is used for transmitting then RTS and DTR pins will 
be tested during transmission.  

\param[in]
  descriptor - pointer to HAL_UartDescriptor_t structure;

\param[in]
  buffer - pointer to the application data buffer; 

\param[in]
  length - number of bytes to transfer;

\return
  -1 - bad descriptor; \n
   Number of bytes placed to the buffer - success.
******************************************************************************/
int HAL_WriteUart(HAL_UartDescriptor_t *descriptor, uint8_t *buffer, uint8_t length);

/*************************************************************************//**
\brief Reads a number of bytes from uart and places them to the buffer.

\param[in]
  descriptor - pointer to HAL_UartDescriptor_t structure;

\param[in]
  buffer - pointer to the application buffer;

\param[in]
  length - number of bytes to be placed to the buffer;

\return
  -1 - bad descriptor, or bad number of bytes to read; \n
  Number of bytes placed to the buffer - success.
*****************************************************************************/
int HAL_ReadUart(HAL_UartDescriptor_t *descriptor, uint8_t *buffer, uint8_t length);

/**************************************************************************//**
\brief Forbids the host to transmit data.
Only UART_CHANNEL_1 can be used for hardware flow control for avr.

\param[in]
  descriptor - pointer to HAL_UartDescriptor_t structure;

\return
  -1 - bad descriptor, bad uart, or unsupported mode; \n
   0 - success.
******************************************************************************/
int HAL_OnUartCts(HAL_UartDescriptor_t *descriptor);

/**************************************************************************//**
\brief Allows the host to transmit data.
Only UART_CHANNEL_1 can be used for hardware flow control for avr.

\param[in]
  descriptor - pointer to HAL_UartDescriptor_t structure;

\return
  -1 - bad descriptor, bad uart, or unsupported mode; \n
   0 - success.  
******************************************************************************/
int HAL_OffUartCts(HAL_UartDescriptor_t *descriptor);

/**************************************************************************//**
\brief Reads RTS pin state.
Only UART_CHANNEL_1 can be used for hardware flow control for avr.

\param[in]
  descriptor - pointer to HAL_UartDescriptor_t structure;

\return
  -1 - bad descriptor, bad uart, or unsupported mode; \n
   0 - RTS is low level; \n  
   1 - RTS is high level;
******************************************************************************/
int HAL_ReadUartRts(HAL_UartDescriptor_t *descriptor);

/**************************************************************************//**
\brief Reads DTR pin state.
Only UART_CHANNEL_1 can be used for hardware flow control for avr.

\param[in]
  descriptor - pointer to HAL_UartDescriptor_t structure;

\return
  -1 - bad descriptor, bad uart, or unsupported mode; \n
   0 - DTR is low level; \n  
   1 - DTR is high level;
******************************************************************************/
int HAL_ReadUartDtr(HAL_UartDescriptor_t *descriptor);

/**************************************************************************//**
\brief Checks the status of tx buffer.

\param[in]
  descriptor - pointer to HAL_UartDescriptor_t structure;

\return
  -1 - bad descriptor, no tx buffer; \n
   1 - tx buffer is empty; \n  
   0 - tx buffer is not empty;
******************************************************************************/
int HAL_IsTxEmpty(HAL_UartDescriptor_t *descriptor);

#if defined(ATMEGA1281) || defined(ATMEGA2561)
/**************************************************************************//**
\brief Enables DTR wake up.

\param[in]
  callback - pointer to callback method;
******************************************************************************/
void HAL_EnableDtrWakeUp(void (* callback)(void));

/**************************************************************************//**
\brief Disables DTR wake up.
******************************************************************************/
void HAL_DisableDtrWakeUp(void);
#endif

#endif /* _UART_H */
// eof uart.h
