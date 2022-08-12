#include <iostream>

typedef uint8_t byte;

int main()
{
    byte number = 0b00001111;
    std::cout << (int)number << std::endl;

    for (int i = 0; i < 8; i++, number /= 2)
    {
        std::cout << number % 2; //<< " " << (int)number << " ";
    }
}

