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

private:
    //Manually set horizontal and vertical size of screen
    int _hsize;
    int _vsize;

    //Bootup related
    uint8_t _index = 4;
    void init_320X240();
    void init_480X272();
    void init_800X480_4_3();
    void init_800X480_5_0();
    void init_800X480_7_0();

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