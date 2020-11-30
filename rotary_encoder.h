// Zerbinati Alberto

#pragma once

class RotaryEncoder
{
public:
  RotaryEncoder(){};
  RotaryEncoder(int _pinS1, int _pinS2, int _pinKey); //deve fare anche setup (pinMode = INPUT)

  bool isButtonPressed();
  String turnDirection(); //"" -> nulla, "dx" -> destra, "sx" -> sinistra

private:
  int pinS1 = 0;
  int pinS2 = 0;
  int pinKey = 0;

  int prevS1 = 0;
  int prevS2 = 0;
  int prevButtonState = 0;
  
  int buttonState = 0;
  int counter = 0;

  void updateCounter();
};
