long mapIntToFloat(long x, long in_min, long in_max, float out_min, float out_max)
{
  return float(x - in_min) * (out_max - out_min) / float(in_max - in_min) + out_min;
}

class Potentiometer {
  public:
    // Constructeurs
    Potentiometer(int pin, int minValue, int maxValue, int initialRawValue);

    //Accesseurs et mutateurs
    int sampleValue();
    bool valueChanged();

    int getRawValue() const;
    void setRawValue(int rawValue);

    int getValue() const;
    void setValue(int value);

  private:
    void convertRawValueToValue();

    int   pin;
    int   minValue;
    int   maxValue;
    int   rawValue;
    float previousRawValue;
    float value;
};

inline Potentiometer::Potentiometer(int pin, int minValue, int maxValue, int initialRawValue) {
  this->pin      = pin;
  this->minValue = minValue;
  this->maxValue = maxValue;
  this->rawValue = initialRawValue;
  this->previousRawValue = initialRawValue;
  this->value = 0.0;
}

inline void Potentiometer::convertRawValueToValue() {
  this->value = map(rawValue, 0, 1023, this->minValue, this->maxValue);
}

inline int Potentiometer::sampleValue() {
  // roll-over
  previousRawValue = rawValue;  // acquisition
   // acquisition
 rawValue = analogRead(A0);

  // conversion
  this->convertRawValueToValue();

  return value;
}

inline bool Potentiometer::valueChanged() {
  return (previousRawValue != rawValue);
}

inline void Potentiometer::setValue(int value) // définition au sein de la classe (inline)
{
  this->value = value;
}

inline int Potentiometer::getValue() const // définition au sein de la classe (inline)
{
  return this->value;
}

inline void Potentiometer::setRawValue(int rawValue) // définition au sein de la classe (inline)
{
  this->rawValue = rawValue;
  // conversion
  this->convertRawValueToValue();
}

inline int Potentiometer::getRawValue() const // définition au sein de la classe (inline)
{
  return this->rawValue;
}
