#ifndef SIMPLEUTILS_THREADPOOL_HPP
#define SIMPLEUTILS_THREADPOOL_HPP

#include <simpleutils/Threading/Thread.hpp>
#include <simpleutils/Threading/Runnable.hpp>

#include <queue>
#include <condition_variable>

namespace simpleutils::Threading
{
    class ThreadPool
    {
        public:
            using Callback = std::function<void()>;

        public:
            ThreadPool() = default;
            ~ThreadPool();

            ThreadPool(const ThreadPool&) = delete;
            ThreadPool& operator=(const ThreadPool&) = delete;

            bool Create(std::size_t poolSize);
            bool Submit(const Callback& task);
            bool Submit(Runnable& runnable);
            void Stop();

        private:
            void workerLoop();

        private:
            std::queue<Callback> m_Tasks {};
            std::vector<std::unique_ptr<Thread>> m_Workers {};
            std::mutex m_QueueMutex {};
            std::condition_variable m_Condition {};
            bool m_Stop {};
    };
} // namespace simpleutils::Tasks


#endif // SIMPLEUTILS_THREADPOOL_HPP