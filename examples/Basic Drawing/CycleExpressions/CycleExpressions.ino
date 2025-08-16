/**********
  CycleExpressions.ino
  -----------------------
  Purpose:
    Iterate through Irisoled bitmaps and display each one for a second.
    Useful to preview most bitmap available in the library.

  Requirements:
    - Adafruit GFX
    - Adafruit SSD1306 (or GFX-compatible driver)
    - Irisoled library

  Usage:
    - Adjust the delay inside loop() to change display time per image.
    - Ensure the allBitmaps[] list matches the bitmaps declared in your Irisoled.h.
    
  Published 2025 by Chijindu-Orji Iseh-Ntah
**********/


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> // Or #include <Adafruit_SH1106.h> for SH1106 based display
#include <Irisoled.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1); // Or Adafruit_SH1106 display(-1); for SH1106 based display

const unsigned char* allBitmaps[] = {
  Irisoled::normal,
  Irisoled::alert,
  Irisoled::angry,
  Irisoled::furious,
  Irisoled::happy,
  Irisoled::sad,
  Irisoled::surprised,
  Irisoled::sleepy,
  Irisoled::blink,
  Irisoled::wink_left,
  Irisoled::wink_right,
  Irisoled::look_left,
  Irisoled::look_right,
  Irisoled::look_up,
  Irisoled::look_down,
  Irisoled::disoriented,
};
const int numBitmaps = sizeof(allBitmaps) / sizeof(allBitmaps[0]);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Or display.begin(SH1106_SWITCHCAPVCC, 0x3C); for SH1106 based display
}

void loop() {
  for (int i = 0; i < numBitmaps; i++) {
    display.clearDisplay();
    display.drawBitmap(0, 0, allBitmaps[i], 128, 64, 1);
    display.display();
    delay(1000);
  }
}
