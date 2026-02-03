#ifndef BUTTON_H
#define BUTTON_H

#include <cstdint>

enum class ButtonEvent : uint8_t 
{ 
    None, 
    ShortPress, 
    LongPress 
};

class Button {
public:
    Button(uint8_t pin, bool pressedIsLow = false)
      : m_pin(pin), m_pressedIsLow(pressedIsLow) {}

    ButtonEvent poll();

private:
    bool rawPressed(bool level) const {
        return m_pressedIsLow ? !level : level;
    }

    uint8_t  m_pin;
    bool     m_pressedIsLow;

    bool     m_lastReading = true;
    bool     m_stableState = true;
    uint32_t m_lastChangeMs = 0;

    uint32_t m_pressStartMs = 0;
    bool     m_longFired = false;
};

#endif