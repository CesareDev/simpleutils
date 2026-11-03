
#include <simpleutils/Tasks/Scheduler.hpp>

namespace simpleutils::Tasks
{
    Scheduler::~Scheduler()
    {
        Stop();
    }

    void Scheduler::Start(const Callback& task, const Time::Duration& interval)
    {
        if (m_IsRunning || !task)
            return;

        // Join a previous execution if it has finished.
        if (m_Thread.IsJoinable())
            m_Thread.Join();

        auto intervalValue = interval.ToChrono();

        if (intervalValue.count() < 0)
            return;

        m_IsRunning = true;

        bool threadStart = m_Thread.Start([this, task, intervalValue]() {
            while (m_IsRunning)
            {
                task();
    
                std::unique_lock<std::mutex> lock(m_ConditionVarMutex);
    
                m_ConditionVar.wait_for(lock, intervalValue, [this]() {
                    return !m_IsRunning;
                });
            }
    
            m_IsRunning = false;
        });

        if (!threadStart)
        {
            m_IsRunning = false;
        }
    }

    void Scheduler::StartFor(const Callback& task, const Time::Duration& interval, std::uint32_t repetition)
    {
        if (m_IsRunning || !task || repetition == 0)
            return;

        if (m_Thread.IsJoinable())
            m_Thread.Join();

        auto intervalValue = interval.ToChrono();

        if (intervalValue.count() < 0)
            return;

        m_IsRunning = true;

        bool threadStart = m_Thread.Start([this, task, intervalValue, repetition]() {
            for (std::uint32_t i {}; i < repetition && m_IsRunning; ++i)
            {
                task();

                // No need to wait after the final execution.
                if (i + 1 == repetition)
                    break;

                std::unique_lock<std::mutex> lock(m_ConditionVarMutex);

                m_ConditionVar.wait_for(lock, intervalValue, [this]() {
                    return !m_IsRunning;
                });
            }

            m_IsRunning = false;
        });

        if (!threadStart)
        {
            m_IsRunning = false;
        }
    }

    void Scheduler::Stop()
    {
        m_IsRunning = false;
        m_ConditionVar.notify_all();
        m_Thread.Join();
    }
}
