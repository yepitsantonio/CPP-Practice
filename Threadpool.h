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
    void start(int n);
    void addTask(int n);
    bool busy();
    void stop();

private:
    void LoopThread();
    bool terminate = false;
    std::vector<std::thread> pool;
    std::mutex mutex;
    std::condition_variable cv;
    std::queue<int> tasks;
};
#endif