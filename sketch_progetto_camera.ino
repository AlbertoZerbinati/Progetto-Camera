#include <FastLED.h>
#include <Ultrasonic.h>
#include <LiquidCrystal.h>
#include "rotary_encoder.h"

#define NUM_LEDS 144
#define DATA_PIN 13
#define RASPIN 6

#define NUM_MODES 7
#define OFF 0
#define RGBMODE 1
#define WHITE 2
#define COLD 3
#define WARM 4
#define PICK 5
#define TEMP 6

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
CRGB leds[NUM_LEDS];
RotaryEncoder re;

//per colori RGB
int red = 255, green = 0, blue = 0;

//per switch mode
int mode = OFF;
int active_mode = OFF;
String modes[NUM_MODES] = {"Off", "RGB", "White", "Cold", "Warm",  "Pick a color!", "Temperature"};

//INPUT (encoder rotativo)
const int pinKey = 7;
const int pinS1 = 8;
const int pinS2 = 9;

//INPUT analog potenziometro
const int pinPot = A0;


//colorpicker
int previousVal = 0;


void setup() {
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  pinMode(RASPIN, INPUT);
  pinMode(pinPot, INPUT);

  re = RotaryEncoder(pinS1, pinS2, pinKey);

  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
  setMode();

  if (active_mode == OFF) {
    off();
    setMode();
  }
  if (active_mode == RGBMODE) {
    rgbmode();
    setMode();
  }
  if (active_mode == WHITE) {
    white();
    setMode();
  }
  if (active_mode == COLD) {
    cold();
    setMode();
  }
  if (active_mode == WARM) {
    warm();
    setMode();
  }
  if (active_mode == PICK) {
    pick();
    setMode();
  }
  delay(10);
}

void off() {
  FastLED.setBrightness(0);
  FastLED.show();
}

void rgbmode() {
  FastLED.setBrightness(25);

  while (red > 0) {
    setMode(); //controllo sempre se sono in modalità giusta
    if (active_mode != RGBMODE)
      return;

    red--;
    green++;
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(red, green, blue);
    }
    FastLED.show();
  }

  while (green > 0) {
    setMode(); //controllo sempre se sono in modalità giusta
    if (active_mode != RGBMODE)
      return;

    green--;
    blue++;
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(red, green, blue);
    }
    FastLED.show();
  }

  while (blue > 0) {
    setMode(); //controllo sempre se sono in modalità giusta
    if (active_mode != RGBMODE)
      return;

    blue--;
    red++;
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(red, green, blue);
    }
    FastLED.show();
  }
}

void white() {
  FastLED.setBrightness(25);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(255, 255, 255);
  }
  FastLED.show();
}

void cold() {
  FastLED.setBrightness(25);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(80, 150, 255);
  }
  FastLED.show();
}

void warm() {
  FastLED.setBrightness(25);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(255, 150, 80);
  }
  FastLED.show();
}

void pick() {
  int val = analogRead(pinPot);
  if (abs(val-previousVal)<10) { //stabilizzazione colore
    val = previousVal;
  }
  float h = map(val, 0, 1023, 370, 0);
  FastLED.setBrightness(25);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(h, 255, 255);
  }
  FastLED.show();
  previousVal = val;
}

void setMode() {
  String dir = re.turnDirection();
  if (dir == "dx") {
    mode++;
    lcd.clear();
  }
  else if (dir == "sx") {
    mode--;
    lcd.clear();
  }
  mode = mode % NUM_MODES;
  if (mode < 0)
    mode = NUM_MODES - 1;
  if (digitalRead(RASPIN) == LOW)
    active_mode = OFF;
  if (re.isButtonPressed() && digitalRead(RASPIN) == HIGH)
    active_mode = mode;

  lcd.setCursor(0, 0);
  lcd.print("Mode   ");
  lcd.print(mode);
  lcd.setCursor(7 - (modes[mode].length() / 2), 1);
  lcd.print(modes[mode]);
}
