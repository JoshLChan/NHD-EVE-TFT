#include <Arduino.h>
#include <NHD-EVE.h>
#include <Proximity.h>


#define trig 7
#define echo 6

NHD_EVE tft(TFT_800X480_7_0);
Ultrasonic prox(trig, echo);

int dist;

void setup()
{
  Serial.begin(115200);
  tft.begin();
  prox.begin();
}

void loop()
{
  // tft.helloWorld("HELLO WORLD!");

  // tft.slideshow();

  
    
  tft.proximityDisplay(dist);

  dist = prox.detect();
  

  // Serial.println("Distance: " + (String)prox.detect());

}
