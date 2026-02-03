#include "Button.h"

#include "Board.h"

constexpr uint32_t DEBOUNCE_MS    = 110;
constexpr uint32_t LONG_PRESS_MS  = 800;

ButtonEvent Button::poll()
{
    const uint32_t now = Board::millis();
    const bool reading = Board::read(m_pin);

    if (reading != m_lastReading) 
    {
        m_lastReading = reading;
        m_lastChangeMs = now;
    }

    if ((now - m_lastChangeMs) < DEBOUNCE_MS)
        return ButtonEvent::None;

    if (m_stableState != reading) 
    {
        m_stableState = reading;

        if (rawPressed(m_stableState)) 
        {
            m_pressStartMs = now;
            m_longFired = false;
        }
        else
        {
            if (!m_longFired) 
                return ButtonEvent::ShortPress;
        }
    }

    if (rawPressed(m_stableState) && !m_longFired &&
        (now - m_pressStartMs) >= LONG_PRESS_MS)
    {
        m_longFired = true;
        return ButtonEvent::LongPress;
    }

    return ButtonEvent::None;
}

// ButtonEvent Button::poll()
// {
//     const uint32_t now = Board::millis();
//     bool reading = Board::read(m_pin);

//     if (m_pressedIsLow? !reading : reading)
//     {
//         delay(DEBOUNCE_MS);
//         reading = Board::read(m_pin);
//         if (m_pressedIsLow? !reading : reading)
//             return ButtonEvent::ShortPress;
//     }
//     return ButtonEvent::None;

//     // if (reading != m_lastReading) 
//     // {
//     //     m_lastReading = reading;
//     //     m_lastChangeMs = now;
//     // }
//     // if ((now - m_lastChangeMs) < DEBOUNCE_MS)
//     //     return ButtonEvent::None;

//     // if (m_stableState != reading) 
//     // {
//     //     m_stableState = reading;

//     //     if (m_stableState == LOW) 
//     //     {             
//     //         m_pressStartMs = now;
//     //         m_longFired = false;
//     //     } 
//     //     else 
//     //     {                               
//     //         if (!m_longFired) 
//     //             return ButtonEvent::ShortPress;    
//     //     }
//     // }

//     // if (m_stableState == LOW && !m_longFired 
//     //     && ((now - m_pressStartMs) >= LONG_PRESS_MS)) 
//     // {
//     //     m_longFired = true;
//     //     return ButtonEvent::LongPress;
//     // }

//     // return ButtonEvent::None;
// }