#ifndef SIMPLEUTILS_THREADPOOL_HPP
#define SIMPLEUTILS_THREADPOOL_HPP

#include <functional>
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>

namespace simpleutils::Threading
{
    using Callback = std::function<void()>;

    class ThreadPool
    {
        public:
            ThreadPool();
            ~ThreadPool();

            bool Create(std::size_t poolSize);
            bool Submit(const Callback& task);
            void Stop();

        private:
            void workerLoop();

        private:
            std::queue<Callback> m_Tasks {};
            std::vector<std::thread> m_Workers {};
            std::mutex m_QueueMutex {};
            std::condition_variable m_Condition {};
            bool m_Stop {};
    };
} // namespace simpleutils::Tasks


#endif // SIMPLEUTILS_THREADPOOL_HPP