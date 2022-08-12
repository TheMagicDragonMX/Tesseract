#ifndef LED_H
#define LED_H
#include <Arduino.h>

typedef unsigned long ulong;

#define ALWAYS_ON 0
#define ON 1
#define OFF 0

class Led {
public:
    // Members
    bool state;
    ulong timeOn;

    // Constructor
    Led();

    // Methods
    bool setStatus(bool state, ulong timeOn = ALWAYS_ON);
};

// Useful fuctions
template <class T>
T pow(T base, T exponent);

#endif