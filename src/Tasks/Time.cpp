#include <simpleutils/Tasks/Time.hpp>

#include <thread>

namespace simpleutils::Tasks
{
    Duration::Duration(int64_t value) :
        m_Value(value)
    {
    }

    Hours::Hours(int64_t value) :
        Duration(value)
    {
    }

    std::chrono::nanoseconds Hours::ToChrono() const
    {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::hours(m_Value));
    }

    Minutes::Minutes(int64_t value) :
        Duration(value)
    {
    }

    std::chrono::nanoseconds Minutes::ToChrono() const
    {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::minutes(m_Value));
    }

    Seconds::Seconds(int64_t value) :
        Duration(value)
    {
    }

    std::chrono::nanoseconds Seconds::ToChrono() const
    {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds(m_Value));
    }

    Milliseconds::Milliseconds(int64_t value) :
        Duration(value)
    {
    }

    std::chrono::nanoseconds Milliseconds::ToChrono() const
    {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(m_Value));
    }

    Microseconds::Microseconds(int64_t value) :
        Duration(value)
    {
    }

    std::chrono::nanoseconds Microseconds::ToChrono() const
    {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::microseconds(m_Value));
    }

    Nanoseconds::Nanoseconds(int64_t value) :
        Duration(value)
    {
    }

    std::chrono::nanoseconds Nanoseconds::ToChrono() const
    {
        return std::chrono::nanoseconds(m_Value);
    }

    void Sleep(const Duration& duration)
    {
        std::this_thread::sleep_for(duration.ToChrono());
    }
} // namespace simpleutils::Tasks
