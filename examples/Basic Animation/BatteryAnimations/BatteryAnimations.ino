/**********
  BatteryAnimations.ino
  -----------------------
  Purpose:
    Demonstrates battery animation: battery_low -> battery -> battery_full

  Requirements:
    - Adafruit GFX + display driver
    - Irisoled + IrisoledAnimation

  Usage:
    - Replace the sequence with real battery level checks to reflect real status.
        
  Published 2025 by Chijindu-Orji Iseh-Ntah
**********/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> // Or #include <Adafruit_SH1106.h> for SH1106 based display
#include <Irisoled.h>
#include <IrisoledAnimation.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1); // Or Adafruit_SH1106 display(-1); for SH1106 based display

const unsigned char* frames[] = {
  Irisoled::battery_low, Irisoled::battery, Irisoled::battery_full
};
const uint16_t delays[] = { 400, 400, 400 };

IrisoledAnimation anim(frames, sizeof(frames)/sizeof(frames[0]), delays, 200, true);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Or display.begin(SH1106_SWITCHCAPVCC, 0x3C); for SH1106 based display
  anim.start();
}

void loop() {
  anim.update(display, 0, 0, 128, 64);
}
