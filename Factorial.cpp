#include <iostream>

#include "Factorial.h"

int count = 0;

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
    count++;
    std::cout << "The count is " << count << std::endl;
}