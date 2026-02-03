// Blinker.h
#ifndef BLINKER_H
#define BLINKER_H

#include <cstdint>
#include "Board.h"

class Blinker
{
public:
    Blinker(uint8_t pin, uint32_t timeoutMs)
        : m_pin(pin), m_timeoutMs(timeoutMs) {}

    void begin(uint32_t nowMs = Board::millis());
    void update(uint32_t nowMs = Board::millis());
    void sync(uint32_t timeoutMs, uint32_t nowMs, Level startState = Level::Low);

private:
    uint8_t  m_pin;
    uint32_t m_timeoutMs;
    uint32_t m_lastFireMs = 0;
    Level    m_ledState = Level::Low;
};

#endif