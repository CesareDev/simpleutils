
#include <simpleutils/Net/SocketPolling.hpp>

#include <sys/epoll.h>
#include <unistd.h>

#include <array>
#include <chrono>
#include <climits>
#include <limits>

namespace simpleutils::Net
{
    SocketPolling::SocketPolling()
    {
        m_EpollDescriptor = ::epoll_create1(EPOLL_CLOEXEC);
    }

    SocketPolling::~SocketPolling()
    {
        if (m_EpollDescriptor >= 0)
            ::close(m_EpollDescriptor);
    }

    bool SocketPolling::IsValid() const
    {
        return m_EpollDescriptor >= 0;
    }

    bool SocketPolling::Add(Socket& socket)
    {
        if (!IsValid())
            return false;

        int descriptor = socket.GetFileDescriptor();

        if (descriptor < 0)
            return false;

        if (m_Sockets.find(descriptor) != m_Sockets.end())
            return false;

        if (m_NextRegistrationId == std::numeric_limits<std::uint64_t>::max())
            return false;

        std::uint64_t registrationId = ++m_NextRegistrationId;

        epoll_event event {};
        event.events = EPOLLIN | EPOLLRDHUP | EPOLLONESHOT;
        event.data.u64 = registrationId;

        m_Sockets.emplace(descriptor, &socket);
        m_Registrations.emplace(registrationId, descriptor);

        if (::epoll_ctl(
                m_EpollDescriptor,
                EPOLL_CTL_ADD,
                descriptor,
                &event) < 0)
        {
            m_Registrations.erase(registrationId);
            m_Sockets.erase(descriptor);
            return false;
        }

        return true;
    }

    bool SocketPolling::Remove(Socket& socket)
    {
        if (!IsValid())
            return false;

        int descriptor = socket.GetFileDescriptor();

        auto it = m_Sockets.find(descriptor);

        if (it == m_Sockets.end() || it->second != &socket)
            return false;

        if (::epoll_ctl(
                m_EpollDescriptor,
                EPOLL_CTL_DEL,
                descriptor,
                nullptr) < 0)
        {
            return false;
        }

        for (auto registration = m_Registrations.begin(); registration != m_Registrations.end(); ++registration)
        {
            if (registration->second == descriptor)
            {
                m_Registrations.erase(registration);
                break;
            }
        }

        m_Sockets.erase(it);
        return true;
    }

    int SocketPolling::Process(const Callback& callback)
    {
        return processInternal(-1, callback);
    }

    int SocketPolling::Process(const Time::Duration& timeout, const Callback& callback)
    {
        auto nanoseconds = timeout.ToChrono();

        if (nanoseconds.count() < 0)
            return -1;

        // Round positive durations up to whole milliseconds.
        constexpr std::int64_t NS_PER_MS = 1000000;

        std::int64_t timeoutMs = nanoseconds.count() / NS_PER_MS;

        if (nanoseconds.count() % NS_PER_MS != 0)
            ++timeoutMs;

        if (timeoutMs > INT_MAX)
            return -1;

        return processInternal(static_cast<int>(timeoutMs), callback);
    }

    int SocketPolling::processInternal(int timeoutMs, const Callback& callback)
    {
        if (!IsValid() || !callback)
            return -1;

        constexpr int MAX_EVENTS = 64;

        std::array<epoll_event, MAX_EVENTS> events {};

        int ready = ::epoll_wait(
            m_EpollDescriptor,
            events.data(),
            MAX_EVENTS,
            timeoutMs
        );

        if (ready <= 0)
            return ready;

        int processed {};

        for (int i = 0; i < ready; ++i)
        {
            std::uint64_t registrationId = events[i].data.u64;

            auto registration = m_Registrations.find(registrationId);

            if (registration == m_Registrations.end())
                continue;

            int descriptor = registration->second;

            auto it = m_Sockets.find(descriptor);

            if (it == m_Sockets.end())
                continue;

            Socket* socket = it->second;

            // The callback handles the ready socket.
            try
            {
                callback(*socket);
            }
            catch (...)
            {
                // Rearm before propagating the exception,
                // provided the socket is still registered.
                if (m_Registrations.find(registrationId) != m_Registrations.end())
                {
                    epoll_event event {};
                    event.events = EPOLLIN | EPOLLRDHUP | EPOLLONESHOT;
                    event.data.u64 = registrationId;

                    ::epoll_ctl(
                        m_EpollDescriptor,
                        EPOLL_CTL_MOD,
                        descriptor,
                        &event
                    );
                }

                throw;
            }

            ++processed;

            // The callback may have removed the socket.
            if (m_Registrations.find(registrationId) == m_Registrations.end())
            {
                continue;
            }

            // Automatically rearm it for the next notification.
            epoll_event event {};
            event.events = EPOLLIN | EPOLLRDHUP | EPOLLONESHOT;
            event.data.u64 = registrationId;

            if (::epoll_ctl(
                    m_EpollDescriptor,
                    EPOLL_CTL_MOD,
                    descriptor,
                    &event) < 0)
            {
                return -1;
            }
        }

        return processed;
    }

} // namespace simpleutils::Net
