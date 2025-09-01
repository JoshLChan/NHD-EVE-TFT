#ifndef PROXIMITY
#define PROXIMITY

#include <Arduino.h>

class Ultrasonic
{
public:
    Ultrasonic(uint8_t trig, uint8_t echo);
    void begin();
    int detect();
private:
    uint8_t _trig;
    uint8_t _echo;

    void clearTrig();
    long pulse();
};

#endif