
#include <simpleutils/Threading/ThreadPool.hpp>

namespace simpleutils::Threading
{
    ThreadPool::~ThreadPool()
    {
        Stop();
    }

    bool ThreadPool::Create(std::size_t poolSize)
    {
        if (poolSize == 0 || !m_Workers.empty() || m_Stop)
            return false;

        for (std::size_t i {}; i < poolSize; ++i)
        {
            auto worker = std::make_unique<Thread>();

            bool workerStart = worker->Start([this]() { 
                workerLoop();
            });

            if (!workerStart)
            {
                Stop();
                return false;
            }

            m_Workers.push_back(std::move(worker));
        }

        return true;
    }

    bool ThreadPool::Submit(const Callback& task)
    {
        if (!task)
            return false;

        {
            std::lock_guard<std::mutex> lock(m_QueueMutex);

            if (m_Stop || m_Workers.empty())
                return false;

            m_Tasks.push(task);
        }

        m_Condition.notify_one();

        return true;
    }

    bool ThreadPool::Submit(Runnable& runnable)
    {
        return Submit([&runnable]() { runnable.Run(); });
    }

    void ThreadPool::Stop()
    {
        {
            std::lock_guard<std::mutex> lock(m_QueueMutex);
            m_Stop = true;
        }

        m_Condition.notify_all();

        for (auto& worker : m_Workers)
            worker->Join();

        m_Workers.clear();
    }

    void ThreadPool::workerLoop()
    {
        while (true)
        {
            Callback task {};

            {
                std::unique_lock<std::mutex> lock(m_QueueMutex);

                m_Condition.wait(lock, [this]() {
                    return m_Stop || !m_Tasks.empty();
                });

                if (m_Stop && m_Tasks.empty())
                    break;

                task = std::move(m_Tasks.front());
                m_Tasks.pop();
            }

            task();
        }
    }
}
