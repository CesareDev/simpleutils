#include <simpleutils/Threading/Thread.hpp>

#include <system_error>

namespace simpleutils::Threading
{
    using Common::ErrorCode;
    using Common::ReturnCode;

    Thread::~Thread()
    {
        Join();
    }

    ReturnCode Thread::Start(const Callback& callback)
    {
        if (!callback)
            return ErrorCode::InvalidArgument;

        if (m_Thread.joinable() || !callback)
            return ErrorCode::ThreadAlreadyRunning;

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
            return ErrorCode::ThreadCreationFailed;
        }

        return ErrorCode::None;
    }

    ReturnCode Thread::Start(Runnable& runnable)
    {
        return Start([&runnable] { runnable.Run(); });
    }

    ReturnCode Thread::Join()
    {
        if (!m_Thread.joinable())
            return ErrorCode::ThreadNotRunning;

        if (m_Thread.get_id() == std::this_thread::get_id())
            return ErrorCode::InvalidState;

        try
        {
            m_Thread.join();
        }
        catch(const std::system_error& e)
        {
            return ErrorCode::Unknown;
        }

        return ErrorCode::None;
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
