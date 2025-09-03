
<p align="center">
  <img src="https://github.com/user-attachments/assets/45d72a1a-9e4f-408f-a2d3-3ade6a18af2f" alt="IrisOled Logo" width="700"/>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/platform-Arduino-lightgrey" alt="Platform: Arduino"/> 
  <img src="https://img.shields.io/badge/license-MIT-blue" alt="License: MIT"/>
  <img src="https://img.shields.io/badge/display-SSD1306%20%7C%20SH1106-lightgrey" alt="Displays"/>
</p>

# IrisOLED

**IrisOLED** is an Arduino library for expressive robotic OLED eyes using SSD1306 / SH1106 and other Adafruit-GFX-compatible displays.  
It provides a collection of monochrome bitmaps (eye expressions + useful icons) and a small non-blocking animation helper so you can add personality to robots without blocking the rest of your code.

<p align="center">
  <img width="700" height="481" alt="irisoled_all" src="https://github.com/user-attachments/assets/2d1cdcb3-5954-425f-b017-8332df16dc21" />
</p>

---

## Table of Contents
- [Features](#features)
- [Install](#install)
- [Quick Start](#quick-start)
- [IrisOLED Bitmaps](#irisoled-bitmaps)
- [IrisOLED Animation](#irisoled-animation)
- [Driver Compatibility and Required Libraries](#driver-compatibility-and-required-libraries)
- [Examples](#examples)
- [License](#license)
- [Contact](#contact)

---

## Features
- **32 pre-made robotic eye expressions and icons**
- **IrisoledAnimation** — lightweight, non-blocking animation player compatible with multiple display drivers
- Works with **SSD1306** and **SH1106** OLED displays
- Compatible with the **Adafruit GFX** API (`drawBitmap`, `clearDisplay`, `display`)
- Examples included for quick testing

---

## Install

1. Download or clone this repository:
   ```bash
   git clone https://github.com/orji123/Irisoled.git
   ```
2. Copy the `Irisoled` folder into your Arduino `libraries/` directory **OR** use:
   **Sketch → Include Library → Add .ZIP Library** and select the ZIP of this repo.
3. Restart the Arduino IDE.
4. Examples will appear under **File → Examples → Irisoled**.

---

## Quick Start

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
  // your code here
}
```

---

## IrisOLED Bitmaps

All bitmaps are declared under the `Irisoled` namespace in `Irisoled.h` and defined in `Irisoled.cpp` in `PROGMEM`.

### Included Names
`Irisoled::alert`, `Irisoled::angry`, `Irisoled::blink_down`, `Irisoled::blink_up`, `Irisoled::blink`, `Irisoled::bored`, `Irisoled::despair`, `Irisoled::disoriented`,  
`Irisoled::excited`, `Irisoled::focused`, `Irisoled::furious`, `Irisoled::happy`, `Irisoled::look_down`, `Irisoled::look_left`, `Irisoled::look_right`, `Irisoled::look_up`,  
`Irisoled::normal`, `Irisoled::sad`, `Irisoled::scared`, `Irisoled::sleepy`, `Irisoled::surprised`, `Irisoled::wink_left`, `Irisoled::wink_right`, `Irisoled::worried`,  
`Irisoled::battery_full`, `Irisoled::battery_low`, `Irisoled::battery`, `Irisoled::left_signal`, `Irisoled::logo`, `Irisoled::mode`, `Irisoled::right_signal`, `Irisoled::warning`.

**Usage**:
```c++
display.drawBitmap(x, y, Irisoled::<name>, width, height, WHITE);
```

---

## IrisOLED Animation

**IrisoledAnimation** is a non-blocking player that renders frames and advances using `millis()` (no `delay()` calls). The `update()` method is templated so it works with any Adafruit-GFX-compatible display object.

### Constructors

```c++
// RAM pointer array
IrisoledAnimation(const unsigned char* frames[],
                  uint8_t frameCount,
                  const uint16_t* delays = nullptr,
                  uint16_t frameDelay = 200,
                  bool loop = true);

// PROGMEM pointer-array variant
IrisoledAnimation(const unsigned char* const framesPROGMEM[],
                  uint8_t frameCount,
                  bool framesInPROGMEM,
                  const uint16_t* delays = nullptr,
                  uint16_t frameDelay = 200,
                  bool loop = true);
```

### Public Methods
- `start(uint8_t startFrame = 0)` — Start/restart from a frame.  
- `stop()` — Pause animation.  
- `resume()` — Resume if paused.  
- `reset()` — Reset to first frame without starting.  
- `setLoop(bool loop)` — Enable/disable looping.  
- `setFrameDelay(uint16_t ms)` — Uniform frame delay when no per-frame delays provided.  
- `setDelays(const uint16_t* delays)` — Provide per-frame delays (ms).  
- `setFrameCallback(FrameCallback cb)` — Register `void cb(uint8_t newIndex)` called on frame change.  
- `update(display, x, y, w, h)` — Call from `loop()`. Draws current frame to `display` and advances frames when their delay elapses.  
- `getCurrentFrame()` — Get current frame index.  
- `getFrameCount()` — Total number of frames.  
- `isRunning()` — True if animation is currently playing.

---

## Driver Compatibility

The animation helper is driver-agnostic. In your sketch always include:

```c++
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> // or <Adafruit_SH1106.h>
```

### Required Libraries
- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)  
- [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306) (for SSD1306 displays)  
- [Adafruit SH1106](https://github.com/wonho-maker/Adafruit_SH1106) (if using SH1106-based displays)  
- Any other display driver that implements the Adafruit-GFX API (`clearDisplay()`, `drawBitmap()`, `display()`)

---

## Examples

See the `examples/` folder in this repository for ready-to-run sketches. Typical examples demonstrate:
- Drawing a single expression bitmap
- Running a blink animation using `IrisoledAnimation`
- Switching expressions based on input (sensors/buttons)

---

## License

This project is released under the **MIT License**. See `LICENSE` for details.

---

## Contact

Maintainer: **Chijindu-Orji Iseh-Ntah"**  
E-mail Address: chijipeters2@gmail.com

---
