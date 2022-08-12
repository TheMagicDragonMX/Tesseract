#include <Array.h>

Array<int, 8> leds;

void setup()
{
	Serial.begin(9600);
    int i = 0;
    for(int i = 0; i < 8; i++)
        leds[i] = i; 
    
    Serial.println("Counting:");
}

void loop()
{
	for(int number : leds)
    {
        Serial.println(number);
        delay(1000);
    }
         
}
