/*

This library was made for the NHD-EVE-TFT displays to showcase basic
Gameduino 2 functinality. Demos include:

- Hello World
- Proximity Detect
- Slideshow

Author : Joshua L. Chan

Revision History: 
0.1 - date 2025.08.31 - Initial Version
0.2 - date 2025.09.01 - fixed bugs

*/


#ifndef NHDEVE
#define NHDEVE

#include <SPI.h>
#include <GD2.h>

#define TFT_320X240 0
#define TFT_480X272 1
#define TFT_800X480_4_3 2
#define TFT_800X480_5_0 3
#define TFT_800X480_7_0 4

class NHD_EVE
{
public:
    NHD_EVE(uint8_t index);
    void begin();
    void helloWorld(char *text);
    void slideshow();
    void proximityDisplay(int distance);
    void reset();
    uint8_t mainMenu();

private:
    //Manually set horizontal and vertical size of screen
    int _hsize;
    int _vsize;

    //Buttons
    uint32_t _buttonclr = 0x1e6e01;

    //Bootup related
    uint8_t _index = 4;
    void init_320X240();
    void init_480X272();
    void init_800X480_4_3();
    void init_800X480_5_0();
    void init_800X480_7_0();

    // Main menu
    bool _loadmainmenu = false;

    //Proximity related
    uint32_t _proximitybg = 0x424242;
    int _distance = 0;

    //Slideshow related
    bool _loadSlideShow = false;
    int _slideshowx = 0;
    uint8_t _slideshowindex = 1;
    void ChangeSlide(uint8_t from, uint8_t to, uint32_t colorFrom, uint32_t colorTo);

};

#endif