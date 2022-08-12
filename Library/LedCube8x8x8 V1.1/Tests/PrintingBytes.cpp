#include <iostream>
typedef uint8_t byte;

int main()
{
    byte number = 0b00001111;
    
    for (byte y = 0; y < 8; y++) {
        //ledCube[z][y][x].setStatus(design & 1, timeOn);
        // std::cout << (number & 0b10000000) / 128; 
        std::cout << ((number & 128) != 0);
        number <<= 1;
    }
}