#ifndef _TYPES_H
#define _TYPES_H

#include <stdint.h>
#include <string.h>

#if defined(__ICCAVR__) || defined(__ICCARM__)

// \cond
#if defined(AT91SAM7X256)
  #include <intrinsics.h>
#elif defined(ATMEGA1281) || defined(ATMEGA2561)
  #include <inavr.h>
  #include <ioavr.h>
  #include <intrinsics.h>
  #include <pgmspace.h>
#endif
// \endcond

/**
 * Some preprocessor magic to allow for a header file abstraction of
 * interrupt service routine declarations for the IAR compiler.  This
 * requires the use of the C99 _Pragma() directive (rather than the
 * old #pragma one that could not be used as a macro replacement), as
 * well as two different levels of preprocessor concetanations in
 * order to do both, assign the correct interrupt vector name, as well
 * as construct a unique function name for the ISR.
 *
 * Do *NOT* try to reorder the macros below, or you'll suddenly find
 * out about all kinds of IAR bugs...
 */
#define PRAGMA(x) _Pragma(#x)

// \cond
#if defined(AT91SAM7X256)

  #define PROGMEM_DECLARE(x) x
  #define memcpy_P   memcpy
  #define hw_platform_address_size_t    uint32_t
  #define BEGIN_PACK PRAGMA(pack(push, 1))
  #define END_PACK   PRAGMA(pack(pop))
  #define INLINE static inline

#elif defined(ATMEGA1281) || defined(ATMEGA2561)

  #ifndef __HAS_ELPM__
    #define _MEMATTR  __flash
  #else /* __HAS_ELPM__ */
    #define _MEMATTR  __farflash
  #endif /* __HAS_ELPM__ */

  #define PROGMEM_DECLARE(x) _MEMATTR x
  #define BEGIN_PACK
  #define END_PACK
  #define INLINE PRAGMA(inline=forced) static

#endif
// \endcond

#define PACK /**/
#define MAY_ALIAS /**/
#define NOP       __no_operation()

/*#define ISR(vec) PRAGMA(vector=vec) __interrupt void handler_##vec(void)
#define sei() (__enable_interrupt( ))
#define cli() (__disable_interrupt( ))
#define nop() (__no_operation())*/
/** Wait until bit \c bit in IO register \c sfr is clear. */
/*#define loop_until_bit_is_clear(sfr, bit) do {;} while (sfr & (1 << bit))*/

/** Enable the watch dog timer with a specific timeout value */
/*#define wdt_enable(timeout) do {        \
    uint8_t volatile sreg_temp = SREG;  \
    cli();                              \
    __watchdog_reset();                 \
    WDTCSR |= (1 << WDCE) | (1 << WDE); \
    WDTCSR = (1 << WDE) | timeout;      \
    SREG = sreg_temp;                   \
} while (0)

#define wdt_reset() (__watchdog_reset())

#define SF_GET_LOW_FUSES() __AddrToZByteToSPMCR_LPM((void __flash *)0x0000, 0x09)*/

#elif defined(__GNUC__)

// \cond
#if defined(AT91SAM7X256)

#elif defined(ATMEGA1281) || defined(ATMEGA2561)
  #include <avr/io.h>
  #include <avr/pgmspace.h>
#endif
// \endcond

// \cond
#if defined(AT91SAM7X256)

  #define PROGMEM_DECLARE(x) x
  #define memcpy_P   memcpy
  #define hw_platform_address_size_t    uint32_t
  #define BEGIN_PACK
  #define END_PACK
  #define PACK __attribute__ ((packed))

#elif defined(ATMEGA1281) || defined(ATMEGA2561)

  #define SF_GET_LOW_FUSES() boot_lock_fuse_bits_get(GET_LOW_FUSE_BITS)
  #define PROGMEM_DECLARE(x) x __attribute__((__progmem__))
  #define hw_platform_address_size_t    uint16_t
  #define BEGIN_PACK
  #define END_PACK
  #define PACK
#endif
// \endcond

#define INLINE static inline __attribute__ ((always_inline))
#define MAY_ALIAS __attribute__((__may_alias__))
#define NOP       asm volatile ("nop")

#else
  #error 'Compiler not supported.'
#endif

typedef uint8_t bool;
typedef uint8_t result_t;

#define false  (bool)0
#define true   (bool)1
#define SUCCESS (result_t)0
#define FAIL    (result_t)1

#endif
// eof types.h
