package com.google.code.ardurct.libraries.graphics.examples;

import com.google.code.ardurct.libraries.graphics.ArduRCT_JAVA;
import com.google.code.ardurct.libraries.graphics.GraphicsFirmware;

public class InteractiveMacros extends GraphicsFirmware {

	ArduRCT_JAVA graphics = new ArduRCT_JAVA();
	
	public int buffer[] = new int[256];
	public int bufferPtr = 0;
	
	public void setup() {
		Serial.begin(9600);
	    graphics.begin(BLACK, WHITE, FONT_MEDIUM, FONT_PLAIN, NO_OVERLAY);
	    graphics.setBacklight(180);
	}

	public void loop() {
		while (Serial.available() > 0) {
			int val = Serial.read();
			buffer[bufferPtr] = val;
			if ((val == '.') || (val == '\n')) break;
			bufferPtr++;
		}
		if ((buffer[bufferPtr] == '.') || (buffer[bufferPtr] == '\n')) {
			if (bufferPtr > 0 && buffer[bufferPtr-1] == '\r') buffer[bufferPtr-1] = 0;
			buffer[bufferPtr] = 0;
			bufferPtr = 0;
			graphics.executeMacro(buffer, 0, 0, 1, 1, true, true);
		}
	}
}
