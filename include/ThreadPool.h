#pragma once
#include <cstdint>
#include <functional>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>

class ThreadPool
{
private:
    uint8_t m_uNumThreads;
    std::vector<std::thread> workerThreads;
    std::queue<std::function<void()>> m_queueTasks;
    std::mutex m_mutex; 
    std::condition_variable m_condition;
    bool m_bStopFlag;

    void workerLoop();

public:
    ThreadPool(uint8_t numThreads);
    ~ThreadPool();
    
    void enqueue(std::function<void()>);
};