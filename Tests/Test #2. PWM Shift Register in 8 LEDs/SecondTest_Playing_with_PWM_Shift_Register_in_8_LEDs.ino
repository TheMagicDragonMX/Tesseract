#include <ShiftRegisterPWM.h>
#define LATCH_PIN 4
#define CLOCK_PIN 3
#define DATA_PIN 2

int LedsValue[10] = { 0, 1, 2, 4, 8, 16, 32, 64, 128, 255};
enum LedTags { ALLOFF, LED_1, LED_2, LED_3, LED_4, LED_5, LED_6, LED_7, LED_8, ALLON };

ShiftRegisterPWM sr(3, 16);

int value = 0;
int wave = 0;
bool goingUp = true;

void setup()
{
	pinMode(LATCH_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);

    sr.interrupt(ShiftRegisterPWM::UpdateFrequency::Slow);
}

void loop()
{
    if(goingUp)
        wave++;
    else
        wave--;

    if(wave == 255)
        goingUp = false;

    if(wave == 0)
        goingUp = true;

    sr.set(0, wave);
    sr.set(1, wave);
    sr.set(2, wave);
    sr.set(3, wave);
    sr.set(4, wave);
    sr.set(5, wave);
    sr.set(6, wave);
    sr.set(7, wave);

    sr.set(8, 255 - wave);
    sr.set(9, 255 - wave);
    sr.set(10, 255 - wave);
    sr.set(11, 255 - wave);
    sr.set(12, 255 - wave);
    sr.set(13, 255 - wave);
    sr.set(14, 255 - wave);
    sr.set(15, 255 - wave);

    sr.set(16, wave);
    sr.set(17, wave);
    sr.set(18, wave);
    sr.set(19, wave);
    sr.set(20, wave);
    sr.set(21, wave);
    sr.set(22, wave);
    sr.set(23, wave);
    delayMicroseconds(500);
}