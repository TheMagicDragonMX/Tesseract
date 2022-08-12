#define dataPin 7
#define latchPin 6
#define clockPin 5
#define resetPin 4

#define floorDataPin 46
#define floorLatchPin 48
#define floorClockPin 50

void setup()
{
	pinMode(dataPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(resetPin, OUTPUT);

	pinMode(floorDataPin, OUTPUT);
    pinMode(floorLatchPin, OUTPUT);
    pinMode(floorClockPin, OUTPUT);

    digitalWrite(resetPin, HIGH);

    //Serial.begin(9600);
}

unsigned long counter = 0;

void loop()
{
    // if(counter == 8) {
    //     for(int i = 0; i < 8; i++)
    //     {
    //         digitalWrite(latchPin, LOW);
    //         shiftOut(dataPin, clockPin, MSBFIRST, 0x00);
    //         digitalWrite(latchPin, HIGH);
    //     }
    //     counter = 0;
    // }

    //counter = micros();
    for(int i = 0; i < 8; i++)
    {
        digitalWrite(latchPin, LOW);
	    shiftOut(dataPin, clockPin, MSBFIRST, 0xFF);
        digitalWrite(latchPin, HIGH);
    }

    digitalWrite(floorLatchPin, LOW);
	shiftOut(floorDataPin, floorClockPin, MSBFIRST, 0b00000001);
    digitalWrite(floorLatchPin, HIGH);
    //delayMicroseconds(2100);

    for(int i = 0; i < 8; i++)
    {
        digitalWrite(latchPin, LOW);
	    shiftOut(dataPin, clockPin, MSBFIRST, 0x00);
        digitalWrite(latchPin, HIGH);
    }

    digitalWrite(floorLatchPin, LOW);
	shiftOut(floorDataPin, floorClockPin, MSBFIRST, 0b00000010);
    digitalWrite(floorLatchPin, HIGH);
    //delayMicroseconds(2100);

    for(int i = 0; i < 8; i++)
    {
        digitalWrite(latchPin, LOW);
	    shiftOut(dataPin, clockPin, MSBFIRST, 0xFF);
        digitalWrite(latchPin, HIGH);
    }
    
    digitalWrite(floorLatchPin, LOW);
	shiftOut(floorDataPin, floorClockPin, MSBFIRST, 0b00000100);
    digitalWrite(floorLatchPin, HIGH);
    //delayMicroseconds(2100);

    for(int i = 0; i < 8; i++)
    {
        digitalWrite(latchPin, LOW);
	    shiftOut(dataPin, clockPin, MSBFIRST, 0x00);
        digitalWrite(latchPin, HIGH);
    }
    
    digitalWrite(floorLatchPin, LOW);
	shiftOut(floorDataPin, floorClockPin, MSBFIRST, 0b00001000);
    digitalWrite(floorLatchPin, HIGH);
    //delayMicroseconds(2100);

    for(int i = 0; i < 8; i++)
    {
        digitalWrite(latchPin, LOW);
	    shiftOut(dataPin, clockPin, MSBFIRST, 0xFF);
        digitalWrite(latchPin, HIGH);
    }
    
    digitalWrite(floorLatchPin, LOW);
	shiftOut(floorDataPin, floorClockPin, MSBFIRST, 0b00010000);
    digitalWrite(floorLatchPin, HIGH);
    //delayMicroseconds(2100);

    for(int i = 0; i < 8; i++)
    {
        digitalWrite(latchPin, LOW);
	    shiftOut(dataPin, clockPin, MSBFIRST, 0x00);
        digitalWrite(latchPin, HIGH);
    }
    
    digitalWrite(floorLatchPin, LOW);
	shiftOut(floorDataPin, floorClockPin, MSBFIRST, 0b00100000);
    digitalWrite(floorLatchPin, HIGH);
    //delayMicroseconds(2100);

    for(int i = 0; i < 8; i++)
    {
        digitalWrite(latchPin, LOW);
	    shiftOut(dataPin, clockPin, MSBFIRST, 0xFF);
        digitalWrite(latchPin, HIGH);
    }
    
    digitalWrite(floorLatchPin, LOW);
	shiftOut(floorDataPin, floorClockPin, MSBFIRST, 0b01000000);
    digitalWrite(floorLatchPin, HIGH);
    //delayMicroseconds(2100);

    for(int i = 0; i < 8; i++)
    {
        digitalWrite(latchPin, LOW);
	    shiftOut(dataPin, clockPin, MSBFIRST, 0x00);
        digitalWrite(latchPin, HIGH);
    }
    
    digitalWrite(floorLatchPin, LOW);
	shiftOut(floorDataPin, floorClockPin, MSBFIRST, 0b10000000);
    digitalWrite(floorLatchPin, HIGH);
    //delayMicroseconds(2100);

    //Serial.println(micros() - counter);

    // delay(1000);

    // digitalWrite(latchPin, LOW);
	// shiftOut(dataPin, clockPin, MSBFIRST, 0xFF);
    // digitalWrite(latchPin, HIGH);
    // delay(1000);
    
    //counter++;
    
}
