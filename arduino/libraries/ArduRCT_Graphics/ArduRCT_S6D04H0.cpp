/*
 * S6D04H0 - Implementation of the ScreenHAL abstract functions for the S6D04H0
 *
 * Copyright (c) 2012 Laurent Wibaux <lm.wibaux@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "ArduRCT_S6D04H0.h"

#define S6D04H0_DELAY    120

#define S6D04H0_CASET    0x2a
#define S6D04H0_PASET    0x2b
#define S6D04H0_RAMWR    0x2c
#define S6D04H0_RAMRD    0x2e
#define S6D04H0_MADCTL   0x36
#define S6D04H0_NOP      0x00

#define S6D04H0_R0       0x48
#define S6D04H0_R90      0x28
#define S6D04H0_R180     0x88
#define S6D04H0_R270     0xE8

// define all the macros starting with _psu_
#include "ArduRCT_ParallelScreenUtils.h"

const unsigned char PROGMEM ArduRCT_S6D04H0_initialization_code[] = {
    0xFE,           /* delay(S6D04H0_DELAY) */
    0, 0x11,        /* SLPOFF: SLeeP OFF */
    0xFE,           /* delay(S6D04H0_DELAY) */
    0, 0x13,        /* NORON: NORmal mode ON */
    0xFE,           /* delay(S6D04H0_DELAY) */
    5, 0xf3, 0x01, 0xff, 0x1f, 0x00, 0x03,
    17, 0xf2, 0x28, 0x60, 0x7f, 0x08, 0x08, 0x00, 0x00, 0x15, 0x48, 0x00, 0x07, 0x01, 0x00, 0x00, 0x94, 0x08, 0x08,
    20, 0xf4, 0x09, 0x00, 0x00, 0x00, 0x21, 0x47, 0x01, 0x02, 0x2A, 0x5D, 0x07, 0x2A, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    12, 0xf5, 0x00, 0x3c, 0x30, 0x00, 0x00, 0x12, 0x00, 0x00, 0x0d, 0x01, 0x00, 0x00,
    9, 0xf6, 0x01, 0x01, 0x07, 0x00, 0x02, 0x0c, 0x02, 0x08, 0x03,
    4, 0xf7, 0x01, 0x00, 0x10, 0x00,
    3, 0xf8, 0x99, 0x00, 0x00,
    1, 0xf9, 0x01,
    1, 0x26, 0x02,  /* GASET: Gamma Set */
    1, 0x35, 0x00,  /* TEON: Tearing on */
    1, 0x36, 0x48,  /* MADCTL: Memory ADdress ConTroL, B7,B6,B5=0 => no rotation, B3=1 => BGR filter */
    1, 0x3a, 0x55,  /* COLMOD: COLor MODe: 16 bits/pixel */
    4, 0x2a, 0x00, 0x00, 0x00, 0xef,    /* CASET: Column Address SET */
    4, 0x2b, 0x00, 0x00, 0x01, 0x3f,     /* PASET:Page Address SET */
    0, 0x29,        /* DISPON:    DISplay ON */
    0xFE,           /* delay(S6D04H0_DELAY) */
    0xFF            /* End initialization */
};


ArduRCT_S6D04H0::ArduRCT_S6D04H0() {    
    _psu_setup();
}
 
/* ---------------- Protected functions ------------------------ */

void ArduRCT_S6D04H0::initScreenImpl(void) {
    uint8_t buffer[32];
    uint16_t i = 0;
    
    // init the screen
    _psu_prepareWR();
    _psu_setDataBusDirectionAsOutput();
    while (1) {
        memcpy_P(buffer, &(ArduRCT_S6D04H0_initialization_code[i]), 32);
        if (buffer[0] == 0xFF) break;
        else if (buffer[0] == 0xFE) delay(S6D04H0_DELAY);
        else {
            _psu_write8bCommand(buffer[1]);
            for (uint8_t j=0; j<buffer[0]; j++) _psu_write8bData(buffer[2+j]);
            i += buffer[0]+1;
        }
        i++;
    }
}

// draw a single pixel
// we inline the function to go as fast as possible
void ArduRCT_S6D04H0::drawPixelImpl(uint16_t x, uint16_t y, uint16_t color) {
    _psu_prepareWR();
    _psu_write8bCommand(S6D04H0_CASET);
    _psu_write16bData(x);
    _psu_write16bData(x);
    _psu_write8bCommand(S6D04H0_PASET);
    _psu_write16bData(y);
    _psu_write16bData(y);
    _psu_write8bCommand(S6D04H0_RAMWR);
    _psu_write16bData(color);
}


void ArduRCT_S6D04H0::fillAreaImpl(uint16_t lx, uint16_t ly, uint16_t hx, uint16_t hy, uint16_t color) {
    uint32_t nbPixels = hx - lx + 1;
    nbPixels *= (hy - ly + 1);
    _psu_prepareWR();
    _setClippingRectangle(lx, ly, hx, hy);
    _psu_write8bCommand(S6D04H0_RAMWR);
    _psu_writeSingleColorBlock(nbPixels, color);
}


