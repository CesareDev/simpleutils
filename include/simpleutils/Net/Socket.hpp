#ifndef SIMPLEUTILS_SOCKET_HPP
#define SIMPLEUTILS_SOCKET_HPP

#include <simpleutils/Net/Endpoint.hpp>
#include <simpleutils/Net/Packet.hpp>
#include <simpleutils/Time/Time.hpp>

#include <cstddef>
#include <string>

namespace simpleutils::Net
{
    class Socket
    {
        public:
            Socket() = default;
            virtual ~Socket();

            Socket(const Socket& socket) = delete;
            Socket& operator=(const Socket&) = delete;

            Socket(Socket&& other) noexcept;
            Socket& operator=(Socket&& other) noexcept;

            virtual bool Send(const Packet& packet) = 0;
            virtual Packet Receive(const Time::Duration& timeout) = 0;
            virtual Packet Receive() = 0;

            Endpoint GetLocalEndpoint() const;
            int GetFileDescriptor() const;
            bool SetReceiveTimeout(const Time::Duration& timeout);

        protected:
            Endpoint resolve(const std::string& address, int port);

        private:
            Endpoint resolveIp(const std::string& address, int port);
            Endpoint resolveHostname(const std::string& address, int port);
            Endpoint resolveInterface(const std::string& address, int port);

        protected:
            int m_FileDescriptor { -1 };
    };
} // namespace simpleutils::Net


#endif // SIMPLEUTILS_SOCKET_HPP