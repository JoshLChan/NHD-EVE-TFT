#include <Arduino.h>
#include <NHD-EVE.h>

#define trig A5
#define echo A4
#define motion A3

NHD_EVE tft(TFT_480X480);
// Ultrasonic prox(trig, echo);

bool b1_pressed = false;
bool b2_pressed = false;
bool b3_pressed = false;

void setup()
{
  Serial.begin(115200);
  
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(motion, INPUT);

  tft.begin();
  // prox.begin();

}

void loop()
{
  tft.doorbell(trig, echo, motion);

}
