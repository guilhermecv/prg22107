// - - - - -
// DmxSerialNeoPixels.ino: Sample DMX application for retrieving 3 DMX values:
//
// Copyright (c) 2016 by Matthias Hertel, http://www.mathertel.de
// This work is licensed under a BSD style license. See http://www.mathertel.de/License.aspx
//
// Documentation and samples are available at http://www.mathertel.de/Arduino
// 06.09.2016 Creation of DmxSerialNeoPixels sample.
// 27.08.2017 working with new DMXSerial DMXProbe mode.
//            cleanup.

// - - - - -

#include <Arduino.h>
#include <DMXSerial.h>

#include "ws2812.h"

// Constants for demo program

#define RedDefaultLevel   5 // 100
#define GreenDefaultLevel 0 // 200
#define BlueDefaultLevel  0 // 255

// number of RGB neopixels, RGB channels are transfered
// warning: try with 12 first and scale up carefully.
#define PIXELS 12

// first DMX start address
#define DMXSTART 1

// number of DMX channels used
#define DMXLENGTH (PIXELS*3)

// Initialize DMXSerial and neo pixel output
void setup () {
  int n;
  DMXSerial.init(DMXProbe);

  // enable pwm outputs
  
  DMXSerial.maxChannel(DMXLENGTH); // after 3 * pixel channels, the onUpdate will be called when new data arrived.

  // setup the neopixel output
  setupNeopixel();

  // give them a decent color...
  n = 1;
  for (int p = 0; p < PIXELS; p++) {
    DMXSerial.write(n++, 5);
    DMXSerial.write(n++, 10);
    DMXSerial.write(n++, 20);
  }
  updateNeopixel(DMXSerial.getBuffer() + DMXSTART, PIXELS);

} // setup ()


// do constantly fetch DMX data and update the neopixels.
void loop() {
  // wait for an incomming DMX packet.
  if (DMXSerial.receive()) {
    updateNeopixel(DMXSerial.getBuffer() + DMXSTART, PIXELS);

  } else {
    // don't update the Neopixels but signal a red.
  } // if
  
} // loop()


// The End.
