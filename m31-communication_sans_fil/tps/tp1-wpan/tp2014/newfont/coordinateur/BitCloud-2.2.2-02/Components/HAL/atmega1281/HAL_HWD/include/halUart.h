/*********************************************************************************
  halUart.h 
  Copyright (c)Meshnetics.

  Description:
    Declarations of uart hardware-dependent module.
          
  History:
    29/05/07 E. Ivanov - Created
**********************************************************************************/

#ifndef _HAL_UART_H
#define _HAL_UART_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <halClkCtrl.h>
#include <halTaskManager.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
/* if UART_DOUBLE_SPEED is 1 the USART uses U2Xn bit (Double speed the usart transmition).
   if UART_DOUBLE_SPEED is 0 then U2Xn bit is not been used.
 */
#ifndef UART_DOUBLE_SPEED
#define UART_DOUBLE_SPEED 1ul
#endif

#define UART_CHANNEL_1  2
#define UART_CHANNEL_0  1
#define DELTA_FOR_INDEX 1

#define UCSRnA 0
#define UCSRnB 1
#define UCSRnC 2
#define UBRRnL 4
#define UBRRnH 5
#define UDRn   6

/******************************************************************************
                   Types section
******************************************************************************/
// clock rate of uart
typedef enum
{
  UART_BAUDRATE_1200 =  (unsigned)((F_CPU * (UART_DOUBLE_SPEED + 1ul)) / (16ul * 1200ul) - 1ul), // 1200 baud rate
  UART_BAUDRATE_2400 =  (unsigned)((F_CPU * (UART_DOUBLE_SPEED + 1ul)) / (16ul * 2400ul) - 1ul), // 2400 baud rate
  UART_BAUDRATE_4800 =  (unsigned)((F_CPU * (UART_DOUBLE_SPEED + 1ul)) / (16ul * 4800ul) - 1ul), // 4800 baud rate
  UART_BAUDRATE_9600 =  (unsigned)((F_CPU * (UART_DOUBLE_SPEED + 1ul)) / (16ul * 9600ul) - 1ul), // 9600 baud rate
  UART_BAUDRATE_19200 =  (unsigned)((F_CPU * (UART_DOUBLE_SPEED + 1ul)) / (16ul * 19200ul) - 1ul), // 19200 baud rate
  UART_BAUDRATE_38400 = (unsigned)((F_CPU * (UART_DOUBLE_SPEED + 1ul)) / (16ul * 38400ul) - 1ul), // 38400 baud rate
  UART_BAUDRATE_115200 = (unsigned)((F_CPU * (UART_DOUBLE_SPEED + 1ul)) / (16ul * 115200ul)), // 115200 baud rate  
  UART_SYNC_BAUDRATE_1200  =  (uint16_t)((F_CPU / (2ul * 1200ul)) - 1ul),
  UART_SYNC_BAUDRATE_2400  =  (uint16_t)((F_CPU / (2ul * 2400ul)) - 1ul),
  UART_SYNC_BAUDRATE_4800  =  (uint16_t)((F_CPU / (2ul * 4800ul)) - 1ul),
  UART_SYNC_BAUDRATE_9600  =  (uint16_t)((F_CPU / (2ul * 9600ul)) - 1ul),
  UART_SYNC_BAUDRATE_38400 =  (uint16_t)((F_CPU / (2ul * 38400ul)) - 1ul),
  UART_SYNC_BAUDRATE_57600 =  (uint16_t)((F_CPU / (2ul * 57600ul)) - 1ul),
  UART_SYNC_BAUDRATE_115200 = (uint16_t)((F_CPU / (2ul * 115200ul)) - 1ul)
} UartBaudRate_t;

// uart data length
typedef enum
{
  UART_DATA5 = (0 << UCSZ12) | (0 << UCSZ11) | (0 << UCSZ10), // 5 bits data length
  UART_DATA6 = (0 << UCSZ12) | (0 << UCSZ11) | (1 << UCSZ10), // 6 bits data length
  UART_DATA7 = (0 << UCSZ12) | (1 << UCSZ11) | (0 << UCSZ10), // 7 bits data length
  UART_DATA8 = (0 << UCSZ12) | (1 << UCSZ11) | (1 << UCSZ10), // 8 bits data length
} UartData_t;

