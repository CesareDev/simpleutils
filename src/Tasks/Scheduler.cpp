#include <simpleutils/Tasks/Scheduler.hpp>

namespace simpleutils::Tasks
{
    Scheduler::Scheduler()
    {
    }
    
    Scheduler::~Scheduler()
    {
        Stop();
    }
    
    void Scheduler::Start(const Task& task, const Duration& interval)
    {
        if (m_IsRunnig) return;

        m_IsRunnig = true;
        
        m_Thread = std::thread([this, task, intervalValue = interval.ToChrono()]() {
            while (m_IsRunnig)
            {
                std::unique_lock<std::mutex> lock(m_ConditionVarMutex);
                task();
                m_ConditionVar.wait_for(lock, intervalValue, [this] { return !m_IsRunnig; });
            }
        });
    }

    void Scheduler::StartFor(const Task& task, const Duration& interval, uint32_t repetition)
    {
        if (m_IsRunnig) return;

        m_IsRunnig = true;
        
        m_Thread = std::thread([this, task, intervalValue = interval.ToChrono(), repetition]() {
            for (uint32_t rep {}; rep < repetition && m_IsRunnig; ++rep)
            {
                std::unique_lock<std::mutex> lock(m_ConditionVarMutex);
                
                task();

                m_ConditionVar.wait_for(lock, intervalValue, [this] { return !m_IsRunnig; });
            }
        });
    }
    
    void Scheduler::Stop()
    {
        m_IsRunnig = false;

        m_ConditionVar.notify_all();

        if (m_Thread.joinable())
        {
            m_Thread.join();
        }
    }
} // simpleutils::Tasks