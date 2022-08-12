#include <LedCube8x8x8.h>

#define ledDataPin 7
#define ledClockPin 6
#define ledLatchPin 5
#define ledResetPin 4

#define floorDataPin 13
#define floorClockPin 12
#define floorLatchPin 11

LedCube8x8x8 Tesseract;

void setup()
{
    Tesseract.setShiftRegisterLedPins(ledDataPin, ledClockPin, ledLatchPin, ledResetPin);
    Tesseract.setShiftRegisterFloorPins(floorDataPin, floorClockPin, floorLatchPin);

    Tesseract.setEverything(HIGH);
}

void loop()
{
    Tesseract.lightUp();
}
