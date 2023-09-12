#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <iostream>
#include <condition_variable>

#include "Threadpool.h"
#include "Factorial.h"

void Threadpool::start(int n)
{
    const int threads = n;
    for (int i = 0; i < threads; i++)
    {
        pool.emplace_back(std::thread(&Threadpool::LoopThread, this));
    }
}

void Threadpool::LoopThread()
{
    while (true)
    {
        int n;
        {
            std::unique_lock<std::mutex> lock(mutex);
            cv.wait(lock, [this]
                    { return !tasks.empty() || terminate; });
            if (terminate)
            {
                return;
            }
            n = tasks.front();
            tasks.pop();
        }
        Factorial factorial(n);
        factorial();
    }
}

void Threadpool::addTask(int n)
{
    {
        std::unique_lock<std::mutex> lock(mutex);
        tasks.push(n);
    }
    cv.notify_one();
}

bool Threadpool::busy()
{
    std::unique_lock<std::mutex> lock(mutex);
    return !tasks.empty();
}

void Threadpool::stop()
{
    {
        std::unique_lock<std::mutex> lock(mutex);
        terminate = true;
    }
    cv.notify_all();
    for (std::thread &thread : pool)
    {
        thread.join();
    }
    pool.clear();
}