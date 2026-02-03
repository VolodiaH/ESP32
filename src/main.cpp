#include <Arduino.h>
#include "Button.h"
#include "Blinker.h"

constexpr uint8_t LED_PIN_BLUE = 43;
constexpr uint8_t LED_PIN_RED = 37;
constexpr uint8_t LED_PIN_YELLOW = 36;
constexpr uint8_t LED_PIN_GREEN = 35;
constexpr uint8_t BUTTON_PIN_INPUT = 3;
constexpr uint8_t BOOT_PIN_INPUT = 0;

constexpr uint32_t SECOND = 1000;
constexpr uint32_t HALF_SECOND = 500;
constexpr uint32_t QUARTER_SECOND = 250;

void slow();
void fast();
void halfFast();

Button btn(BUTTON_PIN_INPUT);
Button btnBoot(BOOT_PIN_INPUT, true);// boot button press is LOW

Blinker ledGreen(LED_PIN_GREEN, 1000);
Blinker ledYellow(LED_PIN_YELLOW, 1000);

void setup() 
{

  pinMode(LED_PIN_BLUE, OUTPUT);
  pinMode(LED_PIN_RED, OUTPUT);
  pinMode(LED_PIN_YELLOW, OUTPUT);
  pinMode(LED_PIN_GREEN, OUTPUT);
  pinMode(BUTTON_PIN_INPUT, INPUT_PULLUP);
  pinMode(BOOT_PIN_INPUT, INPUT_PULLUP);

  ledGreen.begin();
  ledYellow.begin();

  Serial.begin(115200);
}


enum class Mode {Fast,Slow,Third, None};
Mode mode = Mode::Slow;
Mode lastMode = Mode::Slow;

void loop() 
{ 
    switch (btn.poll())
    {
      case ButtonEvent::ShortPress:
        mode = Mode::Slow;
        break;
      case ButtonEvent::LongPress:
        mode = Mode::Third;
        break;
      default:
        break;
    }

    switch (btnBoot.poll())
    {
      case ButtonEvent::ShortPress:
        mode = Mode::Fast;
        break;
      case ButtonEvent::LongPress:
        mode = Mode::Third;
        break;
      default:
        break;
    }

    if (mode != lastMode) 
    {

      lastMode = mode;

      switch (mode) 
      {
        case Mode::Fast:  fast();  break;
        case Mode::Slow:  slow();  break;
        case Mode::Third: halfFast(); break;
      }
    }
    ledGreen.update();
    ledYellow.update();
}

void fast() 
{
  const uint32_t now = Board::millis();
  ledGreen.sync(QUARTER_SECOND, now, Level::Low);
  ledYellow.sync(QUARTER_SECOND, now, Level::Low);
}

void slow() 
{
  const uint32_t now = Board::millis();
  ledGreen.sync(SECOND, now, Level::Low);
  ledYellow.sync(SECOND, now, Level::Low);
}

void halfFast() 
{
  const uint32_t now = Board::millis();
  ledGreen.sync(HALF_SECOND, now, Level::Low);
  ledYellow.sync(HALF_SECOND, now, Level::Low);
}