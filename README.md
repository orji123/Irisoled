<img width="896" height="288" alt="IrisOled Logo 3d" src="https://github.com/user-attachments/assets/45d72a1a-9e4f-408f-a2d3-3ade6a18af2f" />

# IrisOLED
Arduino library for robotic OLED eye expressions for SSD1306 / SH1106 and other Adafruit-GFX-compatible displays

IrisOLED provides a collection of monochrome bitmaps (robotic eye expressions and useful icons) plus a small non-blocking animation helper so you can make expressive robot eyes without blocking the rest of your code.

# Table of contents
* [Features](#features)
* [Install](#install)
* [Quick start](#quick-start)
* [Irisoled bitmaps](#irisoled-bitmaps)
* [IrisoledAnimation - API Reference]
* [Examples overview]
* [PROGMEM notes & memory tips]
* [Driver compatibility (SSD1306 / SH1106)]
* [Contributing]

## Features
* 32 pre-made robotic eye expressions and icons.
* IrisoledAnimation - a lightweight, non-blocking animation player compatible with multiple display drivers.

## Install
1. Download or clone this repository.
2. Copy the Irisoled folder to your Arduino libraries/ directory, or use **Sketch → Include Library → Add .ZIP Library**... to install the ZIP.
3. Restart the Arduino IDE.
4. Examples will appear under **File → Examples → Irisoled**.

## Quick start
```c++
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Irisoled.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  // draw a full-screen bitmap stored in PROGMEM
  display.drawBitmap(0, 0, Irisoled::normal, 128, 64, WHITE);
  display.display();
}

void loop() {
}
```

## IrisOLED bitmaps
All bitmaps are declared under the `Irisoled` namespace in `Irisoled.h` and defined in `Irisoled.cpp` in PROGMEM.

### Names included
* `Irisoled::alert`, `Irisoled::angry`, `Irisoled::blink_down`, `Irisoled::blink_up`, `Irisoled::blink`, `Irisoled::bored`, `Irisoled::despair`, `Irisoled::disoriented`,
* `Irisoled::excited`, `Irisoled::focused`, `Irisoled::furious`, `Irisoled::happy`, `Irisoled::look_down`, `Irisoled::look_left`, `Irisoled::look_right`, Irisoled::look_up`,
* `Irisoled::normal`, `Irisoled::sad`, `Irisoled::scared`, `Irisoled::sleepy`, `Irisoled::surprised`, `Irisoled::wink_left`, `Irisoled::wink_right`, `Irisoled::worried`,
* `Irisoled::battery_full`, `Irisoled::battery_low`, `Irisoled::battery`, `Irisoled::left_signal`, `Irisoled::logo`, `Irisoled::mode`, `Irisoled::right_signal`, `Irisoled::warning`.

Use `display.drawBitmap(x, y, Irisoled::<name>, width, height, WHITE);`








