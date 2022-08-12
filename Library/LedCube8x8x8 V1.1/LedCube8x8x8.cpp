#include "LedCube8x8x8.h"

/**
 * @brief Set a new Led Cube with all leds off
 */
LedCube8x8x8::LedCube8x8x8()
{
    ledCube.fill(Floor(Row(Led())));
}

// <---- Setting basic configuration ----> //
/**
 * @brief Set pins connected to cube shfit registers
 * 
 * @param _dataPin Connected to SER / DS / DATA pin
 * @param _clockPin Connected to SRCLK / SH_CP / CLOCK pin
 * @param _latchPin Connected to RCLK / ST_CP / LATCH pin
 * @param _resetPin Connected to SRCLR' / MR' / RESET pin
 * @param _outputEnablePin Connected to OE pin (MUST BE CONNECTED TO A PWM PIN)
 */
void LedCube8x8x8::setCubePins(byte _dataPin, byte _clockPin, byte _latchPin, byte _resetPin, byte _outputEnablePin)
{
    dataPin = _dataPin;
    clockPin = _clockPin;
    latchPin = _latchPin;
    resetPin = _resetPin;
    outputEnablePin = _outputEnablePin;

    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(resetPin, OUTPUT);

    digitalWrite(clockPin, LOW);
    digitalWrite(resetPin, HIGH);

    analogWrite(outputEnablePin, 255 - MAX_BRIGHTNESS);
}

/**
 * @brief Set pins connected to floor shift register
 * 
 * @param _dataPin Connected to SER / DS / DATA pin
 * @param _clockPin Connected to SRCLK / SH_CP / CLOCK pin
 * @param _latchPin Connected to RCLK / ST_CP / LATCH pin
 */
void LedCube8x8x8::setFloorPins(byte _dataPin, byte _clockPin, byte _latchPin)
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
 */
void LedCube8x8x8::lightUp()
{
    ulong timeFloorMustBeOn = 0;

    for (byte floor = 0; floor < 8; floor++) {
        timeFloorMustBeOn = setFloorConfiguration(ledCube[floor]);

        turnOnFloor(floor);
        delayMicroseconds((timeFloorMustBeOn * 10) / 20);
        turnOffFloor();
    }
}

/**
 * @brief Set floor info on shift registers
 * 
 * @param floor The floor where data is going to be shifted out
 * 
 * @return ulong - Amount of time it was needed to make the operation
 */
ulong LedCube8x8x8::setFloorConfiguration(Floor& floor)
{
    ulong configurationTime = micros();

    turnOffTimeExpiredLeds(floor);
    shiftOutFloorData(floor);

    return micros() - configurationTime;
}

/**
 * @brief Turns of every led that has expired time
 * 
 * @param floor Floor were leds are going to be analyzed
 * 
 * @return None
 */
void LedCube8x8x8::turnOffTimeExpiredLeds(Floor& floor)
{
    for (auto& row : floor)
        for (auto& led : row)
            if (ledIsTimeExpired(led))
                led.state = OFF;
}

/**
 * @brief Returns true if led's time on has expired
 * 
 * @param led
 */
bool LedCube8x8x8::ledIsTimeExpired(Led& led)
{
    return (led.timeOn != ALWAYS_ON) && (millis() > led.timeOn);
}

/**
 * @brief Upload all floor data to registers
 * 
 * @param floor 
 */
void LedCube8x8x8::shiftOutFloorData(Floor& floor)
{
    digitalWrite(latchPin, LOW);

    for (auto& row : floor)
        for (auto& led : row)
            shiftOutLedState(led.state);

    digitalWrite(latchPin, HIGH);
}

/**
 * @brief Push a led state on the registers
 * 
 * @param state Led's actual state
 */
void LedCube8x8x8::shiftOutLedState(bool state)
{
    digitalWrite(dataPin, state);

    digitalWrite(clockPin, HIGH);
	digitalWrite(clockPin, LOW);
}

/**
 * @brief Turn on given floor
 * 
 * @param floor The floor that is going to be activated
 */
