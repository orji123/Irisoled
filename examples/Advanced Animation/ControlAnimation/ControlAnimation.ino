/**********
  ControlAnimation.ino
  -------------------------------
  Purpose:
    Demonstrates advanced controls: start(), stop(), resume(), reset(), isRunning().
    Shows how to control playback from program logic (here using millis()).

  Requirements:
    - Adafruit GFX + display driver
    - Irisoled + IrisoledAnimation

  Usage:
    - Example uses timed events; replace with button/sensor logic as needed.
        
  Published 2025 by Chijindu-Orji Iseh-Ntah
**********/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> // Or #include <Adafruit_SH1106.h> for SH1106 based display
#include <Irisoled.h>
#include <IrisoledAnimation.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1); // Or Adafruit_SH1106 display(-1); for SH1106 based display

const unsigned char* frames[] = {
  Irisoled::normal,
  Irisoled::blink,
  Irisoled::normal
};
const uint16_t delays[] = { 400, 200, 400 };

IrisoledAnimation anim(frames, 3, delays, 200, true);

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Or display.begin(SH1106_SWITCHCAPVCC, 0x3C); for SH1106 based display
  anim.start();
}

void loop() {
  anim.update(display, 0, 0, 128, 64);

  // Example: stop after 5 seconds
  if (millis() > 5000 && anim.isRunning()) {
    Serial.println("Stopping animation...");
    anim.stop();
  }

  // Resume after 8 seconds
  if (millis() > 8000 && !anim.isRunning()) {
    Serial.println("Resuming animation...");
    anim.resume();
  }

  // Reset at 12 seconds
  if (millis() > 12000) {
    Serial.println("Resetting animation...");
    anim.reset();
    anim.start();
  }
}
