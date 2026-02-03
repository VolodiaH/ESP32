#include "Blinker.h"


void Blinker::begin(uint32_t nowMs) 
{
    m_lastFireMs = nowMs;
    m_ledState = Level::Low;
    Board::write(m_pin, m_ledState);
}

void Blinker::sync(uint32_t timeoutMs, uint32_t nowMs, Level startState)
{
    if (m_timeoutMs != timeoutMs) 
    {
        m_timeoutMs = timeoutMs;
        m_ledState = startState;
        Board::write(m_pin, m_ledState);
        m_lastFireMs = nowMs;
    }
}

void Blinker::update(uint32_t nowMs)
{
    if ((nowMs - m_lastFireMs) >= m_timeoutMs) 
    {
        m_lastFireMs = nowMs;
        m_ledState = (m_ledState == Level::Low) ? Level::High : Level::Low;
        Board::write(m_pin, m_ledState);
    }
}