/*
 * TouScruinoV1 - Screen and 5 ways switch management
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

/* 
 * Versions
 *    v0.1    Initial release
 */
 
#ifndef TOUSCRUINO_V1_H
#define TOUSCRUINO_V1_H 1

#include "../ArduRCT_Graphics/ArduRCT_ST7735.h"
#include "../ArduRCT_EventManager/ArduRCT_EventManager.h"
#include "ArduRCT_TouScruino_Configuration.hpp"

class ArduRCT_TouScruinoV1: public ArduRCT_ST7735, public ArduRCT_EventManager {

    public:
        ArduRCT_TouScruinoV1(ArduRCT_RealTimeClock *rtc, ArduRCT_Switch *up, ArduRCT_Switch *down, ArduRCT_Switch *left, ArduRCT_Switch *right, ArduRCT_Switch *center);
};

#endif