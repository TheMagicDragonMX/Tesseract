
class Led
{
    public:
    bool state = false;
};

Led bunchOfLeds[2][2];


void setup()
{
	Serial.begin(9600);
}

void loop()
{
    bunchOfLeds[0][0].state = true;
    bunchOfLeds[0][1].state = false;
    bunchOfLeds[1][0].state = true;
    bunchOfLeds[1][1].state = false;
;
    Serial.print("0, 0 Led state is: ");
    Serial.println(bunchOfLeds[0][0].state);
    Serial.print("0, 1 Led state is: ");
    Serial.println(bunchOfLeds[0][1].state);
    Serial.print("1, 0 Led state is: ");
    Serial.println(bunchOfLeds[1][0].state);
    Serial.print("1, 1 Led state is: ");
    Serial.println(bunchOfLeds[1][1].state);

    delay(10000);
}

/*
Notes:
Seems like objects array works the same as basic type arrays 
*/