uint16_t *ArduRCT_S6D04H0::retrieveBitmapImpl(uint16_t *bitmap, uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
#ifdef __AVR__
    uint32_t nbPixels = width;
    nbPixels *= height;
    
    _psu_prepareWR();
    _setClippingRectangle(x, y, x+width-1, y+height-1); 
    _psu_write8bCommand(S6D04H0_RAMRD);
    GRAPHICS_HARDWARE_DATA_DDR_PORT = 0x00;    
    // one dummy read
    _psu_clearRD();
    bitmap[0] = GRAPHICS_HARDWARE_DATA_IN_PORT;
    *_rdPortPtr |= _rdHighBitMask; 
    // the data is written in R5G6B5, changed to B6G6R6 by MADCTL
    // it therefore reads back in B6G6R6 format, each color byte is [cccccc00]
    for (uint32_t i=0; i<nbPixels; i++) {
        // read B, keep 5
        _psu_clearRD();
        bitmap[i] = GRAPHICS_HARDWARE_DATA_IN_PORT >> 3;
        *_rdPortPtr |= _rdHighBitMask; 
        // read G, keep 6
        _psu_clearRD();
        bitmap[i] |= (GRAPHICS_HARDWARE_DATA_IN_PORT >> 2) << 5;
        *_rdPortPtr |= _rdHighBitMask; 
        // read R, keep 5
        _psu_clearRD();
        bitmap[i] |= (GRAPHICS_HARDWARE_DATA_IN_PORT >> 3) << 11;
        *_rdPortPtr |= _rdHighBitMask; 
    }
    _psu_setDataBusDirectionAsOutput();
#endif
    return bitmap;
}

void ArduRCT_S6D04H0::pasteBitmapImpl(uint16_t *bitmap, uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
    // nbPixels is always < 8192 because of RAM constraint
    uint16_t nbPixels = width;
    nbPixels *= height;
    _psu_prepareWR();
    _setClippingRectangle(x, y, x+width-1, y+height-1); 
    _psu_write8bCommand(S6D04H0_RAMWR);
    uint8_t *bitmap8 = (uint8_t *)bitmap;
    uint8_t pixelL;
    uint8_t pixelH;
    while (nbPixels-- > 0) {
        pixelL = *bitmap8;
        bitmap8++;
        pixelH = *bitmap8;
        bitmap8++;
        _psu_write8bData(pixelH);
        _psu_write8bData(pixelL);
    }
}


void ArduRCT_S6D04H0::setRotationImpl(uint8_t rotation) {
    _psu_prepareWR();
    _psu_write8bCommand(S6D04H0_MADCTL);
    if (rotation == GRAPHICS_ROTATION_0) {
        _psu_write8bData(S6D04H0_R0);
    } else if (rotation == GRAPHICS_ROTATION_90) {
        _psu_write8bData(S6D04H0_R90);
    } else if (rotation == GRAPHICS_ROTATION_180) {
        _psu_write8bData(S6D04H0_R180);    
    } else if (rotation == GRAPHICS_ROTATION_270) {
        _psu_write8bData(S6D04H0_R270);
    }
}


void ArduRCT_S6D04H0::selectScreenImpl() {
    if (_screenSelected) return;
#ifdef __AVR__        
    if (_spiOnBus) {
        // if SPI is active, disable it but remember that we disabled it
        if (SPCR & _BV(SPE)) {
            SPCR &= ~_BV(SPE);
            _spiUsed = true;
        }
    }
    // put the screen in data mode
    *_cdPortPtr |= _cdBitMask;
#endif
    // select the screen
    if (_cs != 0xFF) digitalWrite(_cs, LOW);
    _screenSelected = true;
}


void ArduRCT_S6D04H0::unselectScreenImpl() {
    // unselect the screen
    if (_cs != 0xFF) digitalWrite(_cs, HIGH);
#ifdef __AVR__    
    // release the SCK line, to switch off the led
    digitalWrite(SCK, LOW);
    // restore the SPI if it was active
    if (_spiOnBus & _spiUsed) {
        // we have to set SS as an output to enable SPI
        pinMode(SS, OUTPUT);
        // we always restore the master mode
        SPCR |= _BV(MSTR);
        SPCR |= _BV(SPE);
    }
#endif
    _screenSelected = false;
}


/* ---------------- Private functions -------------------------- */

// define the zone we are going to write to
void ArduRCT_S6D04H0::_setClippingRectangle(uint16_t lx, uint16_t ly, uint16_t hx, uint16_t hy) {
    _psu_write8bCommand(S6D04H0_CASET);
    _psu_write16bData(lx);
    _psu_write16bData(hx);
    _psu_write8bCommand(S6D04H0_PASET);
    _psu_write16bData(ly);
    _psu_write16bData(hy);
}

