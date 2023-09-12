#include <iostream>

#include "Factorial.h"

Factorial::Factorial(int n) : number(n), result(1)
{
}

void Factorial::operator()()
{
    for (int i = 1; i <= number; i++)
    {
        result *= i;
    }
    std::cout << result << std::endl;
}