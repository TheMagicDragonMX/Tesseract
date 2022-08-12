#ifndef LED_CUBE_8X8X8_H
#define LED_CUBE_8X8X8_H
#include "Led.h"

#define MAX_BRIGHTNESS 255
#define NOT_SET -1
#define NO_DELAY 0

class LedCube8x8x8
{
public:
    // <-- Members --> 
    Led leds[8][8][8];
    byte floorValues[8];
    bool cubeDataChanged;

    byte brightness;
    ulong timeFloorMustBeOn;

    int dataPin, clockPin, latchPin, resetPin, brightnessPin;
    int floorDataPin, floorClockPin, floorLatchPin;

    // <-- Private methods -->
    // Initializing leds
    void initializeLeds();
    
    // Showing the leds
    ulong setFloorConfiguration(byte _floor);
    void turnOffTimeExpiredLeds(byte _floor);
    void clearRegisters();
    void clearFloorValues();
    void setNewFloorValues(byte _floor);
    void shiftOutNewValues();

    // Turn on the floor
    void turnOnFloor(byte _floor);
    void turnOffFloor();
    
public:
    LedCube8x8x8();

    // <-- Methods -->
    // Setting basic configuration
    void setShiftRegisterLedPins(int _dataPin, int _clockPin, int _latchPin, int _resetPin, int _brightnessPin = NOT_SET);
    void setShiftRegisterFloorPins(int _dataPin, int _clockPin, int _latchPin);

    // Showing the leds 
    void lightUp();

    // Setting the leds
    void setColumn(int _column, int _floor, bool _state, ulong _timeOn = ALWAYS_ON);
    void setRow(int _row, int _floor, bool _state, ulong _timeOn = ALWAYS_ON);
    void setPilar(int _row, int _column, bool _state, ulong _timeOn = ALWAYS_ON);
    void setFloor(int _floor, bool _state, ulong _timeOn = ALWAYS_ON);
    void setRowWall(int _row, bool _state, ulong _timeOn = ALWAYS_ON);
    void setColumnWall(int _column, bool _state, ulong _timeOn = ALWAYS_ON);
    void setEverything(bool _state, ulong _timeOn = ALWAYS_ON);
    void setLed(int _row, int _column, int _floor, bool _state, ulong _timeOn = ALWAYS_ON);

    // Setting the brightness
    void setBrightness(byte _brightness);
};
#endif
