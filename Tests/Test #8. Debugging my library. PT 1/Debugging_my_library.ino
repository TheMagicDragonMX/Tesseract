// #pragma region Led header
// typedef unsigned long ulong;

// #define ALWAYS_ON 0

// class Led {
// public:
//     // Members
//     bool state;
//     ulong timeOn;
//     byte significance;

//     // Constructor
//     Led();

//     // Methods
//     bool isOn();
//     void setTimeOn(ulong _time);
// };

// byte powInByte(byte _base, byte _exponent);

// #pragma endregion

// #pragma region Led cpp

// /**
//  * @brief Construct a new Led object with default parameters
//  */
// Led::Led()
// {
//     state = false;
//     timeOn = ALWAYS_ON;
//     significance = 0;
// }

// /**
//  * @brief Returns the state of the led
//  * @return bool
//  */
// bool Led::isOn()
// {
//     return state;
// }

// /**
//  * @brief Sets the time that led will stay ON
//  * @param _ms Time in millis, set ALWAYS_ON for endless ON state
//  */
// void Led::setTimeOn(ulong _ms)
// {
//     if(_ms == ALWAYS_ON)
//         timeOn = ALWAYS_ON;
//     else
//         timeOn = millis() + _ms;
// }

// /**
//  * @brief Pows byte type numbers and returns the result
//  * @param _base Base number
//  * @param _exponent Times it will multiply by itslef, 0 will return 1
//  * @return byte (uint_8)
//  */
// byte powInByte(byte _base, byte _exponent)
// {
//     if(_exponent == 0)
//         return 1;

//     byte result = _base;
//     for(byte times = 1; times < _exponent; times++)
//         result = result * _base;

//     return result;
// }

// #pragma endregion

// #pragma region LedCube header
// #define MAX_BRIGHTNESS 255
// #define NOT_SET -1
// #define NO_DELAY 0

// class LedCube8x8x8
// {
// private:
//     // <-- Members --> 
//     Led leds[8][8][8];
//     byte floorValues[8];
//     bool cubeDataChanged;

//     byte brightness;
//     ulong timeFloorMustBeOn;

//     int dataPin, clockPin, latchPin, resetPin, brightnessPin;
//     int floorDataPin, floorClockPin, floorLatchPin;

//     // <-- Private methods -->
//     // Initializing leds
//     void initializeLeds();
    
//     // Showing the leds
//     ulong setFloorConfiguration(byte _floor);
//         void turnOffTimeExpiredLeds(byte _floor);
//         void clearRegisters();
//         void clearFloorValues();
//         void setNewFloorValues(byte _floor);
//         void shiftOutNewValues();

//     // Turn on the floor
//     void turnOnFloor(byte _floor);
//     void turnOffFloor();
    
// public:
//     LedCube8x8x8();

//     // <-- Methods -->
//     // Setting basic configuration
//     void setShiftRegisterLedPins(int _dataPin, int _clockPin, int _latchPin, int _resetPin, int _brightnessPin = NOT_SET);
//     void setShiftRegisterFloorPins(int _dataPin, int _clockPin, int _latchPin);

//     // Showing the leds 
//     void lightUp();

//     // Setting the leds
//     void setColumn(int _column, int _floor, bool _state, ulong _timeOn = ALWAYS_ON);
//     void setRow(int _row, int _floor, bool _state, ulong _timeOn = ALWAYS_ON);
//     void setPilar(int _row, int _column, bool _state, ulong _timeOn = ALWAYS_ON);
//     void setFloor(int _floor, bool _state, ulong _timeOn = ALWAYS_ON);
//     void setRowWall(int _row, bool _state, ulong _timeOn = ALWAYS_ON);
//     void setColumnWall(int _column, bool _state, ulong _timeOn = ALWAYS_ON);
//     void setEverything(bool _state, ulong _timeOn = ALWAYS_ON);
//     void setLed(int _row, int _column, int _floor, bool _state, ulong _timeOn = ALWAYS_ON);

//     // Setting the brightness
//     void setBrightness(byte _brightness);
// };

// #pragma endregion

// #pragma region LedCube cpp

// /**
//  * @brief Construct a new LedCube8x8x8 object with default values and prepares the led array
//  * @return None
//  */
// LedCube8x8x8::LedCube8x8x8()
// {
//     brightness = MAX_BRIGHTNESS;
//     cubeDataChanged = true;
//     initializeLeds();
// }

