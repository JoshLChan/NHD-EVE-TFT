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
    void helloWorld(char* text);
    void init_800X480_7_0();
    void threerats();
    void coolbear();
    void logo();

private:
    int _hsize;
    int _vsize;
    uint8_t _index = 4;
    void init_320X240();
    void init_480X272();
    void init_800X480_4_3();
    void init_800X480_5_0();
};

#endif