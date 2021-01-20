class Switch {
  public:
    // Constructeurs
    Switch(int pin, bool initialState);

    //Accesseurs et mutateurs
    bool sampleState();
    bool stateChanged();

    bool getState() const;
    void setState(bool state);

  private:
    int pin;
    bool previousState;
    bool state;
};

inline Switch::Switch(int pin, bool initialState) {
  pinMode(pin, INPUT);      // sets the digital pin as input
  this->pin   = pin;
  this->previousState = initialState;
  this->state = initialState;
}

inline bool Switch::sampleState() {
  // roll-over
  previousState = state;
  // acquisition
  state = digitalRead(this->pin);   // read the input pin

  return state;
}

inline bool Switch::stateChanged() {
  return (previousState != state);
}


inline void Switch::setState(bool state) // définition au sein de la classe (inline)
{
  this->state = state;
}

inline bool Switch::getState() const // définition au sein de la classe (inline)
{
  return this->state;
}
