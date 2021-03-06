/*
 * ArduRCT_Graphics_Configuration - Hardware configuration
 *
 * Copyright (c) 2010-2014 Laurent Wibaux <lm.wibaux@gmail.com>
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
 
#ifndef ARDURCT_GRAPHICS_CONFIGURATION_H
#define ARDURCT_GRAPHICS_CONFIGURATION_H

#define GRAPHICS_HARDWARE_WIDTH  240
#define GRAPHICS_HARDWARE_HEIGHT 320

/**
 * Defining the pins as constants here allows for a lot of optimisations
 * during compilation
 * See ArduRCT_ParallelScreenUtils.h for details
 **/

#ifdef __AVR__
#define GRAPHICS_HARDWARE_DATA_OUT_PORT PORTB
#define GRAPHICS_HARDWARE_DATA_IN_PORT PINB
#define GRAPHICS_HARDWARE_DATA_DDR_PORT DDRB
#define GRAPHICS_HARDWARE_WR_PORT PORTC

#define GRAPHICS_HARDWARE_WR_PIN 23
#define GRAPHICS_HARDWARE_RD_PIN 21
#define GRAPHICS_HARDWARE_CD_PIN 22
#define GRAPHICS_HARDWARE_CS_PIN 31
#define GRAPHICS_HARDWARE_RESET_PIN 0xFF
#define GRAPHICS_HARDWARE_SPI_ON_BUS true
#define GRAPHICS_HARDWARE_BACKLIGHT_PIN 5
#endif

#if defined(__arm__) && defined(CORE_TEENSY)
#define GRAPHICS_HARDWARE_D0 2
#define GRAPHICS_HARDWARE_D1 14
#define GRAPHICS_HARDWARE_D2 7
#define GRAPHICS_HARDWARE_D3 8
#define GRAPHICS_HARDWARE_D4 6
#define GRAPHICS_HARDWARE_D5 20
#define GRAPHICS_HARDWARE_D6 21
#define GRAPHICS_HARDWARE_D7 5

#define GRAPHICS_HARDWARE_WR_PIN 29
#define GRAPHICS_HARDWARE_RD_PIN 27
#define GRAPHICS_HARDWARE_CD_PIN 28
#define GRAPHICS_HARDWARE_CS_PIN 0xFF
#define GRAPHICS_HARDWARE_RESET_PIN 30
#define GRAPHICS_HARDWARE_SPI_ON_BUS false
#define GRAPHICS_HARDWARE_BACKLIGHT_PIN 32
#endif

// Max space that a pattern or a bitmap that needs to be overlaid can occupy
// minimum is FONT_MAX_SPACE (from font.hpp)
// RAM taken can be up to 5 times this, so beware! 
#define GRAPHICS_MAX_BITMAP_SPACE (9*14)		

// if defined, the screen will try to use 12bits colors
#define GRAPHICS_12B_COLORS_ALLOWED 1

// Comment this if you don't want to use macros
//#define GRAPHICS_HAS_MACROS 1
// the number of macros defined in eeprom
// each compressed macro can be up to SCREEN_MACRO_MAX_SIZE character long
// the eeprom taken will be SCREEN_MACRO_MAX_NUMBER * SCREEN_MACRO_MAX_SIZE bytes
#define GRAPHICS_MACRO_MAX_NUMBER 16
// this number can not be bigger than 255
#define GRAPHICS_MACRO_MAX_SIZE 128

// Comment this if you don't want to use the UI
#define GRAPHICS_HAS_UI 1

#endif