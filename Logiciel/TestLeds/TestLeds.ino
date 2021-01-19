#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#include "FastLED.h"

#define NUM_LEDS 60
#define DATA_PIN 4 // GPIO2

CRGB leds[NUM_LEDS];
void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}
void loop() {
  leds[0] = CRGB::White; FastLED.show(); delay(30);
  leds[0] = CRGB::Black; FastLED.show(); delay(30);

  leds[0] = CRGB::Red; FastLED.show(); delay(30);
  leds[0] = CRGB::Black; FastLED.show(); delay(30);

  for (int dot = 0; dot < NUM_LEDS; dot++) {
    leds[dot] = CRGB::Blue;
    FastLED.show();
    // clear this led for the next time around the loop
    leds[dot] = CRGB::Black;
    delay(30);
  }
}
