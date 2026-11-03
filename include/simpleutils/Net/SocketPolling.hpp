
#ifndef SIMPLEUTILS_SOCKETPOLLING_HPP
#define SIMPLEUTILS_SOCKETPOLLING_HPP

#include <simpleutils/Net/Socket.hpp>
#include <simpleutils/Tasks/Task.hpp>
#include <simpleutils/Time/Time.hpp>

#include <unordered_map>
#include <cstdint>

namespace simpleutils::Net
{
    class SocketPolling
    {
        public:
            SocketPolling();
            ~SocketPolling();

            SocketPolling(const SocketPolling&) = delete;
            SocketPolling& operator=(const SocketPolling&) = delete;

            bool IsValid() const;

            bool Add(Socket& socket);
            bool Remove(Socket& socket);

            int Process(const Tasks::PollingTask& callback);
            int Process(const Time::Duration& timeout, const Tasks::PollingTask& callback);

        private:
            int processInternal(int timeoutMs, const Tasks::PollingTask& callback);

        private:
            int m_EpollDescriptor { -1 };
            std::unordered_map<int, Socket*> m_Sockets {};
            std::uint64_t m_NextRegistrationId {};
            std::unordered_map<std::uint64_t, int> m_Registrations {};
    };

} // namespace simpleutils::Net

#endif // SIMPLEUTILS_SOCKETPOLLING_HPP
