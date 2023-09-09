#include "Factorial.h"
#include <iostream>
#include <thread>
#include <string>
#include <sstream>

int main()
{
    int tasks = -1;
    std::string input;

    while (tasks <= 0)
    {
        std::cout << "Enter the number of Factorials you want to compute: \n";
        std::getline(std::cin, input);

        std::stringstream mySS(input);

        if (mySS >> tasks && tasks > 0 && mySS.eof() && input.find('.') == std::string::npos)
        {
            std::cout << tasks << " Factorial(s) to compute.\n";
        }
        else
        {
            tasks = -1;
            std::cout << "Invalid number of Factorials to compute\n";
        }
    }

    return 0;
}