#ifndef BOARD_H
#define BOARD_H

#include <cstdint>
enum class Level : uint8_t { Low, High };

#ifdef ESP_PLATFORM

#include "Arduino.h"

struct Board 
{
  using Pin = uint8_t;

  //static void pinModeOut(Pin p) { ::pinMode(p, OUTPUT); }
  static void write(Pin p, Level v) { ::digitalWrite(p, v == Level::High ? HIGH : LOW); }
  static int read(Pin p) { return ::digitalRead(p); }
  static uint32_t millis() { return ::millis(); }
};
#endif


///////////////////////////////////////////////////////
#ifdef PLATFORM_STM32

struct Board 
{
  using Pin = StmPin;

  // static void pinModeOut(Pin /*p*/) 
  // {
  //   // usually already configured by CubeMX; otherwise init here
  // }
  static void write(Pin p, Level v) 
  {
    HAL_GPIO_WritePin(p.port, p.pin, v == Level::High ? GPIO_PIN_SET : GPIO_PIN_RESET);
  }
  static uint32_t millis() { return HAL_GetTick(); }
};
#endif

#endif