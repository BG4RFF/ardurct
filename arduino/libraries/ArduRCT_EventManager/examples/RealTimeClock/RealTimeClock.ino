/*
 * RealTimeClock - demonstrate the use of a RTC
 *
 * Copyright (c) 2010 Laurent Wibaux <lm.wibaux@gmail.com>
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

#include <Wire.h>
#include <ArduRCT_EventManager.h>

// create a RealTimeClock
ArduRCT_RealTimeClock rtc(RTC_EXTERNAL_MCP7941X);
// create an eventManager with a RTC
ArduRCT_EventManager eventManager(&rtc);
// define a time handler
ArduRCT_EventHandler timeHandler(EVENT_TIME_SECOND, &outputTime);

void setup() {
    Serial.begin(57600);
    // register the timeHandler with the eventManager
    eventManager.registerEventHandler(&timeHandler);
}

void loop() {
    eventManager.manageEvents();
}

int8_t outputTime(uint8_t eventType) {
    Serial.print(eventManager.getRTC()->getDateAsString(RTC_WITH_DAY_OF_WEEK));
    Serial.print(" ");
    Serial.println(eventManager.getRTC()->getTimeAsString(RTC_WITH_SECONDS));
    return EVENT_HANDLING_DONE;
}