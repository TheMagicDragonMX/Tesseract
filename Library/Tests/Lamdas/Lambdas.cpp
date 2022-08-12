#include <iostream>

void forEach(int array[], void (*printDouble)(int))
{
    for (int index = 0; index < 3; index++)
        printDouble(array[index]);
}

int main()
{
    int array[] = {1, 2, 3};
    forEach(array, [](int number) { 
        std::cout << number * 2 << " "; 
    });
}
