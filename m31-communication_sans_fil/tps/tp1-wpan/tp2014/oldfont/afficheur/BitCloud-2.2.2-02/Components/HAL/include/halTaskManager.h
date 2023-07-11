/**************************************************************************//**
\file  halTaslManager.h

\brief
    Declarations of enums and functions of HAL task manager.

\internal
  Copyright (c)Meshnetics.
  History:
    10/12/07 A. Khromykh - Created
*******************************************************************************/

#ifndef _HAL_TASKHANDLER_H
#define _HAL_TASKHANDLER_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <taskManager.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
#if defined(AT91SAM7X256)
/*! \brief task ID for hal task manager.  HAL_FIRST_X are free ID. */
enum
{
  HAL_USB_ENDPOINTS               = 1ul << 0,
  HAL_USB_SUSPEND                 = 1ul << 1,
  HAL_USB_RESUME                  = 1ul << 2,
  HAL_USB_BUS_RESET               = 1ul << 3,
  HAL_FIRST_5                     = 1ul << 4,
  HAL_SPI_EEPROM_ACCESS_DENIED    = 1ul << 5,   /** eeprom has busy state */
  HAL_FIRST_6                     = 1ul << 6,
  HAL_FIRST_7                     = 1ul << 7,
  HAL_FIRST_8                     = 1ul << 8,
  HAL_FIRST_9                     = 1ul << 9,
  HAL_FIRST_10                    = 1ul << 10,
  HAL_FIRST_11                    = 1ul << 11,
  HAL_FIRST_12                    = 1ul << 12,
  HAL_FIRST_13                    = 1ul << 13,
  HAL_FIRST_14                    = 1ul << 14,
  HAL_FIRST_15                    = 1ul << 15,
  HAL_FIRST_16                    = 1ul << 16,
  HAL_FIRST_17                    = 1ul << 17,
  HAL_FIRST_18                    = 1ul << 18,
  HAL_FIRST_19                    = 1ul << 19,
  HAL_FIRST_20                    = 1ul << 20,
  HAL_FIRST_21                    = 1ul << 21,
  HAL_FIRST_22                    = 1ul << 22,
  HAL_USART0_RX                   = 1ul << 23,  /** uart0 byte is received */
  HAL_USART0_UDRE                 = 1ul << 24,  /** uart0 shift register is empty */
  HAL_USART0_TX                   = 1ul << 25,  /** uart0 byte is moved to shift register */
  HAL_FIRST_23                    = 1ul << 26,
  HAL_ADC                         = 1ul << 27,  /** adc measurement is ready */
  HAL_FIRST_24                    = 1ul << 28,
  HAL_FIRST_25                    = 1ul << 29,
  HAL_FIRST_26                    = 1ul << 30,
  HAL_FIRST_27                    = 1ul << 31
};

