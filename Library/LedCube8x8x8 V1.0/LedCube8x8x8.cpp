#include "LedCube8x8x8.h"

/**
 * @brief Construct a new LedCube8x8x8 object with default values and prepares the led array
 * @return None
 */
LedCube8x8x8::LedCube8x8x8()
{
    brightness = MAX_BRIGHTNESS;
    cubeDataChanged = true;
    initializeLeds();
}

// <---- Initializing leds ----> //
/**
 * @brief Initialize the leds array by giving each led its significance for the shift registers
 * @return None
 */
void LedCube8x8x8::initializeLeds()
{
    for(int floor = 0; floor < 8; floor++)
        for(int column = 0; column < 8; column++)
            for(int row = 0; row < 8; row++)
                leds[row][column][floor].significance = powInByte(2, row);
}

// <---- Settting basic configuration ----> //
/**
 * @brief Set the pins that will be connected to the leds shift registers
 * @param _dataPin (int) Connected to SER / DS / DATA pin
 * @param _clockPin (int) Connected to SRCLK / SH_CP / CLOCK pin
 * @param _latchPin (int) Connected to RCLK / ST_CP / LATCH pin
 * @param _resetPin (int) Connected to SRCLR' / MR' / RESET pin
 * @param _brightnessPin (int) Connected to QH / Q7 / SQH pin (opctional)
 * @return None
 */
void LedCube8x8x8::setShiftRegisterLedPins(int _dataPin, int _clockPin, int _latchPin, int _resetPin, int _brightnessPin = NOT_SET)
{
    dataPin = _dataPin;
    clockPin = _clockPin;
    latchPin = _latchPin;
    resetPin = _resetPin;
    brightnessPin = _brightnessPin;

    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(resetPin, OUTPUT);

    if(_brightnessPin != NOT_SET)
        pinMode(brightnessPin, OUTPUT);
}

/**
 * @brief Set the pins that will be connected to the floor shift register
 * @param _dataPin (int) Connected to SER / DS / DATA pin
 * @param _clockPin (int) Connected to SRCLK / SH_CP / CLOCK pin
 * @param _latchPin (int) Connected to RCLK / ST_CP / LATCH pin
 * @return None
 */
void LedCube8x8x8::setShiftRegisterFloorPins(int _dataPin, int _clockPin, int _latchPin)
{
    floorDataPin = _dataPin;
    floorClockPin = _clockPin;
    floorLatchPin = _latchPin;

    pinMode(floorDataPin, OUTPUT);
    pinMode(floorClockPin, OUTPUT);
    pinMode(floorLatchPin, OUTPUT);
}

// <---- Showing the leds ----> //
/**
 * @brief Call this fuction in loop(), this fuction will light up the cube
 * @return None
 */
void LedCube8x8x8::lightUp()
{
    for(byte floor = 0; floor < 8; floor++) {
        timeFloorMustBeOn = setFloorConfiguration(floor);

        turnOnFloor(floor);
        delayMicroseconds(timeFloorMustBeOn * 8 / 20);
        turnOffFloor();
    }

    // if(brightnessPin != NOT_SET)
    //     analogWrite(brightnessPin, 255 - brightness);
    //cubeDataChanged = false;
}

/**
 * @brief Makes all the operations and set the data of every floor on the shift registers
 * @param _floor (byte) The floor where data is going to be put on the regiters
 * @return ulong - Amount of time it was needed to make the operations
 */
ulong LedCube8x8x8::setFloorConfiguration(byte _floor)
{
    ulong configurationTime = micros();

    turnOffTimeExpiredLeds(_floor);
    clearRegisters();
    clearFloorValues();
    setNewFloorValues(_floor);
    shiftOutNewValues();

    return micros() - configurationTime;
}

/**
 * @brief Changes the state to LOW for each led which its time on has expired
 * @param _floor (int) The floor were leds are going to be analyzed
 * @return None
 */
