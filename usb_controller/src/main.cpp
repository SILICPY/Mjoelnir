#include <Arduino.h>

#include <Adafruit_NeoPixel.h>

#define CURRENT_3A_CC_VOLTAGE 1.31
#define CURRENT_3A_CC_ADC_THRESH ((CURRENT_3A_CC_VOLTAGE / 5) * 1024)

#define CC1_PIN A1
#define CC2_PIN A2
#define RST_PIN PB0

#define PIN_MASK ((1 << RST_PIN) | (1 << LED_BUILTIN))

#define PIXEL_PIN PB3
#define PIXEL_COUNT 70
#define US_SLIP PIXEL_COUNT * 30
#define ENABLE_DELAY 250

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
unsigned long updateCycles = 0;
unsigned long enableTime = millis();

void setStatus(bool enabled) {
  PORTB = (PORTB & (0xff ^ PIN_MASK)) | (enabled ? 1 << RST_PIN : 1 << LED_BUILTIN);

  if (enabled) { // && (!updateCycles || (millis() - enableTime) > ENABLE_DELAY)) {
    updateCycles = 0;
    enableTime = millis();
    pinMode(PIXEL_PIN, INPUT);
  } else {
    pinMode(PIXEL_PIN, OUTPUT);
    for (size_t i = 0; i < 3; ++i) {
      pixels.setPixelColor(16 + i, pixels.Color(50 * abs(sin((millis() / 4000.0) * 2.0 * PI)), 0, 0));
      pixels.setPixelColor(51 + i, pixels.Color(50 * abs(sin((millis() / 4000.0) * 2.0 * PI)), 0, 0));
    }
    pixels.show();
    ++updateCycles;
  }
}

void setup() {
  DDRB |= PIN_MASK;
  setStatus(false);

  pixels.begin();
}

void loop() {
  if (analogRead(CC1_PIN) > (int) CURRENT_3A_CC_ADC_THRESH || analogRead(CC2_PIN) > (int) CURRENT_3A_CC_ADC_THRESH) {
    setStatus(true);
  } else {
    setStatus(false);
  }
}