#include "ThreadPool.h"
#include "atomic"


ThreadPool::ThreadPool(uint8_t numThreads) : m_uNumThreads(numThreads), m_bStopFlag(0)
{
    for (uint8_t i=0; i < m_uNumThreads; i++)
    {
        workerThreads.emplace_back([this]{this->workerLoop();});
    }
}

ThreadPool::~ThreadPool()
{
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_bStopFlag = true;
    }
    m_condition.notify_all();
    for (auto& t : workerThreads)
    {
        if (t.joinable())
        {
            t.join();
        }
    }
}

// void ThreadPool::enqueue(std::function<void()> task)
// {
//     {
//         std::unique_lock lk(m_mutex);
//         m_queueTasks.push(std::move(task));
//     }
//     m_condition.notify_one();
// }


void ThreadPool::waitForTask()
{
    // std::unique_lock<std::mutex> lock(m_mutex);
    // m_condition.wait(lock, [this]{
    //     return m_queueTasks.empty();
    // });
    while (m_taskCount > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void ThreadPool::workerLoop()
{
    while (true)
    {
        std::function<void()> task;
        {    
            std::unique_lock lk(m_mutex);
            m_condition.wait(lk, [this]{
                return m_bStopFlag || !m_queueTasks.empty();
            });
            if (m_bStopFlag && m_queueTasks.empty())
                break;
            
            task = std::move(m_queueTasks.front());
            m_queueTasks.pop();
            // lk.unlock();
        }
        task();
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            if (m_queueTasks.empty())
                m_condition.notify_all();  // Notify waiting threads
        }
    }
}
