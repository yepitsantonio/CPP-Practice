#ifndef __THREADPOOL_H
#define __THREADPOOL_H

#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <iostream>
#include <condition_variable>
class Threadpool
{
public:
    static Threadpool &getInstance();
    // No Threadpool cloning or assigning
    Threadpool(Threadpool &clone) = delete;
    void operator=(const Threadpool &) = delete;

    void start(int numThreads);
    void addTask(int numTasks);
    bool busy();
    void stop();

private:
    Threadpool();
    static Threadpool *instance;

    void LoopThread();
    bool terminate = false;
    std::vector<std::thread> pool;
    std::mutex mutex;
    std::condition_variable cv;
    std::queue<int> tasks;
};
#endif