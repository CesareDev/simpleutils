#ifndef SIMPLEUTILS_THREADPOOL_HPP
#define SIMPLEUTILS_THREADPOOL_HPP

#include <simpleutils/Tasks/Task.hpp>

#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>

namespace simpleutils::Tasks
{
    class ThreadPool
    {
        public:
            explicit ThreadPool(std::size_t poolSize);
            ~ThreadPool();

            bool Submit(const Task& task);
            void Stop();

        private:
            void workerLoop();

        private:
            std::queue<Task> m_Tasks {};
            std::vector<std::thread> m_Workers {};
            std::mutex m_QueueMutex {};
            std::condition_variable m_Condition {};
            bool m_Stop {};
    };
} // namespace simpleutils::Tasks


#endif // SIMPLEUTILS_THREADPOOL_HPP