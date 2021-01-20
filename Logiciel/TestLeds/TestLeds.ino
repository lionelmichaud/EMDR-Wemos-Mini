#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#include "FastLED.h"

#include "Switch.h"
#include "Potentiometer.h"
#include "LedStrip.h"

//-------------------------------------------------
//   DEFINE
//-------------------------------------------------
// VERSION NUMBER
#define SOFTWARE "EMDR"
#define VERSION "0.0.0"

#define ECHO    // Echo des réglages sur la liaison série
#define DEBUG

// LEDs
#define NUM_LEDS 60
#define DATA_PIN 4 // GPIO2

// SWITCHs
#define SW11_PIN 6 // GPI12
#define SW12_PIN 7 // GPI13
#define SW21_PIN 0 // GPI16
#define SW22_PIN 5 // GPI14

// POTENTIOMETER
#define speedPotar_PIN A0 // A0

//-------------------------------------------------
// --- Déclaration des types ---
//-------------------------------------------------
struct SwitchesState {
  CRGB colorSwitch     = CRGB::White;
  int brigthnessSwitch = 0;
  bool displaySwitch   = false;
  bool remoteSwitch    = false;
};

//-------------------------------------------------
// --- Déclaration des constantes globales ---
//-------------------------------------------------
const CRGB ledColor = CRGB::Red;

//-------------------------------------------------
// --- Déclaration des variables globales ---
//-------------------------------------------------
// création des dip switch
Switch SW11(SW11_PIN, false), SW12(SW12_PIN, false);
Switch SW21(SW21_PIN, false), SW22(SW22_PIN, false);

// création du speedPotar
Potentiometer speedPotar(speedPotar_PIN, 1, 10, 0);

// création du LedStrip
LedStrip ledStrip(1, CRGB::White);

// état courant des switch
SwitchesState switches;

// vitesse courante de défielement
int speed;

CRGB leds[NUM_LEDS];

//-------------------------------------------------
// --- Fonctions globales ---
//-------------------------------------------------
// Test des LEDs
//----------------
void test() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  leds[0] = CRGB::White; FastLED.show(); delay(300);
  leds[0] = CRGB::Black; FastLED.show(); delay(300);

  leds[0] = CRGB::Red; FastLED.show(); delay(300);
  leds[0] = CRGB::Black; FastLED.show(); delay(300);

  for (int dot = 0; dot < NUM_LEDS; dot++) {
    leds[dot] = CRGB::Blue;
    FastLED.show();
    // clear this led for the next time around the loop
    leds[dot] = CRGB::Black;
    delay(30);
  }
}

void printState() {
  Serial.print("Vitesse    = "); Serial.println(speed);
  Serial.print("Luminosité = "); Serial.println(switches.brigthnessSwitch);
  Serial.print("Display    = "); Serial.println(switches.displaySwitch);
  Serial.print("Remote     = "); Serial.println(switches.remoteSwitch);
}

// Echantillonage des switchs
//---------------------------
SwitchesState sampleSwitchStates() {
  SwitchesState state;

  bool sw11 = SW11.sampleState();
  if (sw11) {
    state.colorSwitch = CRGB::Blue;
  } else {
    state.colorSwitch = CRGB::Green;
  };
  if (SW11.stateChanged()) {
    ledStrip.setColor(state.colorSwitch);
  };

  bool sw12 = SW12.sampleState();
  if (sw12) {
    state.brigthnessSwitch = 255;
  } else {
    state.brigthnessSwitch = 100;
  };
  if (SW12.stateChanged()) {
    ledStrip.setEyeWidth(state.brigthnessSwitch);
  };

  state.displaySwitch = SW21.sampleState();
  state.remoteSwitch  = SW22.sampleState();

  return state;
}

//=====================================================================
// SETUP
//=====================================================================
void setup() {
#if defined ECHO
  Serial.begin(115200);
#endif

#if defined DEBUG
  test();
#endif

  ledStrip.setup();

  // acquisition
  switches = sampleSwitchStates();
  speed = speedPotar.sampleValue();

  // régler la vitesse
  ledStrip.setSpeed(speed);

  // démarrer le défilement
  ledStrip.start();
}

//=====================================================================
// LOOP (EXECUTES ON CORE 1 BY DEFAULT)
//=====================================================================
void loop() {
  // acquisition
  switches = sampleSwitchStates();
  speed = speedPotar.sampleValue();

  // modifier la vitesse si nécessaire
  if (speedPotar.valueChanged()) {
    ledStrip.setSpeed(speed);
  }

#if defined ECHO
  printState();
#endif

  ledStrip.show();
}
