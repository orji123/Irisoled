<p align="center">
  <img src="https://github.com/user-attachments/assets/45d72a1a-9e4f-408f-a2d3-3ade6a18af2f" alt="IrisOLED Logo" width="500"/>
</p>

# IrisOLED

Arduino library for expressive robotic OLED eyes 👁️  
(SSD1306 / SH1106 and other Adafruit-GFX-compatible displays)

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/orji123/Irisoled/blob/main/LICENSE)
[![Dependency: Adafruit GFX](https://img.shields.io/badge/dependency-Adafruit%20GFX-green.svg)](https://github.com/adafruit/Adafruit-GFX-Library)
[![GitHub stars](https://img.shields.io/github/stars/orji123/Irisoled?style=social)](https://github.com/orji123/Irisoled/stargazers)

---

## Table of contents

- [Features](#features)
- [Install](#install)
- [Quick Start](#quick-start)
- [IrisOLED Bitmaps](#irisoled-bitmaps)
  - [Names included](#names-included)
  - [Using the bitmaps](#using-the-bitmaps)
- [IrisOLED Animation](#irisoled-animation)
  - [Constructors](#constructors)
  - [Public methods](#public-methods)
  - [Example usage](#example-usage)
- [Driver compatibility & required libraries](#driver-compatibility--required-libraries)
- [Dependencies](#dependencies)
- [License](#license)

---

## Features

- 32+ pre-made robotic eye expressions and icons  
- `IrisoledAnimation` — lightweight, non-blocking animation player  
- Works with SSD1306, SH1106, and any Adafruit-GFX-compatible driver  
- Example sketches included

---

## Install

1. **Download or clone** this repository.  
2. Copy the `Irisoled` folder into your Arduino `libraries/` directory, **or** use:  
   `Sketch → Include Library → Add .ZIP Library…` and pick the repo ZIP.  
3. Restart the Arduino IDE.  
4. Examples appear under `File → Examples → Irisoled`.

---

## Quick Start

```cpp
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Irisoled.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  // draw a full-screen bitmap from Irisoled
  display.drawBitmap(0, 0, Irisoled::normal, 128, 64, WHITE);
  display.display();
}

void loop() {
```
  // your code
}
