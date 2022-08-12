#ifndef LED_CUBE_8X8X8_H
#define LED_CUBE_8X8X8_H

#include "Led.h"
#include <Array.h>

typedef Array<Led, 8> Row;
typedef Array<Row, 8> Floor;
typedef Array<Floor, 8> Cube;

#define MAX_BRIGHTNESS 255
#define MIN_BRIGHTNESS 0
#define NOT_SET 0
#define NO_DELAY 0

class LedCube8x8x8
{
public:
    Cube ledCube;

    const byte floorID[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };

    // LED Cube pins
    byte dataPin, clockPin, latchPin, resetPin, outputEnablePin;
    byte floorDataPin, floorClockPin, floorLatchPin;
    
    // Showing the leds
    ulong setFloorConfiguration(Floor& floor);
        void turnOffTimeExpiredLeds(Floor& floor);
            bool ledIsTimeExpired(Led& led);
        
    void shiftOutFloorData(Floor& floor);
    void shiftOutLedState(bool state);

    // Turn on the floor
    void turnOnFloor(byte floor);
    void turnOffFloor();
    
public:
    LedCube8x8x8();

    // Pin configuration methods
    /**
     * @brief Set pins connected to cube shfit registers
     * 
     * @param _dataPin Connected to SER / DS / DATA pin
     * @param _clockPin Connected to SRCLK / SH_CP / CLOCK pin
     * @param _latchPin Connected to RCLK / ST_CP / LATCH pin
     * @param _resetPin Connected to SRCLR' / MR' / RESET pin
     */
    void setCubePins (byte _dataPin, byte _clockPin, byte _latchPin, byte _resetPin, byte _outputEnablePin);
    
    /**
     * @brief Set pins connected to floor shift register
     * 
     * @param _dataPin Connected to SER / DS / DATA pin
     * @param _clockPin Connected to SRCLK / SH_CP / CLOCK pin
     * @param _latchPin Connected to RCLK / ST_CP / LATCH pin
     */
    void setFloorPins (byte _dataPin, byte _clockPin, byte _latchPin);

    // Setting leds
    /**
     * @brief Set a column of the cube (Y Axis)
     * 
     * @param x On which X coodinate
     * @param z On which Z coordinate
     * @param state ON for turning on, OFF for turning off
     * @param timeOn Time in ms we want it to be on (default is ALWAYS ON)
     */
    void setColumn (byte x, byte z, bool state, ulong timeOn = ALWAYS_ON);

    /**
     * @brief Set a row of the cube (X Axis)
     * 
     * @param y On which Y coordinate
     * @param z On which Z coordinate
     * @param state ON for turning on, OFF for turning off
     * @param timeOn Time in ms we want it to be on (default is ALWAYS ON)
     */
    void setRow (byte y, byte z, bool state, ulong timeOn = ALWAYS_ON);
    
    /**
     * @brief Set a pilar of the cube
     * 
     * @param x On which X coodinate
     * @param y On which Y coordinate
     * @param state ON for turning on, OFF for turning off
     * @param timeOn Time in ms we want it to be on (default is ALWAYS ON)
     */
    void setPilar (byte x, byte y, bool state, ulong timeOn = ALWAYS_ON);
    
    /**
     * @brief Set an entire floor of the cube

    * @param z On which Z coordinate
    * @param state ON for turning on, OFF for turning off
    * @param timeOn Time in ms we want it to be on (default is ALWAYS ON)
    */
    void setFloor (byte z, bool state, ulong timeOn = ALWAYS_ON);
    
    /**
     * @brief Set an entire wall of the cube (X axis)

    * @param y On which Y coordinate
    * @param state ON for turning on, OFF for turning off
    * @param timeOn Time in ms we want it to be on (default is ALWAYS ON)
    */
    void setRowWall (byte y, bool state, ulong timeOn = ALWAYS_ON);
    
    /**
     * @brief Set an entire wall of the cube (Y axis)

    * @param x On which X coordinate
    * @param state ON for turning on, OFF for turning off
    * @param timeOn Time in ms we want it to be on (default is ALWAYS ON)
    */
    void setColumnWall (byte x, bool state, ulong timeOn = ALWAYS_ON);
    

    
    /**
     * @brief Set a column of the cube with a specific design (Y Axis)
     * 
     * @param design Use 0bxxxxxxxx to make a design
     * @param x On which X coodinate
     * @param z On which Z coordinate
     * @param timeOn Time in ms we want it to be on (default is ALWAYS ON)
     */
    void setColumnWithDesign (byte design, byte x, byte z, ulong timeOn = ALWAYS_ON);
    
    /**
     * @brief Set a row of the cube with a specific design (X Axis)
     * 
     * @param design Use 0bxxxxxxxx to make a design
     * @param y On which Y coodinate
     * @param z On which Z coordinate
     * @param timeOn Time in ms we want it to be on (default is ALWAYS ON)
     */
    void setRowWithDesign (byte design, byte y, byte z, ulong timeOn = ALWAYS_ON);
    
    /**
     * @brief Set a pilar of the cube with a specific design
     * 
     * @param design Use 0bxxxxxxxx to make a design
     * @param x On which X coodinate
     * @param y On which Y coordinate
     * @param timeOn Time in ms we want it to be on (default is ALWAYS ON)
     */
    void setPilarWithDesign (byte design, byte x, byte y, ulong timeOn = ALWAYS_ON);
    
    /**
     * @brief Set an entire floor of the cube with a specific design

    * @param design Use an array of 0bxxxxxxxx to make a design
    * @param z On which Z coordinate
    * @param timeOn Time in ms we want it to be on (default is ALWAYS ON)
    */
    void setFloorWithDesign (byte design[8], byte z, ulong timeOn = ALWAYS_ON);
    
    /**
     * @brief Set an entire wall of the cube with a specific design (Y Axis)

    * @param design Use an array of 0bxxxxxxxx to make a design
    * @param x On which X coordinate
    * @param timeOn Time in ms we want it to be on (default is ALWAYS ON)
    */
    void setColumnWallWithDesign (byte design[8], byte x, ulong timeOn = ALWAYS_ON);
    
    /**
     * @brief Set an entire wall of the cube with a specific design (X Axis)

    * @param design Use an array of 0bxxxxxxxx to make a design
    * @param y On which Y coordinate
    * @param timeOn Time in ms we want it to be on (default is ALWAYS ON)
    */
    void setRowWallWithDesign (byte design[8], byte y, ulong timeOn = ALWAYS_ON);

    /**
     * @brief Set every led on the cube
     * 
     * @param state ON for turning on, OFF for turning off
     * @param timeOn Time in ms we want it to be on (default is ALWAYS ON)
     */
    void setEverything (bool state, ulong timeOn = ALWAYS_ON);
    
    /**
     * @brief Sets an specific led
     * 
     * @param x On which X coordinate
     * @param y On which Y coordinate
     * @param z On which Z coordinate
     * @param state ON for turning on, OFF for turning off
     * @param timeOn Time in ms we want it to be on (default is ALWAYS ON)
     */
    void setLed (byte x, byte y, byte z, bool state, ulong timeOn = ALWAYS_ON);

    // Setting the brightness
    /**
     * @brief Set the brightness of the cube
     * 
     * @param _brightness 0 for minimum, 255 for maximum
     */
    void setBrightness (byte brightness);

    /**
     * @brief Turns off the cube
     */
    void turnOff ();

    /**
     * @brief Call this fuction in loop(), this fuction will light up the cube
     */
    void lightUp ();
};
#endif
