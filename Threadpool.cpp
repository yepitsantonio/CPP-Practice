#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <iostream>
#include <condition_variable>

#include "Threadpool.h"
#include "Factorial.h"

// Singleton Threadpool
Threadpool::Threadpool() {}

// initialize instance pointer to null
Threadpool *Threadpool::instance = nullptr;

// Since instance is null, create new Threadpool and return the pointer to it, allows only one Threadpool object to exist
Threadpool &Threadpool::getInstance()
{
    if (!instance)
    {
        instance = new Threadpool();
    }
    return *instance;
}

// Place threads in a pool and run the infinite loop method to assign tasks
void Threadpool::start(int n)
{
    const int threads = n;
    for (int i = 0; i < threads; i++)
    {
        pool.emplace_back(std::thread(&Threadpool::LoopThread, this));
    }
}

// Keep threads alive and wait for tasks in the queue, if task in queue, do the task
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

// Add integer of task to be completed in queue and notify a thread(if any) to work on
void Threadpool::addTask(int n)
{
    {
        std::unique_lock<std::mutex> lock(mutex);
        tasks.push(n);
    }
    cv.notify_one();
}

// Check if queue is ever empty to indicate when work is done
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