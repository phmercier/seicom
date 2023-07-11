#ifndef LCD_H_INCLUDED
#define LCD_H_INCLUDED
#include <types.h>
#include "gpio.h"
#include "globaldef.h"

#define E GPIO_2        // Pin connected to Read Enable
#define RW GPIO_3       // Pin connected to Write enable
#define RS GPIO_4       // Pin connected to Register Select LCD
#define CS GPIO_5       // Pin connected to Chip Select LCD
#define RST GPIO_7      // Pin connected to Reset


#define halInitE()       GPIO_2_make_out()
#define halUnInitE()     GPIO_2_make_in()
#define halOnE()         GPIO_2_set()
#define halOffE()        GPIO_2_clr()
#define halReadE()       GPIO_2_read()
#define halToggleE()     GPIO_2_toggle()

#define halInitRW()       GPIO_3_make_out()
#define halUnInitRW()     GPIO_3_make_in()
#define halOnRW()         GPIO_3_set()
#define halOffRW()        GPIO_3_clr()
#define halReadRW()       GPIO_3_read()
#define halToggleRW()     GPIO_3_toggle()

#define halInitRS()       GPIO_4_make_out()
#define halUnInitRS()     GPIO_4_make_in()
#define halOnRS()         GPIO_4_set()
#define halOffRS()        GPIO_4_clr()
#define halReadRS()       GPIO_4_read()
#define halToggleRS()     GPIO_4_toggle()

#define halInitCS()       GPIO_5_make_out()
#define halUnInitCS()     GPIO_5_make_in()
#define halOnCS()         GPIO_5_set()
#define halOffCS()        GPIO_5_clr()
#define halReadCS()       GPIO_5_read()
#define halToggleCS()     GPIO_5_toggle()

#define halInitRST()       GPIO_7_make_out()
#define halUnInitRST()     GPIO_7_make_in()
#define halOnRST()         GPIO_7_set()
#define halOffRST()        GPIO_7_clr()
#define halReadRST()       GPIO_7_read()
#define halToggleRST()     GPIO_7_toggle()


typedef struct
{
    uint16_t adresse;
    uint16_t taille;
    uint8_t largeur;
    uint8_t hauteur;
} font_t;

bool _lcdInit ( void );
void _lcdClear( void );
void lcdDataReady(bool valid, uint16_t data);
void lcdDataSent(bool valid, uint16_t data);
bool lcdCommand ( uint8_t cmd );
bool lcdSetDramPointer ( uint8_t row, uint8_t col );
bool lcdWrite ( uint8_t d );

// Methode pour fonts codeAscii

void _lcdDot ( uint8_t x, uint8_t y, uint8_t v );
uint8_t lcdReadStatus ( void );
void _lcdImage ( const uint8_t* bitmap, uint8_t w, uint8_t h, uint8_t x, uint8_t y, uint8_t mode );
void _lcdPrint ( uint8_t x, uint8_t y, uint8_t m , char *fmt, ... );
void _lcdFontSelect ( const uint8_t* f, uint8_t w, uint8_t h );
void _lcdRectangle (uint8_t left, uint8_t top, uint8_t right, uint8_t bottom, uint8_t linestate );
void _lcdImageEeprom(uint8_t codeAscii, uint8_t largeur, uint8_t hauteur,uint8_t tailleFont, uint8_t x, uint8_t y);
void _lcdPutChar(uint8_t codeAscii, font_t f, uint8_t x, uint8_t y);
void _lcdPutString(char *s, font_t f, uint8_t x, uint8_t y);


// Methode pour fonts Unicode

void _lcdImageEepromUnicode(uint16_t unicode, uint8_t largeur, uint8_t hauteur,uint8_t tailleFont, uint8_t x, uint8_t y);
void _lcdPutCharUnicode(uint16_t unicode, font_t f, uint8_t x, uint8_t y);
void _lcdPutStringUnicode(char *s, font_t f, uint8_t x, uint8_t y);

//#define MSQ_RST 0x01 // reset
//#define MSQ_CS  0x02 // chip select
//#define MSQ_RS  0x04 // register select
//#define MSQ_WR  0x08 // write enable clock
//#define MSQ_RD  0x10 // read enable clock



#define LCD_PIXEL_OFF   0
#define LCD_PIXEL_ON    1
#define LCD_PIXEL_INV   2


//**** LCD 128x64 dots - E.G. Displaytech 64128H
#define LCD_ROWS  8           // 8 bit row x 8 row = 64 dots
#define LCD_COLS  128         // 1 bit colum x 128 = 128 Dots


#define LCD_CMD_RESET    0xE2
#define LCD_CMD_ON       0xAE
#define LCD_CMD_RES      0x20
#define LCD_CMD_SRV      0x81
#define LCD_CMD_BIAS     0xA2
#define LCD_CMD_POWERC   0x28
#define LCD_CMD_SIR      0xAC
#define LCD_CMD_ADC      0xA0
#define LCD_CMD_SHL      0xC0
#define LCD_CMD_EON      0xA4
#define LCD_CMD_REVERSE  0xA6
#define LCD_CMD_IDL      0x40
#define LCD_CMD_SPAGE    0xB0
#define LCD_CMD_COL      0x10

#endif // LCD_H_INCLUDED
