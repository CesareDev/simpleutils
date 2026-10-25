#include <simpleutils/Tasks/ThreadPool.hpp>

#include <stdexcept>

namespace simpleutils::Tasks
{
    ThreadPool::ThreadPool(std::size_t poolSize)
    {
        if (poolSize == 0)
            throw std::invalid_argument("ThreadPool size must be greater than 0");

        for (std::size_t i {}; i < poolSize; ++i)
        {
            m_Workers.emplace_back([this] {
                workerLoop();
            });
        }
    }

    ThreadPool::~ThreadPool()
    {
        Stop();
    }

    bool ThreadPool::Submit(const Task& task)
    {
        {
            std::lock_guard<std::mutex> lock(m_QueueMutex);

            if (m_Stop) return false;

            m_Tasks.push(task);
        }

        m_Condition.notify_one();

        return true;
    }

    void ThreadPool::Stop()
    {
        {
            std::lock_guard<std::mutex> lock(m_QueueMutex);
            m_Stop = true;
        }

        m_Condition.notify_all();

        for (auto& worker : m_Workers)
        {
            if (worker.joinable())
                worker.join();
        }
    }

    void ThreadPool::workerLoop()
    {
        while (true)
        {
            Task task;

            {
                std::unique_lock<std::mutex> lock(m_QueueMutex);

                m_Condition.wait(lock, [this] {
                    return m_Stop || !m_Tasks.empty();
                });

                if (m_Stop && m_Tasks.empty()) break;

                task = std::move(m_Tasks.front());
                m_Tasks.pop();
            }

            task();
        }
    }
} // namespace simpleutils::Tasks