/*! \brief task ID for hal task manager.  HAL_SECOND_X are free ID. */
enum
{
  HAL_SECOND_1                    = 1ul << 0,
  HAL_SECOND_2                    = 1ul << 1,
  HAL_USART1_RX                   = 1ul << 2,  /** uart1 byte is received */
  HAL_USART1_UDRE                 = 1ul << 3,  /** uart1 shift register is empty */
  HAL_USART1_TX                   = 1ul << 4,  /** uart1 byte is moved to shift register */
  HAL_TWI                         = 1ul << 5,  /** twi bus interrupt is happened */
  HAL_SECOND_3                    = 1ul << 6,
  HAL_TIMER4_COMPA                = 1ul << 7,  /** timer interrupt is happened */
  HAL_SECOND_4                    = 1ul << 8,
  HAL_SECOND_5                    = 1ul << 9,
  HAL_SECOND_6                    = 1ul << 10,
  HAL_SECOND_7                    = 1ul << 11,
  HAL_SECOND_8                    = 1ul << 12,
  HAL_SECOND_9                    = 1ul << 13,
  HAL_SECOND_10                   = 1ul << 14,
  HAL_SECOND_11                   = 1ul << 15,
  HAL_UART0_TXBUFE                = 1ul << 16,  /** uart0 dma buffer is empty */
  HAL_UART0_RXBUFF                = 1ul << 17,  /** uart0 dma buffer is full */
  HAL_UART0_TIMEOUT               = 1ul << 18,  /** uart0 dma timeout is happened */
  HAL_UART1_TXBUFE                = 1ul << 19,  /** uart1 dma buffer is empty */
  HAL_UART1_RXBUFF                = 1ul << 20,  /** uart1 dma buffer is full */
  HAL_UART1_TIMEOUT               = 1ul << 21,  /** uart1 dma timeout is happened */
  HAL_SPI0_TXBUFE                 = 1ul << 22,  /** spi0 dma buffer is empty */
  HAL_SPI0_RXBUFF                 = 1ul << 23,  /** spi0 dma buffer is full */
  HAL_SPI1_TXBUFE                 = 1ul << 24,  /** spi1 dma buffer is empty */
  HAL_SPI1_RXBUFF                 = 1ul << 25,  /** spi1 dma buffer is full */
  HAL_SECOND_12                   = 1ul << 26,
  HAL_SECOND_13                   = 1ul << 27,
  HAL_SECOND_14                   = 1ul << 28,
  HAL_SECOND_15                   = 1ul << 29,
  HAL_SECOND_16                   = 1ul << 30,
  HAL_SECOND_17                   = 1ul << 31
};

#elif defined(ATMEGA1281) || defined(ATMEGA2561)

enum
{
  HAL_INT0         = (uint8_t)1 << 0,
  HAL_INT1         = (uint8_t)1 << 1,
  HAL_INT2         = (uint8_t)1 << 2,
  HAL_INT3         = (uint8_t)1 << 3,
  HAL_INT4         = (uint8_t)1 << 4,
  HAL_INT5         = (uint8_t)1 << 5,
  HAL_INT6         = (uint8_t)1 << 6,
  HAL_INT7         = (uint8_t)1 << 7
};

enum
{
  HAL_PCINT0       = (uint8_t)1 << 0,
  HAL_PCINT1       = (uint8_t)1 << 1,
  HAL_WDT          = (uint8_t)1 << 2,
  HAL_TIMER2_COMPA = (uint8_t)1 << 3,
  HAL_TIMER2_COMPB = (uint8_t)1 << 4,
  HAL_TIMER2_OVF   = (uint8_t)1 << 5,
  HAL_TIMER1_CAPT  = (uint8_t)1 << 6,
  HAL_TIMER1_COMPA = (uint8_t)1 << 7
};

enum
{
  HAL_TIMER1_COMPB = (uint8_t)1 << 0,
  HAL_TIMER1_COMPC = (uint8_t)1 << 1,
  HAL_TIMER1_OVF   = (uint8_t)1 << 2,
  HAL_TIMER0_COMPA = (uint8_t)1 << 3,
  HAL_TIMER0_COMPB = (uint8_t)1 << 4,
  HAL_TIMER0_OVF   = (uint8_t)1 << 5,
  HAL_SPI_STC      = (uint8_t)1 << 6,
  HAL_USART0_RX    = (uint8_t)1 << 7
};

enum
{
  HAL_USART0_UDRE  = (uint8_t)1 << 0,
  HAL_USART0_TX    = (uint8_t)1 << 1,
  HAL_ANALOG_COMP  = (uint8_t)1 << 2,
  HAL_ADC          = (uint8_t)1 << 3,
  HAL_EE_READY     = (uint8_t)1 << 4,
  HAL_TIMER3_CAPT  = (uint8_t)1 << 5,
  HAL_TIMER3_COMPA = (uint8_t)1 << 6,
  HAL_TIMER3_COMPB = (uint8_t)1 << 7
};

enum
{
  HAL_TIMER3_COMPC = (uint8_t)1 << 0,
  HAL_TIMER3_OVF   = (uint8_t)1 << 1,
  HAL_USART1_RX    = (uint8_t)1 << 2,
  HAL_USART1_UDRE  = (uint8_t)1 << 3,
  HAL_USART1_TX    = (uint8_t)1 << 4,
  HAL_TWI          = (uint8_t)1 << 5,
  HAL_SPM_READY    = (uint8_t)1 << 6,
  HAL_TIMER4_COMPA = (uint8_t)1 << 7
};

