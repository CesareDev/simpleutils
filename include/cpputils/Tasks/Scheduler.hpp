#ifndef SIMPLEUTILS_SCHEDULER_HPP
#define SIMPLEUTILS_SCHEDULER_HPP

#include <simpleutils/Tasks/Time.hpp>

#include <thread>
#include <functional>
#include <atomic>
#include <condition_variable>

namespace simpleutils::Tasks
{
    typedef std::function<void()> Task;

    class Scheduler
    {
        public:
            Scheduler();
            ~Scheduler();

            void Start(const Task& task, const Duration& interval);
            void Stop();

        private:
            std::thread m_Thread {};
            std::atomic<bool> m_IsRunnig {};
            std::mutex m_ConditionVarMutex {};
            std::condition_variable m_ConditionVar {};
    };
} // namespace simpleutils

#endif