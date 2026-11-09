#include <simpleutils/Time/StopWatch.hpp>

namespace simpleutils::Time
{
    void StopWatch::Start()
    {
        if (m_IsRunning)
            return;

        m_StartTime = Clock::now();
        m_IsRunning = true;
    }

    void StopWatch::Stop()
    {
        if (!m_IsRunning)
            return;

        m_Elapsed += Clock::now() - m_StartTime;
        m_IsRunning = false;
    }

    void StopWatch::Restart()
    {
        m_Elapsed = std::chrono::nanoseconds {};
        m_StartTime = Clock::now();
        m_IsRunning = true;
    }

    void StopWatch::Reset()
    {
        m_IsRunning = false;
        m_StartTime = Clock::time_point();
        m_Elapsed = std::chrono::nanoseconds(0);
    }

    bool StopWatch::IsRunning() const
    {
        return m_IsRunning;
    }

    Nanoseconds StopWatch::Elapsed() const
    {
        std::chrono::nanoseconds elapsed = m_Elapsed;

        if (m_IsRunning)
        {
            elapsed += Clock::now() - m_StartTime;
        }

        return Nanoseconds(elapsed.count());
    }
} // namespace simpleutils::Time
