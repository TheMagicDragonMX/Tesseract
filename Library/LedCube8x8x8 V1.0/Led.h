#ifndef LED_H
#define LED_H
#include <Arduino.h>

typedef unsigned long ulong;

#define ALWAYS_ON 0

class Led {
public:
    // Members
    bool state;
    ulong timeOn;
    byte significance;

    // Constructor
    Led();

    // Methods
    bool isOn();
    void setTimeOn(ulong _time);
};

// Useful fuctions
byte powInByte(byte _base, byte _exponent);

#endif