void LedCube8x8x8::turnOffTimeExpiredLeds(byte _floor)
{
    for(byte column = 0; column < 8; column++) {
        for(byte row = 0; row < 8; row++)
            if(leds[row][column][_floor].isOn() and leds[row][column][_floor].timeOn != ALWAYS_ON and millis() > leds[row][column][_floor].timeOn)
                leds[row][column][_floor].state = LOW;
    }
}

/**
 * @brief Clears all the registers in order to prepare them for another submission
 * @return None
 */
void LedCube8x8x8::clearRegisters()
{
    // Setting the reset
    digitalWrite(latchPin, LOW);
    digitalWrite(resetPin, LOW);
    
    // Resetting the registers
    digitalWrite(latchPin, HIGH);
    digitalWrite(resetPin, HIGH);
}

/**
 * @brief Clears the floorValues[] array in order to prepare it for the next floor values
 * @return None
 */
void LedCube8x8x8::clearFloorValues()
{
    for(int index = 0; index < 8; index++)
        floorValues[index] = 0;
}

/**
 * @brief Gets the values that will be written in the registers by adding each on led significance into the array
 * @param _floor (int) The floor where each on led significance is going to be analyzed
 * @return None
 */
void LedCube8x8x8::setNewFloorValues(byte _floor)
{
    for(int column = 0; column < 8; column++) 
        for(int row = 0; row < 8; row++)
            if(leds[row][column][_floor].state == HIGH)
                floorValues[column] += leds[row][column][_floor].significance; 
}

/**
 * @brief Writtes the floor values on the registers
 * @return None
 */
void LedCube8x8x8::shiftOutNewValues()
{
    digitalWrite(latchPin, LOW);

    for(int shiftRegister = 0; shiftRegister < 8; shiftRegister++) 
        shiftOut(dataPin, clockPin, MSBFIRST, floorValues[shiftRegister]);
    
    digitalWrite(latchPin, HIGH);
}

/**
 * @brief Turns on the given floor
 * @param _floor (byte) The floor that is going to be activated
 * @return None
 */
void LedCube8x8x8::turnOnFloor(byte _floor)
{
    digitalWrite(floorLatchPin, LOW);
    shiftOut(floorDataPin, floorClockPin, MSBFIRST, powInByte(2, _floor));
    digitalWrite(floorLatchPin, HIGH);
}

/**
 * @brief Turns off the given floor
 * @param _floor (byte) The floor that is going to be desactivated
 * @return None
 */
void LedCube8x8x8::turnOffFloor()
{
    digitalWrite(floorLatchPin, LOW);
    shiftOut(floorDataPin, floorClockPin, MSBFIRST, 0x00);
    digitalWrite(floorLatchPin, HIGH);
}

// <---- Setting the leds ----> //
/**
 * @brief Set a column of the cube
 * @param _column (int) Which column we want to set
 * @param _floor (int) On which floor we want to set it
 * @param _state (bool) HIGH for turning on, LOW for turning off
 * @param _timeOn (ulong) Time in ms we want it to be on (default is ALWAYS ON)
 * @return None
 */
void LedCube8x8x8::setColumn(int _column, int _floor, bool _state, ulong _timeOn = ALWAYS_ON)
{
    for(int row = 0; row < 8; row++) {
        leds[row][_column][_floor].state = _state;
        leds[row][_column][_floor].setTimeOn(_timeOn);
    }
}

/**
 * @brief Set a row of the cube
 * @param _row (int) Which row we want to set
 * @param _floor (int) On which floor we want to set it
 * @param _state (bool) HIGH for turning on, LOW for turning off
 * @param _timeOn (ulong) Time in ms we want it to be on (default is ALWAYS ON)
 * @return None
 */
void LedCube8x8x8::setRow(int _row, int _floor, bool _state, ulong _timeOn = ALWAYS_ON)
{
    for(int column = 0; column < 8; column++) {
        leds[_row][column][_floor].state = _state;
        leds[_row][column][_floor].setTimeOn(_timeOn);
    }
}

