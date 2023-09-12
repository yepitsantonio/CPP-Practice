#include <iostream>

#include "Factorial.h"

int count = 0;

Factorial::Factorial(int n) : number(n), result(1)
{
}

// operator() can treat object as a function call, ex. factorial();
void Factorial::operator()()
{
    for (int i = 1; i <= number; i++)
    {
        result *= i;
    }
    std::cout << result << std::endl;

    // Debug code to make sure all tasks are complete
    count++;
    std::cout << "The count is " << count << std::endl;
}