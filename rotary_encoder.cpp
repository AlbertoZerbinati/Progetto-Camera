// Zerbinati Alberto

#include "Arduino.h" //setta lo scope corretto (pinMode, INPUT,...)
#include "rotary_encoder.h"

RotaryEncoder::RotaryEncoder(int _pinS1, int _pinS2, int _pinKey) {
  //setup encoder
  pinS1 = _pinS1;
  pinS2 = _pinS2;
  pinKey = _pinKey;

  prevButtonState = 0;
  buttonState = 0;
  counter = 0;

  pinMode(pinS1, INPUT);
  pinMode(pinS2, INPUT);
  pinMode(pinKey, INPUT);
  prevS1 = digitalRead(pinS1);
  prevS2 = digitalRead(pinS2);
}

String RotaryEncoder::turnDirection() {
  String ret = "";
  int currS1 = digitalRead(pinS1);
  int currS2 = digitalRead(pinS2);

  if (currS1 != prevS1 && currS1 == HIGH) {
    if (currS2 == currS1) {
      ret = "dx";
    }
    else {
      ret = "sx";
    }
  } 
  prevS1 = currS1;
  return ret;
}

bool RotaryEncoder::isButtonPressed() {
  buttonState = digitalRead(pinKey);
  bool ret = (buttonState == LOW && buttonState != prevButtonState);
  prevButtonState = buttonState;

  return ret;
}
