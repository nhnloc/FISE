#pragma once
#include <cstdint>
#include <functional>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <future>
#include <atomic>

class ThreadPool
{
private:
    uint8_t m_uNumThreads;
    std::vector<std::thread> workerThreads;
    std::queue<std::function<void()>> m_queueTasks;
    std::mutex m_mutex; 
    std::condition_variable m_condition;
    // bool m_bStopFlag;
    std::atomic<bool> m_bStopFlag;
    std::atomic<int> m_taskCount;

    void workerLoop();

public:
    ThreadPool(uint8_t numThreads);
    ~ThreadPool();
    
    // void enqueue(std::function<void()>);
    template <class F, class... Args>
    auto enqueue(F&& f, Args&&... args)
        -> std::future<std::invoke_result_t<F, Args...>>
    {
        using ReturnType = std::invoke_result_t<F, Args...>;

        auto task = std::make_shared<std::packaged_task<ReturnType()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<ReturnType> result = task->get_future();

        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_queueTasks.emplace([task]() { (*task)(); });
        }

        m_taskCount++;              // Track number of unfinished tasks
        m_condition.notify_one();  // Wake up one worker
        return result;
    }
    void waitForTask();
};