// // <---- Initializing leds ----> //
// /**
//  * @brief Initialize the leds array by giving each led its significance for the shift registers
//  * @return None
//  */
// void LedCube8x8x8::initializeLeds()
// {
//     for(int floor = 0; floor < 8; floor++)
//         for(int column = 0; column < 8; column++)
//             for(int row = 0; row < 8; row++)
//                 leds[row][column][floor].significance = powInByte(2, row);
// }

// // <---- Settting basic configuration ----> //
// /**
//  * @brief Set the pins that will be connected to the leds shift registers
//  * @param _dataPin (int) Connected to SER / DS / DATA pin
//  * @param _clockPin (int) Connected to SRCLK / SH_CP / CLOCK pin
//  * @param _latchPin (int) Connected to RCLK / ST_CP / LATCH pin
//  * @param _resetPin (int) Connected to SRCLR' / MR' / RESET pin
//  * @param _brightnessPin (int) Connected to QH / Q7 / SQH pin (opctional)
//  * @return None
//  */
// void LedCube8x8x8::setShiftRegisterLedPins(int _dataPin, int _clockPin, int _latchPin, int _resetPin, int _brightnessPin = NOT_SET)
// {
//     dataPin = _dataPin;
//     clockPin = _clockPin;
//     latchPin = _latchPin;
//     resetPin = _resetPin;
//     brightnessPin = _brightnessPin;

//     pinMode(dataPin, OUTPUT);
//     pinMode(clockPin, OUTPUT);
//     pinMode(latchPin, OUTPUT);
//     pinMode(resetPin, OUTPUT);

//     if(_brightnessPin != NOT_SET)
//         pinMode(brightnessPin, OUTPUT);
// }

// /**
//  * @brief Set the pins that will be connected to the floor shift register
//  * @param _dataPin (int) Connected to SER / DS / DATA pin
//  * @param _clockPin (int) Connected to SRCLK / SH_CP / CLOCK pin
//  * @param _latchPin (int) Connected to RCLK / ST_CP / LATCH pin
//  * @return None
//  */
// void LedCube8x8x8::setShiftRegisterFloorPins(int _dataPin, int _clockPin, int _latchPin)
// {
//     floorDataPin = _dataPin;
//     floorClockPin = _clockPin;
//     floorLatchPin = _latchPin;

//     pinMode(floorDataPin, OUTPUT);
//     pinMode(floorClockPin, OUTPUT);
//     pinMode(floorLatchPin, OUTPUT);
// }

// // <---- Showing the leds ----> //
// /**
//  * @brief Call this fuction in loop(), this fuction will light up the cube
//  * @return None
//  */
// void LedCube8x8x8::lightUp()
// {
//     for(byte floor = 0; floor < 8; floor++) {
//         timeFloorMustBeOn = setFloorConfiguration(floor);

//         turnOnFloor(floor);
//         delayMicroseconds(timeFloorMustBeOn * 8 / 20);
//         turnOffFloor();
//     }

//     // if(brightnessPin != NOT_SET)
//     //     analogWrite(brightnessPin, 255 - brightness);
//     //cubeDataChanged = false;
// }

// /**
//  * @brief Makes all the operations and set the data of every floor on the shift registers
//  * @param _floor (byte) The floor where data is going to be put on the regiters
//  * @return ulong - Amount of time it was needed to make the operations
//  */
// ulong LedCube8x8x8::setFloorConfiguration(byte _floor)
// {
//     ulong configurationTime = micros();

//     turnOffTimeExpiredLeds(_floor);
//     clearRegisters();
//     clearFloorValues();
//     setNewFloorValues(_floor);
//     shiftOutNewValues();

//     return micros() - configurationTime;
// }

// /**
//  * @brief Changes the state to LOW for each led which its time on has expired
//  * @param _floor (int) The floor were leds are going to be analyzed
//  * @return None
//  */
// void LedCube8x8x8::turnOffTimeExpiredLeds(byte _floor)
// {
//     for(byte column = 0; column < 8; column++) {
//         for(byte row = 0; row < 8; row++)
//             if(millis() > leds[row][column][_floor].timeOn and leds[row][column][_floor].timeOn != ALWAYS_ON and leds[row][column][_floor].isOn())
//                 leds[row][column][_floor].state = LOW;
//     }
// }

