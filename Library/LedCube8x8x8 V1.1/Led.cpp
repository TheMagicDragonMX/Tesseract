#include "Led.h"

/**
 * @brief Set a new <Led> which will be off
 */
Led::Led()
{
    state = OFF;
    timeOn = ALWAYS_ON;
}

bool Led::setStatus(bool _state, ulong _timeOn = ALWAYS_ON)
{
    state = _state;
    timeOn = (_timeOn != ALWAYS_ON)
    ? millis() + _timeOn
    : ALWAYS_ON;
}

/**
 * @brief Classic pow(), but with any numeric type
 * @param base
 * @param exponent If < 0, returns 1
 * @return Given type
 */
template <class T>
T pow(T base, T exponent)
{
    if (exponent <= 0)
        return 1;
    
    T result = base;
    for (byte times = 1; times < exponent; times++)
        result *= base;
    
    return result;
}