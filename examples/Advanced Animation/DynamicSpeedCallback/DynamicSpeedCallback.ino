/**********
  DynamicSpeedCallback.ino
  -----------------------------------
  Purpose:
    Demonstrates:
      - setting a uniform frame delay at runtime (setFrameDelay)
      - switching to per-frame delays (setDelays)
      - receiving frame-change notifications via setFrameCallback

  Requirements:
    - Adafruit GFX + display driver
    - Irisoled + IrisoledAnimation

  Usage:
    - Toggle delays or callback behavior based on sensors or UI events.
        
  Published 2025 by Chijindu-Orji Iseh-Ntah
**********/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> // Or #include <Adafruit_SH1106.h> for SH1106 based display
#include <Irisoled.h>
#include <IrisoledAnimation.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1); // Or Adafruit_SH1106 display(-1); for SH1106 based display

const unsigned char* frames[] = {
  Irisoled::look_left,
  Irisoled::look_right,
  Irisoled::look_up,
  Irisoled::look_down
};
const uint16_t delays[] = { 300, 300, 500, 500 };

IrisoledAnimation anim(frames, 4, delays, 200, true);

// Callback function
void onFrameChange(uint8_t frameIndex) {
  Serial.print("Frame changed: ");
  Serial.println(frameIndex);
}

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Or display.begin(SH1106_SWITCHCAPVCC, 0x3C); for SH1106 based display
  anim.setFrameCallback(onFrameChange);
  anim.start();
}

void loop() {
  anim.update(display, 0, 0, 128, 64);

  // Speed up after 5 seconds
  if (millis() > 5000 && millis() < 10000) {
    anim.setFrameDelay(100);
  }

  // Use custom per-frame delays after 10 seconds
  if (millis() > 10000) {
    anim.setDelays(delays);
  }
}
