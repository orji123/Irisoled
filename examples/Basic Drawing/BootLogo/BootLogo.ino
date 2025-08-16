/**********
  BootLogo.ino
  ------------
  Purpose:
    Display a boot logo for a short time, then switch to a runtime expression (Irisoled::happy).

  Requirements:
    - Adafruit GFX
    - Adafruit SSD1306 or compatible
    - Irisoled library

  Usage:
    - Adjust the boot delay (currently 2000 ms) to shorten/lengthen the logo display.
    - Replace Irisoled::logo and Irisoled::happy with other bitmaps if desired.

  Notes:
    - Good for showing startup state on robot power-on.

  Published 2025 by Chijindu-Orji Iseh-Ntah
*********/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> // Or #include <Adafruit_SH1106.h> for SH1106 based display
#include <Irisoled.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1); // Or Adafruit_SH1106 display(-1); for SH1106 based display

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Or display.begin(SH1106_SWITCHCAPVCC, 0x3C); for SH1106 based display
  
  // Boot logo
  display.clearDisplay();
  display.drawBitmap(0, 0, Irisoled::logo, 128, 64, 1);
  display.display();
  delay(2000);

  // Switch to happy
  display.clearDisplay();
  display.drawBitmap(0, 0, Irisoled::happy, 128, 64, 1);
  display.display();
}

void loop() {
}