/**
 * @brief Set a pilar of the cube (the vertical ones)
 * @param _row (int) Row coordinate of the pilar
 * @param _column (int) Column coordinate of the pilar
 * @param _state (bool) HIGH for turning on, LOW for turning off
 * @param _timeOn (ulong) Time in ms we want it to be on (default is ALWAYS ON)
 * @return None
 */
void LedCube8x8x8::setPilar(int _row, int _column, bool _state, ulong _timeOn = ALWAYS_ON)
{
    for(int floor = 0; floor < 8; floor++) {
        leds[_row][_column][floor].state = _state;
        leds[_row][_column][floor].setTimeOn(_timeOn);
    }
}

/**
 * @brief Set an entire floor of the cube
 * @param _floor (int) Which floor we want to set 
 * @param _state (bool) HIGH for turning on, LOW for turning off
 * @param _timeOn (ulong) Time in ms we want it to be on (default is ALWAYS ON)
 */
void LedCube8x8x8::setFloor(int _floor, bool _state, ulong _timeOn = ALWAYS_ON)
{
    for(int column = 0; column < 8; column++)
        for(int row = 0; row < 8; row++) {
            leds[row][column][_floor].state = _state;
            leds[row][column][_floor].setTimeOn(_timeOn);
        }
}

/**
 * @brief Set an entire wall of the cube (row side)
 * @param _row (int) Which wall we want to set 
 * @param _state (bool) HIGH for turning on, LOW for turning off
 * @param _timeOn (ulong) Time in ms we want it to be on (default is ALWAYS ON)
 */
void LedCube8x8x8::setRowWall(int _row, bool _state, ulong _timeOn = ALWAYS_ON)
{
    for(int floor = 0; floor < 8; floor++) 
        for(int column = 0; column < 8; column++) {
            leds[_row][column][floor].state = _state;
            leds[_row][column][floor].setTimeOn(_timeOn);
        }
}

/**
 * @brief Set an entire wall of the cube (column side)
 * @param _row (int) Which wall we want to set 
 * @param _state (bool) HIGH for turning on, LOW for turning off
 * @param _timeOn (ulong) Time in ms we want it to be on (default is ALWAYS ON)
 */
void LedCube8x8x8::setColumnWall(int _column, bool _state, ulong _timeOn = ALWAYS_ON)
{
    for(int floor = 0; floor < 8; floor++) 
        for(int row = 0; row < 8; row++) {
            leds[row][_column][floor].state = _state;
            leds[row][_column][floor].setTimeOn(_timeOn);
        }
}

/**
 * @brief Set every led on the cube
 * @param _state (bool) HIGH for turning on, LOW for turning off
 * @param _timeOn (ulong) Time in ms we want it to be on (default is ALWAYS ON)
 */
void LedCube8x8x8::setEverything(bool _state, ulong _timeOn = ALWAYS_ON)
{
    for(int floor = 0; floor < 8; floor++)
        for(int column = 0; column < 8; column++)
            for(int row = 0; row < 8; row++) {
                leds[row][column][floor].state = _state;
                leds[row][column][floor].setTimeOn(_timeOn);
            }
}

/**
 * @brief Sets an specific led
 * 
 * @param _row (int) On which row is the led
 * @param _column (int) On which column is the led
 * @param _floor (int) On which floor is the led
 * @param _state (bool) HIGH for turning on, LOW for turning off
 * @param _timeOn (ulong) Time in ms we want it to be on (default is ALWAYS ON)
 */
void LedCube8x8x8::setLed(int _row, int _column, int _floor, bool _state, ulong _timeOn = ALWAYS_ON)
{
    leds[_row][_column][_floor].state = _state;
    leds[_row][_column][_floor].setTimeOn(_timeOn);
}

// <---- Settting the brightness --->
/**
 * @brief Set the brightness of the cube
 * @param _brightness 0 for minimum, 255 for maximum
 * @return None
 */
void LedCube8x8x8::setBrightness(byte _brightness)
{
    brightness = _brightness;
}