// parity mode
typedef enum
{
  UART_PARITY_NONE = (0 << UPM11) | (0 << UPM10), // Non parity mode
  UART_PARITY_EVEN = (1 << UPM11) | (0 << UPM10), // Even parity mode
  UART_PARITY_ODD =  (1 << UPM11) | (1 << UPM10)  // Odd parity mode
} UartParity_t;

// number of stop bits
typedef enum
{
  UART_STOPBIT_1 = (0 << USBS1), // 1 stop bits mode
  UART_STOPBIT_2 = (1 << USBS1)  // 2 stop bits mode
} UartStopBits_t;

// Defines edge of clock to sample data.
/*
------------------------------------------------------------------------------------
|            |  Transmitted Data Changed (Output | Received Data Sampled (Input on |
|            |  of TxDn Pin)                     | RxDn Pin)                       |
|------------|-----------------------------------|----------------------------------
|FALLING_EDGE|  Rising XCKn Edge                 | Falling XCKn Edge               |
|RISING_EDGE |  Falling XCKn Edge                | Rising XCKn Edge                |
------------------------------------------------------------------------------------
*/
typedef enum
{
  FALLING_EDGE = 0,
  RISING_EDGE  = 1
} UartSyncMode_t;

// uart mode
typedef enum
{
  ASYNC     = ((0 << UMSEL01) | (0 << UMSEL00)),
  SYNC      = ((0 << UMSEL01) | (1 << UMSEL00))
} UartMode_t;

// clck is output in master mode else input  
typedef enum
{
  SYNC_MASTER = 0,
  SYNC_SLAVE = 1	  
} UartClckMode_t;

// usart control
typedef struct 
{
  uint8_t txBufferLength; // length of transmit buffer
  uint8_t *txBuffer;
  uint8_t txPointOfRead; 
  uint8_t txPointOfWrite; 
  uint8_t rxBufferLength; // length of transmit buffer
  uint8_t *rxBuffer;
  uint8_t rxPointOfRead; 
  uint8_t rxPointOfWrite; 
} UartControl_t;

// bit field for shift register empty data
typedef struct
{
  uint8_t u0Empty : 1;
  uint8_t u1Empty : 1;
} UartShiftRegisterEmpty_t;

/******************************************************************************
                   Prototypes section
******************************************************************************/
/******************************************************************************
  Puts byte to the ring buffer.
  Parameters:
    i - offset into halUartControl.
    data - data to put.
  Returns:
    none.
******************************************************************************/
void halUartRxBufferFiller(uint8_t i, uint8_t data);

/******************************************************************************
                   Inline static functions section 
******************************************************************************/
/******************************************************************************
  Disables USART channel
  Parameters:
    tty - number of USART channel.
  Returns:
    none.
******************************************************************************/
INLINE void halCloseUART(uint8_t tty)
{
  *(uint8_t*)((uint8_t*)(&UCSR0A + (tty * 8)) + UCSRnB) = 0x00; // disable uart 
}

/******************************************************************************
  Enables data register empty interrupt
  Parameters:
    tty - number of USART channel.
  Returns:
    none.
******************************************************************************/
INLINE void halEnableUARTDremInterrupt(uint8_t tty)
{
  *(uint8_t*)((uint8_t*)(&UCSR0A + (tty * 8)) + UCSRnB) |=  (1 << UDRIE1); 
}

/******************************************************************************
  Disables data register empty interrupt
  Parameters:
    tty - number of USART channel.
  Returns:
    none.
******************************************************************************/
INLINE void halDisableUARTDremInterrupt(uint8_t tty)
{
  *(uint8_t*)((uint8_t*)(&UCSR0A + (tty * 8)) + UCSRnB) &=  ~(1 << UDRIE1); 
}

/******************************************************************************
  Enables transmit complete interrupt
  Parameters:
    tty - number of USART channel.
  Returns:
    none.
******************************************************************************/
INLINE void halEnableUARTTxcInterrupt(uint8_t tty)
{
  *(uint8_t*)((uint8_t*)(&UCSR0A + (tty * 8)) + UCSRnB) |=  (1 << TXCIE1); 
}

