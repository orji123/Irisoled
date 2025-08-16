/***************************************************
  Irisoled - Robotic OLED Eye Expressions Library
  Copyright (c) 2025 Chijindu-Orji Iseh-Ntah

  Licensed under the MIT License.
  See license.txt for details.
  
  IrisoledAnimation.h
  Non-blocking animation helper for Irisoled bitmaps (PROGMEM)
****************************************************/

#ifndef IRISOLEDANIMATION_H
#define IRISOLEDANIMATION_H

#include <Arduino.h>
#include <Adafruit_GFX.h>

class IrisoledAnimation {
public:
  typedef void (*FrameCallback)(uint8_t newIndex);

  // RAM-frames constructor
  IrisoledAnimation(const unsigned char* frames[],
                    uint8_t frameCount,
                    const uint16_t* delays = nullptr,
                    uint16_t frameDelay = 200,
                    bool loop = true);

  // PROGMEM-frames constructor
  IrisoledAnimation(const unsigned char* const framesPROGMEM[],
                    uint8_t frameCount,
                    bool framesInPROGMEM,
                    const uint16_t* delays = nullptr,
                    uint16_t frameDelay = 200,
                    bool loop = true);

  // control
  void start(uint8_t startFrame = 0);
  void stop();
  void resume();
  void reset();
  void setLoop(bool loop);
  void setFrameDelay(uint16_t ms);
  void setDelays(const uint16_t* delays);
  void setFrameCallback(FrameCallback cb);

  // query
  uint8_t getCurrentFrame() const;
  uint8_t getFrameCount() const;
  bool isRunning() const;

  // ---- templated update: accepts any display object that exposes:
  //      clearDisplay(), drawBitmap(x,y,ptr,w,h,color), display()
  //    This works with Adafruit_SSD1306, Adafruit_SH1106, and similar drivers.
  template<typename Display>
  void update(Display &display, int16_t x, int16_t y, uint8_t w, uint8_t h);

private:
  const unsigned char* getFramePtr(uint8_t index) const;

  const unsigned char** _framesRAM;
  const unsigned char* const* _framesPROG;
  bool _framesInPROGMEM;

  const uint16_t* _delays;
  uint16_t _fallbackDelay;

  uint8_t _frameCount;
  bool _loop;
  uint8_t _current;
  unsigned long _lastMillis;
  bool _running;

  FrameCallback _onFrameChange;
};

// --------------------- Implementation ---------------------

#if defined(__AVR__)
  #include <avr/pgmspace.h>
  #define IR_READ_PTR_FROM_PROGMEM(ptr) ((const unsigned char*)pgm_read_ptr(&(ptr)))
#else
  #define IR_READ_PTR_FROM_PROGMEM(ptr) (ptr)
#endif

template<typename Display>
void IrisoledAnimation::update(Display &display, int16_t x, int16_t y, uint8_t w, uint8_t h) {
  if (!_running || _frameCount == 0) return;

  unsigned long now = millis();

  // get current bitmap pointer (handles PROGMEM pointer arrays)
  const unsigned char* bmp = getFramePtr(_current);
  if (bmp) {
    // draw and show using the concrete display's API
    display.clearDisplay();
    display.drawBitmap(x, y, bmp, w, h, 1); // color value 1 => WHITE for monochrome
    display.display();
  }

  uint16_t delayMs = (_delays != nullptr) ? _delays[_current] : _fallbackDelay;

  if ((unsigned long)(now - _lastMillis) >= (unsigned long)delayMs) {
    _lastMillis = now;
    uint8_t prev = _current;
    _current++;
    if (_current >= _frameCount) {
      if (_loop) _current = 0;
      else { _current = _frameCount - 1; _running = false; }
    }
    if (_onFrameChange && _current != prev) _onFrameChange(_current);
  }
}

#undef IR_READ_PTR_FROM_PROGMEM

#endif // IRISOLEDANIMATION_H