// /**
//  * @brief Clears all the registers in order to prepare them for another submission
//  * @return None
//  */
// void LedCube8x8x8::clearRegisters()
// {
//     // Setting the reset
//     digitalWrite(latchPin, LOW);
//     digitalWrite(resetPin, LOW);
    
//     // Resetting the registers
//     digitalWrite(latchPin, HIGH);
//     digitalWrite(resetPin, HIGH);
// }

// /**
//  * @brief Clears the floorValues[] array in order to prepare it for the next floor values
//  * @return None
//  */
// void LedCube8x8x8::clearFloorValues()
// {
//     for(int index = 0; index < 8; index++)
//         floorValues[index] = 0;
// }

// /**
//  * @brief Gets the values that will be written in the registers by adding each on led significance into the array
//  * @param _floor (int) The floor where each on led significance is going to be analyzed
//  * @return None
//  */
// void LedCube8x8x8::setNewFloorValues(byte _floor)
// {
//     for(int column = 0; column < 8; column++) 
//         for(int row = 0; row < 8; row++)
//             if(leds[row][column][_floor].state == HIGH)
//                 floorValues[column] += leds[row][column][_floor].significance; 
// }

// /**
//  * @brief Writtes the floor values on the registers
//  * @return None
//  */
// void LedCube8x8x8::shiftOutNewValues()
// {
//     digitalWrite(latchPin, LOW);

//     for(int shiftRegister = 0; shiftRegister < 8; shiftRegister++) 
//         shiftOut(dataPin, clockPin, MSBFIRST, floorValues[shiftRegister]);
    
//     digitalWrite(latchPin, HIGH);
// }

// /**
//  * @brief Turns on the given floor
//  * @param _floor (byte) The floor that is going to be activated
//  * @return None
//  */
// void LedCube8x8x8::turnOnFloor(byte _floor)
// {
//     digitalWrite(floorLatchPin, LOW);
//     shiftOut(floorDataPin, floorClockPin, MSBFIRST, powInByte(2, _floor));
//     digitalWrite(floorLatchPin, HIGH);
// }

// /**
//  * @brief Turns off the given floor
//  * @param _floor (byte) The floor that is going to be desactivated
//  * @return None
//  */
// void LedCube8x8x8::turnOffFloor()
// {
//     digitalWrite(floorLatchPin, LOW);
//     shiftOut(floorDataPin, floorClockPin, MSBFIRST, 0x00);
//     digitalWrite(floorLatchPin, HIGH);
// }

// // <---- Setting the leds ----> //
// /**
//  * @brief Set a column of the cube
//  * @param _column (int) Which column we want to set
//  * @param _floor (int) On which floor we want to set it
//  * @param _state (bool) HIGH for turning on, LOW for turning off
//  * @param _timeOn (ulong) Time in ms we want it to be on (default is ALWAYS ON)
//  * @return None
//  */
// void LedCube8x8x8::setColumn(int _column, int _floor, bool _state, ulong _timeOn = ALWAYS_ON)
// {
//     for(int row = 0; row < 8; row++) {
//         leds[row][_column][_floor].state = _state;
//         leds[row][_column][_floor].setTimeOn(_timeOn);
//     }
// }

// /**
//  * @brief Set a row of the cube
//  * @param _row (int) Which row we want to set
//  * @param _floor (int) On which floor we want to set it
//  * @param _state (bool) HIGH for turning on, LOW for turning off
//  * @param _timeOn (ulong) Time in ms we want it to be on (default is ALWAYS ON)
//  * @return None
//  */
// void LedCube8x8x8::setRow(int _row, int _floor, bool _state, ulong _timeOn = ALWAYS_ON)
// {
//     for(int column = 0; column < 8; column++) {
//         leds[_row][column][_floor].state = _state;
//         leds[_row][column][_floor].setTimeOn(_timeOn);
//     }
// }

// /**
//  * @brief Set a pilar of the cube (the vertical ones)
//  * @param _row (int) Row coordinate of the pilar
//  * @param _column (int) Column coordinate of the pilar
//  * @param _state (bool) HIGH for turning on, LOW for turning off
//  * @param _timeOn (ulong) Time in ms we want it to be on (default is ALWAYS ON)
//  * @return None
//  */
// void LedCube8x8x8::setPilar(int _row, int _column, bool _state, ulong _timeOn = ALWAYS_ON)
// {
//     for(int floor = 0; floor < 8; floor++) {
//         leds[_row][_column][floor].state = _state;
//         leds[_row][_column][floor].setTimeOn(_timeOn);
//     }
// }

