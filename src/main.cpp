#include <Arduino.h>
#include <NHD-EVE.h>

bool SD_open = false;


NHD_EVE tft(TFT_800X480_7_0);

void setup()
{
  Serial.begin(115200);
  tft.begin();

  // if (!SD.begin(SD_CONFIG))
  // {
  //   SD.initErrorHalt(&Serial);
  // }
}

void loop()
{
  // tft.helloWorld("HELLO WORLD!");

  tft.slideshow();

  // tft.logo();
  // delay(5000);
  // tft.coolbear();
  // delay(5000);
  // tft.threerats();
  // delay(5000);

  // storeImage();
}
