#include <Arduino.h>
#include <chrono>

constexpr size_t LED_PIN_BLUE = 43;
constexpr size_t LED_PIN_RED = 37;
constexpr size_t LED_PIN_YELLOW = 36;
constexpr size_t LED_PIN_GREEN = 35;

void policeLeds();
void trafficLights();

void setup() 
{
  pinMode(LED_PIN_BLUE, OUTPUT);
  pinMode(LED_PIN_RED, OUTPUT);
  pinMode(LED_PIN_YELLOW, OUTPUT);
  pinMode(LED_PIN_GREEN, OUTPUT);
}

void loop() 
{
  //trafficLights();
  policeLeds();
}

struct Step 
{
  uint8_t pin;
  uint16_t on_ms;
  uint16_t off_ms;
  uint8_t repeats;
};

constexpr uint16_t SECUND_DELAY = 1000;
constexpr uint16_t HALF_SECUND_DELAY = 500;

constexpr uint8_t BLINK = 1;
constexpr uint8_t YELLOW_BLINKS = 3;

constexpr Step trafficLightsSteps[] = 
{
  { LED_PIN_RED,    SECUND_DELAY * 2, HALF_SECUND_DELAY, BLINK },
  { LED_PIN_YELLOW,  HALF_SECUND_DELAY , HALF_SECUND_DELAY, YELLOW_BLINKS },
  { LED_PIN_GREEN,  SECUND_DELAY * 4, HALF_SECUND_DELAY, BLINK },
};

constexpr Step policeLedsSteps[] = 
{
  { LED_PIN_RED,    HALF_SECUND_DELAY / 2, HALF_SECUND_DELAY / 2, BLINK },
  { LED_PIN_BLUE,  HALF_SECUND_DELAY / 2 , HALF_SECUND_DELAY / 2, BLINK }, // LED_PIN_BLUE
};

template <size_t count>
void runSequence(const Step (&steps)[count])
{
  for (const Step &s : steps) 
  {
    for (uint8_t i {}; i < s.repeats; ++i) 
    {
      digitalWrite(s.pin, HIGH); delay(s.on_ms);
      digitalWrite(s.pin, LOW);  delay(s.off_ms);
    }
  }
}

void trafficLights()
{
    runSequence(trafficLightsSteps);
}

void policeLeds()
{
    runSequence(policeLedsSteps);
}