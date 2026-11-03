#ifndef SIMPLEUTILS_SCHEDULER_HPP
#define SIMPLEUTILS_SCHEDULER_HPP

#include <simpleutils/Time/Time.hpp>

#include <thread>
#include <functional>
#include <atomic>
#include <condition_variable>

namespace simpleutils::Tasks
{
    using Callback = std::function<void()>;

    class Scheduler
    {
        public:
            Scheduler();
            ~Scheduler();

            void Start(const Callback& task, const Time::Duration& interval);
            void StartFor(const Callback& task, const Time::Duration& interval, std::uint32_t repetition);
            void Stop();

        private:
            std::thread m_Thread {};
            std::atomic<bool> m_IsRunnig {};
            std::mutex m_ConditionVarMutex {};
            std::condition_variable m_ConditionVar {};
    };
} // namespace simpleutils

#endif