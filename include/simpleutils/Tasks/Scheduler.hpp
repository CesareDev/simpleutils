#ifndef SIMPLEUTILS_SCHEDULER_HPP
#define SIMPLEUTILS_SCHEDULER_HPP

#include <simpleutils/Tasks/Task.hpp>
#include <simpleutils/Tasks/Time.hpp>

#include <thread>
#include <functional>
#include <atomic>
#include <condition_variable>

namespace simpleutils::Tasks
{
    class Scheduler
    {
        public:
            Scheduler();
            ~Scheduler();

            void Start(const Task& task, const Duration& interval);
            void StartFor(const Task& task, const Duration& interval, std::uint32_t repetition);
            void Stop();

        private:
            std::thread m_Thread {};
            std::atomic<bool> m_IsRunnig {};
            std::mutex m_ConditionVarMutex {};
            std::condition_variable m_ConditionVar {};
    };
} // namespace simpleutils

#endif