// /**
//  * @brief Set an entire floor of the cube
//  * @param _floor (int) Which floor we want to set 
//  * @param _state (bool) HIGH for turning on, LOW for turning off
//  * @param _timeOn (ulong) Time in ms we want it to be on (default is ALWAYS ON)
//  */
// void LedCube8x8x8::setFloor(int _floor, bool _state, ulong _timeOn = ALWAYS_ON)
// {
//     for(int column = 0; column < 8; column++)
//         for(int row = 0; row < 8; row++) {
//             leds[row][column][_floor].state = _state;
//             leds[row][column][_floor].setTimeOn(_timeOn);
//         }
// }

// /**
//  * @brief Set an entire wall of the cube (row side)
//  * @param _row (int) Which wall we want to set 
//  * @param _state (bool) HIGH for turning on, LOW for turning off
//  * @param _timeOn (ulong) Time in ms we want it to be on (default is ALWAYS ON)
//  */
// void LedCube8x8x8::setRowWall(int _row, bool _state, ulong _timeOn = ALWAYS_ON)
// {
//     for(int floor = 0; floor < 8; floor++) 
//         for(int column = 0; column < 8; column++) {
//             leds[_row][column][floor].state = _state;
//             leds[_row][column][floor].setTimeOn(_timeOn);
//         }
// }

// /**
//  * @brief Set an entire wall of the cube (column side)
//  * @param _row (int) Which wall we want to set 
//  * @param _state (bool) HIGH for turning on, LOW for turning off
//  * @param _timeOn (ulong) Time in ms we want it to be on (default is ALWAYS ON)
//  */
// void LedCube8x8x8::setColumnWall(int _column, bool _state, ulong _timeOn = ALWAYS_ON)
// {
//     for(int floor = 0; floor < 8; floor++) 
//         for(int row = 0; row < 8; row++) {
//             leds[row][_column][floor].state = _state;
//             leds[row][_column][floor].setTimeOn(_timeOn);
//         }
// }

// /**
//  * @brief Set every led on the cube
//  * @param _state (bool) HIGH for turning on, LOW for turning off
//  * @param _timeOn (ulong) Time in ms we want it to be on (default is ALWAYS ON)
//  */
// void LedCube8x8x8::setEverything(bool _state, ulong _timeOn = ALWAYS_ON)
// {
//     for(int floor = 0; floor < 8; floor++)
//         for(int column = 0; column < 8; column++)
//             for(int row = 0; row < 8; row++) {
//                 leds[row][column][floor].state = _state;
//                 leds[row][column][floor].setTimeOn(_timeOn);
//             }
// }

// /**
//  * @brief 
//  * 
//  * @param _row (int) On which row is the led
//  * @param _column (int) On which column is the led
//  * @param _floor (int) On which floor is the led
//  * @param _state (bool) HIGH for turning on, LOW for turning off
//  * @param _timeOn (ulong) Time in ms we want it to be on (default is ALWAYS ON)
//  */
// void LedCube8x8x8::setLed(int _row, int _column, int _floor, bool _state, ulong _timeOn = ALWAYS_ON)
// {
//     leds[_row][_column][_floor].state = _state;
//     leds[_row][_column][_floor].setTimeOn(_timeOn);
// }

// // <---- Settting the brightness --->
// /**
//  * @brief Set the brightness of the cube
//  * @param _brightness 0 for minimum, 255 for maximum
//  * @return None
//  */
// void LedCube8x8x8::setBrightness(byte _brightness)
// {
//     brightness = _brightness;
// }
// #pragma endregion

#include <LedCube8x8x8.h>

#define floorDataPin 46
#define floorLatchPin 48
#define floorClockPin 50

#define ledDataPin 7
#define ledLatchPin 6
#define ledClockPin 5
#define ledResetPin 4

LedCube8x8x8 Tesseract;

void setup()
{
    Tesseract.setShiftRegisterFloorPins(floorDataPin, floorClockPin, floorLatchPin);
    Tesseract.setShiftRegisterLedPins(ledDataPin, ledClockPin, ledLatchPin, ledResetPin);
}

