#include <simpleutils/Threading/Thread.hpp>

#include <system_error>

namespace simpleutils::Threading
{
    Thread::~Thread()
    {
        Join();
    }

    bool Thread::Start(const Callback& callback)
    {
        if (m_Thread.joinable() || !callback)
            return false;

        m_IsRunning = true;

        try
        {
            m_Thread = std::thread([this, callback]()
            {
                callback();
                m_IsRunning = false;
            });
        }
        catch (...)
        {
            m_IsRunning = false;
            return false;
        }

        return true;
    }

    bool Thread::Start(Runnable& runnable)
    {
        return Start([&runnable] { runnable.Run(); });
    }

    void Thread::Join()
    {
        if (m_Thread.joinable())
            m_Thread.join();
    }

    bool Thread::IsRunning() const
    {
        return m_IsRunning;
    }

    bool Thread::IsJoinable() const
    {
        return m_Thread.joinable();
    }
} // namespace simpleutils::Threading