void LedCube8x8x8::turnOnFloor(byte floor)
{
    digitalWrite(floorLatchPin, LOW);
    shiftOut(floorDataPin, floorClockPin, MSBFIRST, floorID[floor]);
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
 * @brief Set a column of the cube (Y Axis)
 * 
 * @param x On which X coodinate
 * @param z On which Z coordinate
 * @param state ON for turning on, OFF for turning off
 * @param timeOn Time in ms we want it to be on (default is ALWAYS ON)
 */
void LedCube8x8x8::setColumn(byte x, byte z, bool state, ulong timeOn = ALWAYS_ON)
{
    for (byte y = 0; y <= 7; y++) 
        ledCube[z][x][y].setStatus(state, timeOn);
}

/**
 * @brief Set a row of the cube (X Axis)
 * 
 * @param y On which Y coordinate
 * @param z On which Z coordinate
 * @param state ON for turning on, OFF for turning off
 * @param timeOn Time in ms we want it to be on (default is ALWAYS ON)
 */
void LedCube8x8x8::setRow(byte y, byte z, bool state, ulong timeOn = ALWAYS_ON)
{
    for (byte x = 0; x <= 7; x++) 
        ledCube[z][x][y].setStatus(state, timeOn);
}

/**
 * @brief Set a pilar of the cube
 * 
 * @param x On which X coodinate
 * @param y On which Y coordinate
 * @param state ON for turning on, OFF for turning off
 * @param timeOn Time in ms we want it to be on (default is ALWAYS ON)
 */
void LedCube8x8x8::setPilar(byte x, byte y, bool state, ulong timeOn = ALWAYS_ON)
{
    for (auto& floor : ledCube)
        floor[x][y].setStatus(state, timeOn);
}

/**
 * @brief Set an entire floor of the cube

 * @param z On which Z coordinate
 * @param state ON for turning on, OFF for turning off
 * @param timeOn Time in ms we want it to be on (default is ALWAYS ON)
 */
void LedCube8x8x8::setFloor(byte z, bool state, ulong timeOn = ALWAYS_ON)
{
    for (auto& row : ledCube[z])
        for (auto& led : row)
            led.setStatus(state, timeOn);
}

/**
 * @brief Set an entire wall of the cube (Y axis)

 * @param x On which X coordinate
 * @param state ON for turning on, OFF for turning off
 * @param timeOn Time in ms we want it to be on (default is ALWAYS ON)
 */
void LedCube8x8x8::setColumnWall(byte x, bool state, ulong timeOn = ALWAYS_ON)
{   
    for (auto& floor : ledCube)
        for (byte y = 0; y <= 7; y++) 
            floor[x][y].setStatus(state, timeOn);
}

/**
 * @brief Set an entire wall of the cube (X axis)

 * @param y On which Y coordinate
 * @param state ON for turning on, OFF for turning off
 * @param timeOn Time in ms we want it to be on (default is ALWAYS ON)
 */
void LedCube8x8x8::setRowWall(byte y, bool state, ulong timeOn = ALWAYS_ON)
{
    for (auto& floor : ledCube)
        for (byte x = 0; x <= 7; x++) 
            floor[x][y].setStatus(state, timeOn);
}

/**
 * @brief Set a column of the cube with a specific design (Y Axis)
 * 
 * @param design Use 0bxxxxxxxx to make a design
 * @param x On which X coodinate
 * @param z On which Z coordinate
 * @param timeOn Time in ms we want it to be on (default is ALWAYS ON)
 */
void LedCube8x8x8::setColumnWithDesign(byte design, byte x, byte z, ulong timeOn = ALWAYS_ON)
{
    for (byte y = 0; y <= 7; y++) {
        ledCube[z][x][y].setStatus((design & 128) != 0, timeOn);
        design <<= 1;
    }
}

/**
 * @brief Set a row of the cube with a specific design (X Axis)
 * 
 * @param design Use 0bxxxxxxxx to make a design
 * @param y On which Y coodinate
 * @param z On which Z coordinate
 * @param timeOn Time in ms we want it to be on (default is ALWAYS ON)
 */
void LedCube8x8x8::setRowWithDesign(byte design, byte y, byte z, ulong timeOn = ALWAYS_ON)
{
    for (byte x = 0; x <= 7; x++) {
        ledCube[z][x][y].setStatus((design & 128) != 0, timeOn);
        design <<= 1;
    }
}

/**
 * @brief Set a pilar of the cube with a specific design
 * 
 * @param design Use 0bxxxxxxxx to make a design
 * @param x On which X coodinate
 * @param y On which Y coordinate
 * @param timeOn Time in ms we want it to be on (default is ALWAYS ON)
 */
void LedCube8x8x8::setPilarWithDesign(byte design, byte x, byte y, ulong timeOn = ALWAYS_ON)
{
    for (int z = 7; z >= 0; z--) {
        ledCube[z][x][y].setStatus((design & 128) != 0, timeOn);
        design <<= 1;
    }
}

/**
 * @brief Set an entire floor of the cube with a specific design

 * @param design Use an array of 0bxxxxxxxx to make a design
 * @param z On which Z coordinate
 * @param timeOn Time in ms we want it to be on (default is ALWAYS ON)
 */
void LedCube8x8x8::setFloorWithDesign(byte design[8], byte z, ulong timeOn = ALWAYS_ON)
{
    for (int y = 7; y >= 0; y--)
        setRowWithDesign(design[y], y, z, timeOn);
}

/**
 * @brief Set an entire wall of the cube with a specific design (Y Axis)

 * @param design Use an array of 0bxxxxxxxx to make a design
 * @param x On which X coordinate
 * @param timeOn Time in ms we want it to be on (default is ALWAYS ON)
 */
void LedCube8x8x8::setColumnWallWithDesign(byte design[8], byte x, ulong timeOn = ALWAYS_ON)
{
    for (int z = 7; z >= 0; z--)
        setColumnWithDesign(design[z], x, z, timeOn);
}

/**
 * @brief Set an entire wall of the cube with a specific design (X Axis)

 * @param design Use an array of 0bxxxxxxxx to make a design
 * @param y On which Y coordinate
 * @param timeOn Time in ms we want it to be on (default is ALWAYS ON)
 */
void LedCube8x8x8::setRowWallWithDesign(byte design[8], byte y, ulong timeOn = ALWAYS_ON)
{
    for (int z = 7; z >= 0; z--)
        setRowWithDesign(design[z], y, z, timeOn);
}

/**
 * @brief Set every led on the cube
 * 
 * @param state ON for turning on, OFF for turning off
 * @param timeOn Time in ms we want it to be on (default is ALWAYS ON)
 */
void LedCube8x8x8::setEverything(bool state, ulong timeOn = ALWAYS_ON)
{
    for (auto& floor : ledCube)
        for (auto& row : floor)
            for (auto& led : row)
                led.setStatus(state, timeOn);
}

/**
 * @brief Sets an specific led
 * 
 * @param x On which X coordinate
 * @param y On which Y coordinate
 * @param z On which Z coordinate
 * @param state ON for turning on, OFF for turning off
 * @param timeOn Time in ms we want it to be on (default is ALWAYS ON)
 */
void LedCube8x8x8::setLed(byte x, byte y, byte z, bool state, ulong timeOn = ALWAYS_ON)
{
    ledCube[z][x][y].setStatus(state, timeOn);
}

// <---- Settting the brightness --->
/**
 * @brief Set the brightness of the cube
 * 
 * @param _brightness 0 for minimum, 255 for maximum
 */
void LedCube8x8x8::setBrightness(byte brightness)
{
    analogWrite(outputEnablePin, 255 - brightness);
}

/**
 * @brief Turns off the cube
 */
void LedCube8x8x8::turnOff()
{
    analogWrite(outputEnablePin, 255 - MIN_BRIGHTNESS);
}