// ulong timeLedsOn = 0;
// ulong timeControl = 0;

void loop()
{
    // Tesseract.setFloor(7, HIGH);
    // Tesseract.lightUp();
}

// <--- Intialize leds debug --->
    // for(byte floor = 0; floor < 8; floor++)
    // {
    //     Serial.print("Floor No. ");
    //     Serial.println(floor);
    //     for(byte column = 0; column < 8; column++)
    //     {
    //         for(byte row = 0; row < 8; row++)
    //         {
    //             Serial.print(Tesseract.leds[row][column][floor].significance);
    //             Serial.print(" ");
    //         }
    //         Serial.println("");
    //     }
    //     Serial.println("");
    //     Serial.println("");
    // }

// <--- Pin setup debug --->
    // digitalWrite(ledDataPin, HIGH);
    // digitalWrite(ledClockPin, HIGH);
    // digitalWrite(ledLatchPin, HIGH);
    // digitalWrite(ledResetPin, HIGH);
    //
    // digitalWrite(floorDataPin, HIGH);
    // digitalWrite(floorClockPin, HIGH);
    // digitalWrite(floorLatchPin, HIGH);
    //
    // delay(1000);
    //
    // digitalWrite(ledDataPin, LOW);
    // digitalWrite(ledClockPin, LOW);
    // digitalWrite(ledLatchPin, LOW);
    // digitalWrite(ledResetPin, LOW);
    //
    // digitalWrite(floorDataPin, LOW);
    // digitalWrite(floorClockPin, LOW);
    // digitalWrite(floorLatchPin, LOW);

// <--- Test if library now works --->
    // Tesseract.setLed(0, 0, 0, HIGH);
    // Tesseract.lightUp();

// <--- Initial state leds debug --->
    // for(byte floor = 0; floor < 8; floor++)
    // {
    //     Serial.print("Floor No. ");
    //     Serial.println(floor);
    //     for(byte column = 0; column < 8; column++)
    //     {
    //         for(byte row = 0; row < 8; row++)
    //         {
    //             Serial.print(Tesseract.leds[row][column][floor].state);
    //             Serial.print(" ");
    //         }
    //         Serial.println("");
    //     }
    //     Serial.println("");
    //     Serial.println("");
    // }

// <--- Set up with every fuction debug --->
    // <--- Set up one led debug --->
    // Tesseract.setLed(0, 0, 0, HIGH);
    //
    // <--- Set up column debug --->
    // Tesseract.setColumn(0, 0, HIGH);
    //
    // <--- Set up row debug --->
    // Tesseract.setRow(0, 0, HIGH);
    //
    // <--- Set up pilar debug --->
    // Tesseract.setPilar(0, 0, HIGH);
    //
    // <--- Set up floor debug --->
    // Tesseract.setFloor(0, HIGH);
    //
    // <--- Set up row wall debug --->
    // Tesseract.setRowWall(0, HIGH);
    //
    // <--- Set up column wall debug --->
    // Tesseract.setColumnWall(0, HIGH);
    //
    // <--- Set up everything debug --->
    // Tesseract.setEverything(HIGH);
    //
    // for(byte floor = 0; floor < 8; floor++)
    // {
    //     Serial.print("Floor No. ");
    //     Serial.println(floor);
    //     for(byte column = 0; column < 8; column++)
    //     {
    //         for(byte row = 0; row < 8; row++)
    //         {
    //             Serial.print(Tesseract.leds[row][column][floor].state);
    //             Serial.print(" ");
    //         }
    //         Serial.println("");
    //     }
    //     Serial.println("");
    //     Serial.println("");
    // }

// <--- Test if library now works --->
    // Tesseract.setFloor(0, HIGH);
    // Tesseract.lightUp();

