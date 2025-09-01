#include <Arduino.h>
#include <NHD-EVE.h>
#include <Proximity.h>

#define trig 7
#define echo 6

NHD_EVE tft(TFT_800X480_7_0);
Ultrasonic prox(trig, echo);

int dist;

uint8_t mode = 0;
bool b1_pressed = false;
bool b2_pressed = false;
bool b3_pressed = false;

void setup()
{
  Serial.begin(115200);
  tft.begin();
  prox.begin();

  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
}

void loop()
{

  // tft.mainMenu();
  if (mode == 0)
    tft.mainMenu();

  if (!digitalRead(A0) && !b1_pressed && mode == 0)
  {
    b1_pressed = true;
    tft.reset();
    mode = 1;
  }
  else if (!digitalRead(A1) && !b2_pressed && mode == 0)
  {
    b2_pressed = true;
    tft.reset();
    mode = 2;
  }
  else if (!digitalRead(A2) && !b3_pressed && mode == 0)
  {
    b3_pressed = true;
    tft.reset();
    mode = 3;
  }

  if (digitalRead(A0))
    b1_pressed = false;
  if (digitalRead(A1))
    b2_pressed = false;
  if (digitalRead(A2))
    b3_pressed = false;

  if ((mode != 0 && !digitalRead(A0) && !b1_pressed) ||
      (mode != 0 && !digitalRead(A1) && !b2_pressed) ||
      (mode != 0 && !digitalRead(A2) && !b3_pressed))
  {
    b1_pressed = true;
    b2_pressed = true;
    b3_pressed = true;
    mode = 0;
  }

  switch (mode)
  {
  case 0:
    tft.mainMenu();
    break;
  case 1:
    tft.helloWorld("HELLO WORLD!");
    break;
  case 2:
    tft.proximityDisplay(dist);
    dist = prox.detect();
    break;
  case 3:
    tft.slideshow();
    break;

  default:
    break;
  }

  // Serial.println("B1: " + (String)digitalRead(A0) + "B2: " + (String)digitalRead(A1) + "B3: " + (String)digitalRead(A2) + " | mode: " + (String)mode);
}
