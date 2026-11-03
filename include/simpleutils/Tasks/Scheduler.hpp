#ifndef SIMPLEUTILS_SCHEDULER_HPP
#define SIMPLEUTILS_SCHEDULER_HPP

#include <simpleutils/Time/Time.hpp>
#include <simpleutils/Threading/Thread.hpp>

#include <atomic>
#include <condition_variable>

namespace simpleutils::Tasks
{
    class Scheduler
    {
        public:
            using Callback = std::function<void()>;

        public:
            Scheduler() = default;
            ~Scheduler();

            void Start(const Callback& task, const Time::Duration& interval);
            void StartFor(const Callback& task, const Time::Duration& interval, std::uint32_t repetition);
            void Stop();

        private:
            Threading::Thread m_Thread {};
            std::atomic<bool> m_IsRunning {};
            std::mutex m_ConditionVarMutex {};
            std::condition_variable m_ConditionVar {};
    };
} // namespace simpleutils

#endif