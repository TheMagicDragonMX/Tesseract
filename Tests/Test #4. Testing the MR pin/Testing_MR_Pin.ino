#define DATA_PIN 11
#define LATCH_PIN 10
#define CLOCK_PIN 9
#define RESET_PIN 8


void setup()
{
	pinMode(DATA_PIN, OUTPUT);
    pinMode(LATCH_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(RESET_PIN, OUTPUT);

    digitalWrite(RESET_PIN, HIGH);
}

void loop()
{
    digitalWrite(LATCH_PIN, LOW);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 0b01010101);
    digitalWrite(LATCH_PIN, HIGH);
    delay(5000);


    digitalWrite(LATCH_PIN, LOW);
    digitalWrite(RESET_PIN, LOW);
//    delay(1000);
    digitalWrite(RESET_PIN, HIGH);
    digitalWrite(LATCH_PIN, HIGH);
    
    delay(1000);
}

/*
Notes:
So, I've learned that in order to clear all the outputs from the register, both latch and reset pins need to go low,
then both go back to high again
*/