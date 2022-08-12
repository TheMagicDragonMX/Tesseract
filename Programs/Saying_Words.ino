#define floorDataPin 16
#define floorLatchPin 15
#define floorClockPin 14

#define ledDataPin 12
#define outputEnablePin 11
#define ledLatchPin 10
#define ledClockPin 9
#define ledResetPin 8

#include <LedCube8x8x8.h>

LedCube8x8x8 Tesseract;

void setup()
{
	Tesseract.setShiftRegisterFloorPins(floorDataPin, floorClockPin, floorLatchPin);
    Tesseract.setShiftRegisterLedPins(ledDataPin, ledClockPin, ledLatchPin, ledResetPin);

    digitalWrite(outputEnablePin, LOW);
}

void loop()
{
    a
	
}
