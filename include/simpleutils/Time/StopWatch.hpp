#ifndef SIMPLEUTILS_STOPWATCH_HPP
#define SIMPLEUTILS_STOPWATCH_HPP

#include <simpleutils/Time/Time.hpp>

namespace simpleutils::Time
{
    class StopWatch
    {
        public:
            StopWatch() = default;
            ~StopWatch() = default;

            void Start();
            void Stop();
            void Restart();
            void Reset();

            bool IsRunning() const;
            Nanoseconds Elapsed() const;

        private:
            using Clock = std::chrono::steady_clock;

            Clock::time_point m_StartTime {};
            std::chrono::nanoseconds m_Elapsed {};
            bool m_IsRunning {};
    };
} // namespace simpleutils::Time


#endif // SIMPLEUTILS_STOPWATCH_HPP