// <--- clearRegisters() method debug -->
    // // Turn on the first floor
    // digitalWrite(floorLatchPin, LOW);
    // shiftOut(floorDataPin, floorClockPin, MSBFIRST, 0x80);
    // digitalWrite(floorLatchPin, HIGH);
    //
    // // Light up all the registers
    // for(int i = 0; i < 8; i++)
    // {
    //     digitalWrite(ledLatchPin, LOW);
    //     shiftOut(ledDataPin, ledClockPin, MSBFIRST, 0xFF);
    //     digitalWrite(ledLatchPin, HIGH);
    // }
    //
    // delay(5000);
    //
    // // Reset the registers
    // Tesseract.clearRegisters();
    //
    // delay(1000);
    //
    // // Light up all the registers
    // for(int i = 0; i < 8; i++)
    // {
    //     digitalWrite(ledLatchPin, LOW);
    //     shiftOut(ledDataPin, ledClockPin, MSBFIRST, 0xFF);
    //     digitalWrite(ledLatchPin, HIGH);
    // }

// <--- clearFloorValues() method debug -->
    // // Print register values before the light
    // for(int index = 0; index < 8; index++)
    // {
    //     Serial.print(Tesseract.floorValues[index]);
    //     Serial.print(" ");
    // }
    // Serial.println("");
    // Serial.println("");
    //
    // // Light up all the registers
    // // for(int i = 0; i < 8; i++)
    // // {
    // //     digitalWrite(ledLatchPin, LOW);
    // //     shiftOut(ledDataPin, ledClockPin, MSBFIRST, 0xFF - powInByte(2, i));
    // //     digitalWrite(ledLatchPin, HIGH);
    // // }
    //
    // Tesseract.setFloor(7, HIGH);
    // for(int intersection = 0; intersection < 8; intersection++)
    //     Tesseract.setLed(intersection, intersection, 7, LOW);
    //
    // // Check last floor status
    // Serial.println("Floor No. 7");
    // for(byte column = 0; column < 8; column++)
    // {
    //     for(byte row = 0; row < 8; row++)
    //     {
    //         Serial.print(Tesseract.leds[row][column][7].state);
    //         Serial.print(" ");
    //     }
    //     Serial.println("");
    // }
    // Serial.println("");
    //
    // // Run setRowValues()
    // Serial.println("Testing setRowValues()");
    // Tesseract.setNewFloorValues(7);
    //
    // // Print register values before the light
    // for(int index = 0; index < 8; index++)
    // {
    //     Serial.print(Tesseract.floorValues[index]);
    //     Serial.print(" ");
    // }
    // Serial.println("");
    //
    // // Run clearFloorValues()
    // Serial.println("Testing clearFloorValues()");
    // Tesseract.clearFloorValues();
    //
    // // Print final register values 
    // for(int index = 0; index < 8; index++)
    // {
    //     Serial.print(Tesseract.floorValues[index]);
    //     Serial.print(" ");
    // }
    // Serial.println("");

// <--- Test if library now works --->
    // Tesseract.setFloor(7, HIGH);
    // Tesseract.lightUp();

// <--- turnOnFloor() method debug --->
    // // Light up all the registers
    // for(int i = 0; i < 8; i++)
    // {
    //     digitalWrite(ledLatchPin, LOW);
    //     shiftOut(ledDataPin, ledClockPin, MSBFIRST, 0xFF);
    //     digitalWrite(ledLatchPin, HIGH);
    // }
    //
    // // Turn on last floor
    // // Tesseract.turnOnFloor(0);
    //
    // // Turn on every floor
    // // for(int i = 0; i < 8; i++)
    // // {
    // //     Tesseract.turnOnFloor(i);
    // //     delay(100);
    // // }

// <--- shiftOutNewValues() method debug --->
    // Light up all the registers
    // for(int i = 0; i < 8; i++)
    //     Tesseract.floorValues[i] = 0x01;
    //
    // // Print register values before the light
    // for(int index = 0; index < 8; index++)
    // {
    //     Serial.print(Tesseract.floorValues[index]);
    //     Serial.print(" ");
    // }
    //
    // // Turn on last floor
    //
    // Tesseract.turnOnFloor(7);
    //
    // // Shift out values
    // Tesseract.shiftOutNewValues();

// <--- Test if library now works --->
    // Tesseract.setFloor(7, HIGH);
    // Tesseract.lightUp();

