#include <LedCube8x8x8.h>

#define HIGHEST_FLOOR 7
#define LOWEST_FLOOR 0

#define florDataPin 16
#define florLatchPin 15
#define florClockPin 14

#define ledDataPin 12
#define outputEnablePin 11
#define ledLatchPin 10
#define ledClockPin 9
#define ledResetPin 8

#define MAX_AMOUNT_OF_DROPS 20

LedCube8x8x8 Tesseract;

class WaterDrop
{
private:
    byte rowPosition, columnPosition, floorPosition;
    ulong timeDropIsOn, timeToFall, timeToFallAgain;

public:
    WaterDrop(ulong, ulong);

    bool isTimeToFall();
    void fall();
    void reset();
};

WaterDrop::WaterDrop(ulong _timeDropIsOn, ulong _timeToFall)
{
    rowPosition = random(0, 8);
    columnPosition = random(0, 8);
    floorPosition = HIGHEST_FLOOR;

    timeDropIsOn = _timeDropIsOn;
    timeToFall = _timeToFall;
    timeToFallAgain = millis() + timeToFall;

    Tesseract.setLed(rowPosition, columnPosition, floorPosition, HIGH, timeDropIsOn);
}

bool WaterDrop::isTimeToFall()
{
    if(millis() > timeToFallAgain)
        return true;
    else
        return false;
}

void WaterDrop::fall()
{
    if(floorPosition == LOWEST_FLOOR) {
        reset();
        return;
    }

    floorPosition--;
    timeToFallAgain = millis() + timeToFall;

    Tesseract.setLed(rowPosition, columnPosition, floorPosition, HIGH, timeDropIsOn);
}

void WaterDrop::reset()
{
    rowPosition = random(0, 8);
    columnPosition = random(0, 8);
    floorPosition = HIGHEST_FLOOR;
    timeToFallAgain = millis() + timeToFall;

    Tesseract.setLed(rowPosition, columnPosition, floorPosition, HIGH, timeDropIsOn);
}

ulong rainOnDropTime = 500;
ulong rainTimeToFallTime = 300;

WaterDrop rain[MAX_AMOUNT_OF_DROPS] = 
{
    WaterDrop(rainOnDropTime, rainTimeToFallTime), WaterDrop(rainOnDropTime, rainTimeToFallTime), WaterDrop(rainOnDropTime, rainTimeToFallTime), 
    WaterDrop(rainOnDropTime, rainTimeToFallTime), WaterDrop(rainOnDropTime, rainTimeToFallTime), WaterDrop(rainOnDropTime, rainTimeToFallTime), 
    WaterDrop(rainOnDropTime, rainTimeToFallTime), WaterDrop(rainOnDropTime, rainTimeToFallTime), WaterDrop(rainOnDropTime, rainTimeToFallTime), 
    WaterDrop(rainOnDropTime, rainTimeToFallTime), WaterDrop(rainOnDropTime, rainTimeToFallTime), WaterDrop(rainOnDropTime, rainTimeToFallTime), 
    WaterDrop(rainOnDropTime, rainTimeToFallTime), WaterDrop(rainOnDropTime, rainTimeToFallTime), WaterDrop(rainOnDropTime, rainTimeToFallTime), 
    WaterDrop(rainOnDropTime, rainTimeToFallTime), WaterDrop(rainOnDropTime, rainTimeToFallTime), WaterDrop(rainOnDropTime, rainTimeToFallTime), 
    WaterDrop(rainOnDropTime, rainTimeToFallTime), WaterDrop(rainOnDropTime, rainTimeToFallTime),
};

void setup()
{
    Tesseract.setShiftRegisterFloorPins(florDataPin, florClockPin, florLatchPin);
    Tesseract.setShiftRegisterLedPins(ledDataPin, ledClockPin, ledLatchPin, ledResetPin);

    digitalWrite(outputEnablePin, LOW);

    // for(int waterDrop = 0; waterDrop < 10; waterDrop++) {
    //     rain[waterDrop] = WaterDrop(rainTimeToFallTime, rainTimeToFallTime);
}

int amountOfDrops = 0;

void loop()
{
    if((millis() / 1000) > amountOfDrops and amountOfDrops < MAX_AMOUNT_OF_DROPS)
        amountOfDrops++;

    for(byte waterDrop = 0; waterDrop < amountOfDrops; waterDrop++)
        if(rain[waterDrop].isTimeToFall())
            rain[waterDrop].fall();

    Tesseract.lightUp();
}
              