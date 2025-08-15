/***************************************************
  Irisoled - Robotic OLED Eye Expressions Library
  Copyright (c) 2025 Chijindu-Orji Iseh-Ntah

  Licensed under the MIT License.
  See license.txt for details.
****************************************************/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_SH1106.h>
#include <Irisoled.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // Uncomment for SSD1306 based OLED display
Adafruit_SH1106 display(OLED_RESET); // Uncomment for SH1106 based OLED display

void setup() {
  // display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Uncomment for SSD1306 based OLED display
  display.begin(SH1106_SWITCHCAPVCC, 0x3C); // Uncomment for SH1106 based OLED display
  display.clearDisplay();

  // Draw boot screen bitmap at (0,0)
  display.drawBitmap(0, 0, Irisoled::boot, 128, 64, WHITE);
  display.display();
}

void loop() {
}
