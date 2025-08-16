/***************************************************
  Irisoled - Robotic OLED Eye Expressions Library
  Copyright (c) 2025 Chijindu-Orji Iseh-Ntah

  Licensed under the MIT License.
  See license.txt for details.

  IrisoledAnimation.cpp
****************************************************/

#include "IrisoledAnimation.h"

// For reading pointers stored in PROGMEM on AVR
#if defined(__AVR__)
  #include <avr/pgmspace.h>
#endif

// Helper: read pointer from PROGMEM on AVR, direct on other archs
#if defined(__AVR__)
  #define IR_READ_PTR(ptr) ((const unsigned char*)pgm_read_ptr(&(ptr)))
#else
  #define IR_READ_PTR(ptr) (ptr)
#endif

// RAM-frames constructor
IrisoledAnimation::IrisoledAnimation(const unsigned char* frames[],
                                     uint8_t frameCount,
                                     const uint16_t* delays,
                                     uint16_t frameDelay,
                                     bool loop) :
  _framesRAM((const unsigned char**)frames),
  _framesPROG(nullptr),
  _framesInPROGMEM(false),
  _delays(delays),
  _fallbackDelay(frameDelay),
  _frameCount(frameCount),
  _loop(loop),
  _current(0),
  _lastMillis(0),
  _running(false),
  _onFrameChange(nullptr)
{}

// PROGMEM-frames constructor
IrisoledAnimation::IrisoledAnimation(const unsigned char* const framesPROGMEM[],
                                     uint8_t frameCount,
                                     bool framesInPROGMEM,
                                     const uint16_t* delays,
                                     uint16_t frameDelay,
                                     bool loop) :
  _framesRAM(nullptr),
  _framesPROG(framesPROGMEM),
  _framesInPROGMEM(framesInPROGMEM),
  _delays(delays),
  _fallbackDelay(frameDelay),
  _frameCount(frameCount),
  _loop(loop),
  _current(0),
  _lastMillis(0),
  _running(false),
  _onFrameChange(nullptr)
{}

// Start animation
void IrisoledAnimation::start(uint8_t startFrame) {
  if (_frameCount == 0) return;
  _current = (startFrame < _frameCount) ? startFrame : 0;
  _lastMillis = millis();
  _running = true;
  if (_onFrameChange) _onFrameChange(_current);
}

// Stop/pause
void IrisoledAnimation::stop() {
  _running = false;
}

// Resume
void IrisoledAnimation::resume() {
  if (_frameCount == 0) return;
  _lastMillis = millis();
  _running = true;
}

// Reset
void IrisoledAnimation::reset() {
  _current = 0;
  _running = false;
  _lastMillis = 0;
}

// Set looping
void IrisoledAnimation::setLoop(bool loop) {
  _loop = loop;
}

// Set uniform delay
void IrisoledAnimation::setFrameDelay(uint16_t ms) {
  _fallbackDelay = ms;
}

// Set per-frame delays array
void IrisoledAnimation::setDelays(const uint16_t* delays) {
  _delays = delays;
}

// Set callback
void IrisoledAnimation::setFrameCallback(FrameCallback cb) {
  _onFrameChange = cb;
}

// Query functions
uint8_t IrisoledAnimation::getCurrentFrame() const { return _current; }
uint8_t IrisoledAnimation::getFrameCount() const { return _frameCount; }
bool IrisoledAnimation::isRunning() const { return _running; }

// Get pointer to bitmap for index, handling PROGMEM pointer-array if needed
const unsigned char* IrisoledAnimation::getFramePtr(uint8_t index) const {
  if (index >= _frameCount) return nullptr;

  if (_framesInPROGMEM && _framesPROG != nullptr) {
    return IR_READ_PTR(_framesPROG[index]);
  } else if (_framesRAM != nullptr) {
    return _framesRAM[index];
  } else {
    return nullptr;
  }
}

#undef IR_READ_PTR
