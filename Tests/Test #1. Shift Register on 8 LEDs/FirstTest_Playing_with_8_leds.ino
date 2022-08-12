#define LATCH_PIN 9
#define CLOCK_PIN 8
#define DATA_PIN 10
#define PWM_PIN 3

int LedsValue[10] = { 0, 1, 2, 4, 8, 16, 32, 64, 128, 255};
enum LedTags { ALLOFF, LED_1, LED_2, LED_3, LED_4, LED_5, LED_6, LED_7, LED_8, ALLON };



void setup()
{
	pinMode(LATCH_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);

    pinMode(PWM_PIN, OUTPUT);

    Serial.begin(9600);
}

int value = 0;
int wave = 0;
bool goingUp = true;

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

    value = LedsValue[LED_1];
    shiftOutNumber(value);
    analogWrite(PWM_PIN, wave);

    //Serial.println(value);
    delay(2);

    
}

void shiftOutNumber(int value)
{
    digitalWrite(LATCH_PIN, LOW);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, value);
    digitalWrite(LATCH_PIN, HIGH);
}

/* 
Notes
1° -> Byte Manipulation
Tried to manupulate the output by using "byte" type and shift operator, I discarted the idea 
becaouse it was going to be difficult to select which leds would turn on

2° -> Int aray with numbers
I used an int array that keeped the number that represents each led on the shift register, it worked well
so I think I will improve it by using enums to refer those numbers
 
3° -> Adding an enum
Adding an enum that works as interpreter of the int array indexes works fine, now it easy to send a number
to the shift register, next step is evaluate how it could work with PWM

UPDATE: LED's only use a max value of 6 mA, giving a max of 384 mA for an entire floor of 64 LED's, Arduino
suports a current supply of 400 mA, so it is perfectly fine for an entire floor :,D
With that said, lets see how we can implement PWM

4° -> First PWM interaction
Now I can set an special voltage value to every led in the register, with everyone having the same voltage, 
now I'll try to make every LED individual.

UPDATE: Giving each LED a PWM value in particular seems very difficult, so I'm going to use the already existent
PWM Shift Register library, which I'll test in another .ino file
*/