/******************************************************************************
  Disables transmit complete interrupt
  Parameters:
    tty - number of USART channel.
  Returns:
    none.
******************************************************************************/
INLINE void halDisableUARTTxcInterrupt(uint8_t tty)
{
  *(uint8_t*)((uint8_t*)(&UCSR0A + (tty * 8)) + UCSRnB) &=  ~(1 << TXCIE1); 
}

/******************************************************************************
  Enables receive complete interrupt
  Parameters:
    tty - number of USART channel.
  Returns:
    none.
******************************************************************************/
INLINE void halEnableUARTRxcInterrupt(uint8_t tty)
{
  *(uint8_t*)((uint8_t*)(&UCSR0A + (tty * 8)) + UCSRnB) |=  (1 << RXCIE0); 
}

/******************************************************************************
  Disables receive complete interrupt
  Parameters:
    tty - number of USART channel.
  Returns:
    none.
******************************************************************************/
INLINE void halDisableUARTRxcInterrupt(uint8_t tty)
{
  *(uint8_t*)((uint8_t*)(&UCSR0A + (tty * 8)) + UCSRnB) &=  ~(1 << RXCIE0); 
}

/******************************************************************************
  Puts byte to data register of USART
  Parameters:
    tty - number of USART channel.
    data - byte to send.
  Returns:
******************************************************************************/
INLINE void halSendUARTRByte(uint8_t tty, uint8_t data)
{
  *(uint8_t*)((uint8_t*)(&UCSR0A + (tty * 8)) + UDRn) = data;
}

/******************************************************************************
  Posts the task to taskhandler that USART0 data register empty 
  interrupt has occured. 
******************************************************************************/
INLINE void halSigUsart0DataInterrupt(void)
{
  // We must disable the interrupt because we must "break" context.
  halDisableUARTDremInterrupt(UART_CHANNEL_0 - DELTA_FOR_INDEX);
  halPostTask3(HAL_USART0_UDRE);
}

/******************************************************************************
  Posts the task to taskhandler that Tx complete on UASRT0 
  interrupt has occured. 
******************************************************************************/
INLINE void halSigUsart0TransInterrupt(void)
{
  halDisableUARTTxcInterrupt(UART_CHANNEL_0 - DELTA_FOR_INDEX);
  halPostTask3(HAL_USART0_TX);
}

/******************************************************************************
  Posts the task to taskhandler that USART0 receive 
  interrupt has occured. 
  Parameters:
    data - data to put
******************************************************************************/
INLINE void halSigUsart0RecvInterrupt(uint8_t data)
{
  halUartRxBufferFiller(UART_CHANNEL_0 - DELTA_FOR_INDEX, data);
  halPostTask2(HAL_USART0_RX);
}

/******************************************************************************
  Posts the task to taskhandler that USART1 data register empty 
  interrupt has occured. 
******************************************************************************/
INLINE void halSigUsart1DataInterrupt(void)
{
  // We must disable the interrupt because we must "break" context.
  halDisableUARTDremInterrupt(UART_CHANNEL_1 - DELTA_FOR_INDEX); 
  halPostTask4(HAL_USART1_UDRE);
}

/******************************************************************************
  Posts the task to taskhandler that Tx complete on UASRT1 
  interrupt has occured. 
******************************************************************************/
INLINE void halSigUsart1TransInterrupt(void)
{
  halDisableUARTTxcInterrupt(UART_CHANNEL_1 - DELTA_FOR_INDEX);
  halPostTask4(HAL_USART1_TX);
}

/******************************************************************************
  Posts the task to taskhandler that USART1 receive 
  interrupt has occured. 
  Parameters:
    data - data to put
******************************************************************************/
INLINE void halSigUsart1RecvInterrupt(uint8_t data)
{
  halUartRxBufferFiller(UART_CHANNEL_1 - DELTA_FOR_INDEX, data);
  halPostTask4(HAL_USART1_RX);
}

#endif /* _HAL_UART_H */
//eof halUart.h
