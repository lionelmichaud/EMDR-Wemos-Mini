#define STRIP_PIN 4
#define STRIP_NUM_LED 60

enum State {running = 1, stopped = 0};
enum Direction {up = 1, down = -1};

class LedStrip {

  public:
    // Constructeurs
    LedStrip(int speed, CRGB initialColor);
    LedStrip(int speed);

    //Accesseurs et mutateurs
    void setup(); // call only once in the main program setup() function
    void start();
    void stop();
    void show();

    void setSpeed(int speed);
    void setColor(CRGB color);
    void setBrightness(uint8_t brightness);
    void setEyeWidth(int width);
    int getSpeed() const;
    
  private:
    void moveLight();
    void nextPos();

    const int pin    = STRIP_PIN;
    const int numLed = STRIP_NUM_LED;
    const int pauses[10] = {90, 80, 70, 60, 50, 40, 30, 20, 10, 0};
    CRGB leds[STRIP_NUM_LED];
    enum State state = stopped;
    enum Direction dir = up;
    int  speed = 1;
    int  pos   = 0;
    CRGB color = CRGB::Blue;
    uint8_t brightness = 255;
    int eyeWidth = 1;
};

inline LedStrip::LedStrip(int speed, CRGB initialColor) {
  this->speed = speed;
  for (int i = 0; i < numLed; i++) {
    leds[i] = initialColor;
  }
}

inline LedStrip::LedStrip(int speed) {
  this->speed = speed;
  for (int i = 0; i < numLed; i++) {
    leds[i] = CRGB::Black;
  }
}

inline void LedStrip::start() {
  this->pos = 0;
  this->state = running;
}

inline void LedStrip::stop() {
  this->state = stopped;
}

inline void LedStrip::setSpeed(int speed) {
  this->speed = speed;
}

inline void LedStrip::setColor(CRGB color) {
  this->color = color;
}

inline void LedStrip::setBrightness(uint8_t brightness) {
  this->brightness = brightness;
  FastLED.setBrightness(brightness);
}

inline void LedStrip::setEyeWidth(int width) {
  this->eyeWidth = width;
}

inline int LedStrip::getSpeed() const {
  return this->speed;
}

inline void LedStrip::nextPos() {
  switch (dir)
  {
    case up:
      if (pos == numLed - 1) {
        dir = down;
        this->nextPos();
      } else {
        pos++;
      };
      break;

    case down:
      if (pos == 0) {
        dir = up;
        this->nextPos();
      } else {
        pos--;
      };
      break;
  }
  delay(this->pauses[speed - 1]);
}

inline void LedStrip::moveLight() {
  leds[pos] = CRGB::Black;
  this->nextPos();
  leds[pos] = color;
}

inline void LedStrip::show() {
  switch (state)
  {
    case running:
      this->moveLight();
      FastLED.show();
      break;

    case stopped:
      break;
  }
}

inline void LedStrip::setup() {
  FastLED.addLeds<NEOPIXEL, STRIP_PIN>(leds, numLed);
}
