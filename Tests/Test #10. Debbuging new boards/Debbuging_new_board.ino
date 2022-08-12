#include <LedCube8x8x8.h>

#define HIGHEST_FLOOR 7
#define LOWEST_FLOOR 0

#define floorDataPin 1
#define floorLatchPin 15
#define floorClockPin 14

#define ledDataPin 12
#define outputEnablePin 11
#define ledLatchPin 10
#define ledClockPin 9
#define ledResetPin 8

LedCube8x8x8 Tesseract;

void setup()
{
	Tesseract.setShiftRegisterFloorPins(floorDataPin, floorClockPin, floorLatchPin);
    Tesseract.setShiftRegisterLedPins(ledDataPin, ledClockPin, ledLatchPin, ledResetPin);
    
    // pinMode(ledDataPin, OUTPUT);
    pinMode(outputEnablePin, OUTPUT);
    // pinMode(ledLatchPin, OUTPUT);
    // pinMode(ledClockPin, OUTPUT);
    // pinMode(ledResetPin, OUTPUT);

    // pinMode(floorDataPin, OUTPUT);
    // pinMode(floorLatchPin, OUTPUT);
    // pinMode(floorClockPin, OUTPUT);

    // digitalWrite(floorLatchPin, LOW);
    // shiftOut(floorDataPin, floorClockPin, MSBFIRST, 0x80);
    // digitalWrite(floorLatchPin, HIGH);    

    digitalWrite(outputEnablePin, LOW);
    // digitalWrite(ledResetPin, HIGH);

    // digitalWrite(ledLatchPin, LOW);
    // shiftOut(ledDataPin, ledClockPin, MSBFIRST, 0xF0);
    // shiftOut(ledDataPin, ledClockPin, MSBFIRST, 0xFF);
    // shiftOut(ledDataPin, ledClockPin, MSBFIRST, 0xFF);
    // shiftOut(ledDataPin, ledClockPin, MSBFIRST, 0xFF);
    // shiftOut(ledDataPin, ledClockPin, MSBFIRST, 0xFF);
    // shiftOut(ledDataPin, ledClockPin, MSBFIRST, 0xFF);
    // shiftOut(ledDataPin, ledClockPin, MSBFIRST, 0xFF);
    // shiftOut(ledDataPin, ledClockPin, MSBFIRST, 0xFF);
    // digitalWrite(ledLatchPin, HIGH);

    
    
    //Tesseract.setFloor(7, HIGH);
    Tesseract.setEverything(HIGH);
}

void loop()
{
	Tesseract.lightUp();

    // for(int i = 0; i <= 8; i++) {
    //     digitalWrite(floorLatchPin, LOW);
    //     shiftOut(floorDataPin, floorClockPin, MSBFIRST, powInByte(2, i));
    //     digitalWrite(floorLatchPin, HIGH);
    //     delay(1000);
    // }
}
