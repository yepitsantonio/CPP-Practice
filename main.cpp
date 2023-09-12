#include "Factorial.h"
#include "Threadpool.h"
#include <iostream>
#include <thread>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <iomanip>

int main()
{
    int tasks = -1;
    int threads = -1;
    std::string input;

    while (tasks <= 0)
    {
        std::cout << "Enter the number of Factorials you want to compute (only up to 20!): \n";
        std::getline(std::cin, input);

        std::stringstream mySS(input);
        // User input is a positive integer greater than 0 with no decimals
        if (mySS >> tasks && tasks > 0 && tasks <= 20 && mySS.eof() && input.find('.') == std::string::npos)
        {
            std::cout << tasks << " Factorial(s) to compute.\n";
        }
        else
        {
            tasks = -1;
            std::cout << "Invalid number of Factorials to compute\n";
        }
    }

    while (threads <= 0)
    {
        std::cout << "Enter the number of Threads to solve: \n";
        std::getline(std::cin, input);

        std::stringstream mySS(input);
        // Number of threads must be within the the max number of threads the system can support
        if (mySS >> threads && threads > 0 && threads <= std::thread::hardware_concurrency() && mySS.eof() && input.find('.') == std::string::npos)
        {
            std::cout << threads << " Thread(s) to solve.\n";
        }
        else
        {
            threads = -1;
            std::cout << "Invalid number of Threads to solve\n";
        }
    }

    Threadpool threadpool;
    threadpool.start(threads);
    auto startTime = std::chrono::high_resolution_clock::now();

    for (int i = 1; i <= tasks; i++)
    {
        threadpool.addTask(i);
    }

    while (threadpool.busy())
    {
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    threadpool.stop();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    double programTime = static_cast<double>(duration.count()) / 1e6;

    std::cout << "Execution time is : " << std::setprecision(15) << programTime << std::endl;

    return 0;
}