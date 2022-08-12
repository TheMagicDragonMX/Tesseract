#include "Led.h"

/**
 * @brief Construct a new Led object with default parameters
 */
Led::Led()
{
    state = false;
    timeOn = ALWAYS_ON;
    significance = 0;
}

/**
 * @brief Returns the state of the led
 * @return bool
 */
bool Led::isOn()
{
    return state;
}

/**
 * @brief Sets the time that led will stay ON
 * @param _ms Time in millis, set ALWAYS_ON for endless ON state
 */
void Led::setTimeOn(ulong _ms)
{
    if(_ms == ALWAYS_ON)
        timeOn = ALWAYS_ON;
    else
        timeOn = millis() + _ms;
}

/**
 * @brief Pows byte type numbers and returns the result
 * @param _base Base number
 * @param _exponent Times it will multiply by itslef, 0 will return 1
 * @return byte (uint_8)
 */
byte powInByte(byte _base, byte _exponent)
{
    if(_exponent == 0)
        return 1;

    byte result = _base;
    for(byte times = 1; times < _exponent; times++)
        result = result * _base;

    return result;
}