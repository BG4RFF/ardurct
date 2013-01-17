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

class ArduRCT_TouScruinoV1: public ArduRCT_ST7735 {

    public:
        ArduRCT_TouScruinoV1(uint8_t cd, uint8_t cs, uint8_t reset, uint8_t backlightPin, ArduRCT_EventManager *eventManager,
            ArduRCT_Switch *up, ArduRCT_Switch *down, ArduRCT_Switch *left, ArduRCT_Switch *right, ArduRCT_Switch *center);
    
        void update();
        
        ArduRCT_RealTimeClock *getRTC();
        
        void registerEventHandler(ArduRCT_EventHandler *handler);

        void registerSwitch(ArduRCT_Switch *aSwitch);
        
        void registerAnalog(ArduRCT_Analog *anAnalog);
        
        void registerEncoder(ArduRCT_Encoder *anEncoder);
        
    private:
        ArduRCT_EventManager *_eventManager;
};

#endif