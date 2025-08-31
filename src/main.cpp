#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <NHD-EVE.h>

File image;
bool SD_open = false;

void storeImage();

NHD_EVE tft(TFT_800X480_7_0);

void setup()
{
  Serial.begin(115200);
  // tft.begin();
  // GD.Clear();
}

void loop()
{
  // tft.helloWorld("HELLO WORLD!");

  // tft.logo();
  // delay(5000);
  // tft.coolbear();
  // delay(5000);
  // tft.threerats();
  // delay(5000);

  storeImage();
}

void storeImage()
{
  if (Serial.available())
  {
    if (!SD_open)
    {
      image = SD.open("image.jpg", FILE_WRITE | O_TRUNC);

      SD_open = true;
    }

    if (image)
    {
      byte buffer[255];

      Serial.readBytes(buffer, 255);

      for (int i = 0; i < 255; i++)
      {
        if (buffer[i] >= 0)
        image.write(buffer[i]);
      }
    }
    else
    {
      Serial.println("error opening image");
    }
  }
  else
  {
    if (SD_open)
    {
      SD_open = false;

      image.close();
    }

    Serial.println("ACK");
    image = SD.open("image.jpg");
    Serial.println("Image Size: " + (String)image.size());
    image.close();

    delay(1000);
  }
}