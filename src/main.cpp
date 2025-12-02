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

  // if (mode == 0)
  //   tft.mainMenu();

  // // Mode selection
  // if (!digitalRead(A0) && !b1_pressed && mode == 0)
  // {
  //   b1_pressed = true;
  //   tft.reset();
  //   mode = 1;
  // }
  // else if (!digitalRead(A1) && !b2_pressed && mode == 0)
  // {
  //   b2_pressed = true;
  //   tft.reset();
  //   mode = 2;
  // }
  // else if (!digitalRead(A2) && !b3_pressed && mode == 0)
  // {
  //   b3_pressed = true;
  //   tft.reset();
  //   mode = 3;
  // }

  // // Reset button debounce
  // if (digitalRead(A0))
  //   b1_pressed = false;
  // if (digitalRead(A1))
  //   b2_pressed = false;
  // if (digitalRead(A2))
  //   b3_pressed = false;

  // //Back to main menu
  // if ((mode != 0 && !digitalRead(A0) && !b1_pressed) ||
  //     (mode != 0 && !digitalRead(A1) && !b2_pressed) ||
  //     (mode != 0 && !digitalRead(A2) && !b3_pressed))
  // {
  //   b1_pressed = true;
  //   b2_pressed = true;
  //   b3_pressed = true;
  //   mode = 0;
  // }

  // switch (mode)
  // {
  // case 0:
  //   tft.mainMenu();
  //   break;
  // case 1:
  //   tft.helloWorld("HELLO WORLD!");
  //   break;
  // case 2:
  //   tft.proximityDisplay(dist);
  //   dist = prox.detect();
  //   break;
  // case 3:
  //   tft.slideshow();
  //   break;

  // default:
  //   break;
  // }
}
