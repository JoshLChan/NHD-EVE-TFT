#include <Proximity.h>

Ultrasonic::Ultrasonic(uint8_t trig, uint8_t echo)
{
    _trig = trig;
    _echo = echo;
}

void Ultrasonic::begin()
{
    pinMode(_trig, OUTPUT);
    pinMode(_echo, INPUT);
    Serial.println("begin");
}

int Ultrasonic::detect()
{
   
    clearTrig();
    int duration = pulse();
    return duration * 0.034 / 2;
}

void Ultrasonic::clearTrig()
{
    digitalWrite(_trig, LOW);
    delayMicroseconds(2);
}

long Ultrasonic::pulse()
{
    digitalWrite(_trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trig, LOW);
    return pulseIn(_echo, HIGH);
}