enum
{
  HAL_TIMER4_COMPB = (uint8_t)1 << 0,
  HAL_TIMER4_COMPC = (uint8_t)1 << 1,
  HAL_TIMER4_OVF   = (uint8_t)1 << 2,
  HAL_TIMER5_COMPA = (uint8_t)1 << 3,
  HAL_TIMER5_COMPB = (uint8_t)1 << 4,
  HAL_TIMER5_COMPC = (uint8_t)1 << 5,
  HAL_TIMER5_OVF   = (uint8_t)1 << 6,
  HAL_SLEEP        = (uint8_t)1 << 7
};

#endif

/******************************************************************************
                   External variables section
******************************************************************************/
#if defined(AT91SAM7X256)
extern volatile uint32_t halTaskFlags0 ;
extern volatile uint32_t halTaskFlags1;
#elif defined(ATMEGA1281) || defined(ATMEGA2561)
extern volatile uint8_t halTaskFlags0;
extern volatile uint8_t halTaskFlags1;
extern volatile uint8_t halTaskFlags2;
extern volatile uint8_t halTaskFlags3;
extern volatile uint8_t halTaskFlags4;
extern volatile uint8_t halTaskFlags5;
#endif

/******************************************************************************
                   Inline static functions section
******************************************************************************/
#if defined(AT91SAM7X256)
/**************************************************************************//**
\brief Set task for task manager.

\param[in]
  flag task for task mask 0
******************************************************************************/
INLINE void halPostTask0(uint32_t flag)
{
  halTaskFlags0 |= flag;
  SYS_PostTask(HAL_TASK_ID);
}

/**************************************************************************//**
\brief Set task for task manager.

\param[in]
  flag task for task mask 1
******************************************************************************/
INLINE void halPostTask1(uint32_t flag)
{
  halTaskFlags1 |= flag;
  SYS_PostTask(HAL_TASK_ID);
}
#elif defined(ATMEGA1281) || defined(ATMEGA2561)
/**************************************************************************//**
\brief Set task for task manager.

\param[in]
  flag task for task mask 0
******************************************************************************/
INLINE void halPostTask0(uint8_t flag)
{
  halTaskFlags0 |= flag;
  SYS_PostTask(HAL_TASK_ID);
}

/**************************************************************************//**
\brief Set task for task manager.

\param[in]
  flag task for task mask 1
******************************************************************************/
INLINE void halPostTask1(uint8_t flag)
{
  halTaskFlags1 |= flag;
  SYS_PostTask(HAL_TASK_ID);
}

/**************************************************************************//**
\brief Set task for task manager.

\param[in]
  flag task for task mask 2
******************************************************************************/
INLINE void halPostTask2(uint8_t flag)
{
  halTaskFlags2 |= flag;
  SYS_PostTask(HAL_TASK_ID);
}

/**************************************************************************//**
\brief Set task for task manager.

\param[in]
  flag task for task mask 3
******************************************************************************/
INLINE void halPostTask3(uint8_t flag)
{
  halTaskFlags3 |= flag;
  SYS_PostTask(HAL_TASK_ID);
}

/**************************************************************************//**
\brief Set task for task manager.

\param[in]
  flag task for task mask 4
******************************************************************************/
INLINE void halPostTask4(uint8_t flag)
{
  halTaskFlags4 |= flag;
  SYS_PostTask(HAL_TASK_ID);
}

/**************************************************************************//**
\brief Set task for task manager.

\param[in]
  flag task for task mask 5
******************************************************************************/
INLINE void halPostTask5(uint8_t flag)
{
  halTaskFlags5 |= flag;
  SYS_PostTask(HAL_TASK_ID);
}
#endif

#endif  /*_HAL_TASKHANDLER_H*/

// eof halTaskManager.h
