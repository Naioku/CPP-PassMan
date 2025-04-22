#include <iostream>

#include "ExampleClass.h"

int main()
{
    std::cout << "Hello, World!" << std::endl;
    ExampleClass exampleClass;
    std::cout << exampleClass.add(1, 2) << std::endl;
    return 0;
}
