#include <Arduino.h>

#include <Adafruit_NeoPixel.h>

#define CC_VOLTAGE_THRESH_3A 1.31
#define CC_ADC_THRESH_3A (int) ((CC_VOLTAGE_THRESH_3A / 5) * 1024)

#define CC1_PIN A1
#define CC2_PIN A2
#define RST_PIN PB0

#define PIN_MASK ((1 << RST_PIN) | (1 << LED_BUILTIN))

#define PIXEL_PIN PB3
#define PIXEL_COUNT 70
#define US_SLIP (PIXEL_COUNT * 30)

#define SWITCH_DELAY 50

class Timer {
  unsigned long currentTime;
  unsigned long duration;

public:
  void start(unsigned long duration) {
    this->duration = duration;
    this->currentTime = millis();
  }

  bool isExpired() {
    return (millis() - currentTime >= duration);
  }
};

enum State {
  DISABLED,
  SWITCHING,
  ENABLED,
};

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

State currentState;
Timer timer;

void doErrAnim() {
  for (size_t i = 0; i < 3; ++i) {
    pixels.setPixelColor(16 + i, pixels.Color(50 * abs(sin((millis() / 4000.0) * 2.0 * PI)), 0, 0));
    pixels.setPixelColor(51 + i, pixels.Color(50 * abs(sin((millis() / 4000.0) * 2.0 * PI)), 0, 0));
  }
  pixels.show();
}

void updateStatus() {
  PORTB = (PORTB & (0xff ^ PIN_MASK)) | (currentState == State::ENABLED ? 1 << RST_PIN : 1 << LED_BUILTIN);

  if (currentState == State::DISABLED) {
    pinMode(PIXEL_PIN, OUTPUT);
    doErrAnim();
  } else {
    pinMode(PIXEL_PIN, INPUT);
  }
}

void setup() {
  DDRB = PIN_MASK;

  currentState = State::SWITCHING;
  timer.start(SWITCH_DELAY);

  pixels.begin();
}

void loop() {
  if (max(analogRead(CC1_PIN), analogRead(CC2_PIN)) > CC_ADC_THRESH_3A) {
    if (currentState == State::DISABLED) {
      currentState = State::SWITCHING;
      timer.start(SWITCH_DELAY);
    } else if (currentState == State::SWITCHING && timer.isExpired()) {
      currentState = State::ENABLED;
    }
  } else {
    if (currentState == State::ENABLED) {
      currentState = State::SWITCHING;
      timer.start(SWITCH_DELAY);
    } else if (currentState == State::SWITCHING && timer.isExpired()) {
      currentState = State::DISABLED;
    }
  }

  updateStatus();
}