// <--- checkLedsTimeOn() method debug --->
    // Tesseract.setFloor(7, HIGH);
    // for(byte column = 0; column < 8; column++)
    // {
    //     for(byte row = 0; row < 8; row++)
    //     {
    //         Serial.print(Tesseract.leds[row][column][7].timeOn);
    //         Serial.print(" ");
    //     }
    //     Serial.println("");
    // }
    // Serial.println("");
    // Serial.println("");
    //
    // Tesseract.checkLedsTimeOn();
    //
    // for(byte column = 0; column < 8; column++)
    // {
    //     for(byte row = 0; row < 8; row++)
    //     {
    //         Serial.print(Tesseract.leds[row][column][7].state);
    //         Serial.print(" ");
    //     }
    //     Serial.println("");
    // }
    //
    // Tesseract.setFloor(7, HIGH);
    //
    // for(byte column = 0; column < 8; column++)
    // {
    //     for(byte row = 0; row < 8; row++)
    //     {
    //         Serial.print(Tesseract.leds[row][column][7].timeOn);
    //         Serial.print(" ");
    //     }
    //     Serial.println("");
    // }
    //
    // Tesseract.lightUp();
    //
    // delay(10000);

// <--- Test if library now works --->
    // Tesseract.lightUp();

// <--- Testing Led Cube --->
    // Tesseract.setEverything(HIGH, 3000);
    // Tesseract.setFloor(7, HIGH);
    //
    // Tesseract.setLed(0, 0, 0, HIGH);
    // Tesseract.setLed(0, 7, 0, HIGH);
    // Tesseract.setLed(7, 0, 0, HIGH);
    // Tesseract.setLed(7, 7, 0, HIGH);
    // Tesseract.setLed(0, 0, 7, HIGH);
    // Tesseract.setLed(0, 7, 7, HIGH);
    // Tesseract.setLed(7, 0, 7, HIGH);
    // Tesseract.setLed(7, 7, 7, HIGH);
    //
    // Tesseract.setFloor(0, HIGH);
    // Tesseract.setFloor(7, HIGH);
    // Tesseract.setRowWall(0, HIGH);
    // Tesseract.setRowWall(7, HIGH);
    // Tesseract.setColumnWall(0, HIGH);
    // Tesseract.setColumnWall(7, HIGH);
    //
    // Tesseract.setRow(0, 7, HIGH);
    // Tesseract.setRow(7, 7, HIGH);
    // Tesseract.setRow(0, 0, HIGH);
    // Tesseract.setRow(7, 0, HIGH);
    //
    // Tesseract.setColumn(0, 0, HIGH);
    // Tesseract.setColumn(7, 0, HIGH);
    // Tesseract.setColumn(0, 7, HIGH);
    // Tesseract.setColumn(7, 7, HIGH);
    //    
    // Tesseract.setPilar(0, 0, HIGH);
    // Tesseract.setPilar(0, 7, HIGH);
    // Tesseract.setPilar(7, 0, HIGH);
    // Tesseract.setPilar(7, 7, HIGH);
    //
    // Tesseract.setFloor(0, LOW);
    // Tesseract.setFloor(1, HIGH);
    // Tesseract.setFloor(2, LOW);
    // Tesseract.setFloor(3, HIGH);
    // Tesseract.setFloor(4, LOW);
    // Tesseract.setFloor(5, HIGH);
    // Tesseract.setFloor(6, LOW);
    // Tesseract.setFloor(7, HIGH);
    //
    // if(millis()/1000 % 2)
    // {
    //     Tesseract.setFloor(0, LOW, 1000);
    //     Tesseract.setFloor(1, HIGH, 1000);
    //     Tesseract.setFloor(2, LOW, 1000);
    //     Tesseract.setFloor(3, HIGH, 1000);
    //     Tesseract.setFloor(4, LOW, 1000);
    //     Tesseract.setFloor(5, HIGH, 1000);
    //     Tesseract.setFloor(6, LOW, 1000);
    //     Tesseract.setFloor(7, HIGH, 1000);
    // }
    // else
    // {
    //     Tesseract.setFloor(0, HIGH, 1000);
    //     Tesseract.setFloor(1, LOW, 1000);
    //     Tesseract.setFloor(2, HIGH, 1000);
    //     Tesseract.setFloor(3, LOW, 1000);
    //     Tesseract.setFloor(4, HIGH, 1000);
    //     Tesseract.setFloor(5, LOW, 1000);
    //     Tesseract.setFloor(6, HIGH, 1000);
    //     Tesseract.setFloor(7, LOW, 1000);
    // }
    // Serial.println(Tesseract.cubeDataChanged);
    // Tesseract.lightUp();
    //
    // delay(10);

