#ifndef SIMPLEUTILS_SOCKET_HPP
#define SIMPLEUTILS_SOCKET_HPP

#include <cstddef>
#include <string>

namespace simpleutils::Net
{
    class Socket
    {
        public:
            Socket();
            virtual ~Socket();

            Socket(const Socket& socket) = delete;
            Socket& operator=(const Socket&) = delete;

            virtual std::size_t Send(const void* data, std::size_t size) = 0;
            virtual std::size_t Receive(void* buffer, std::size_t capacity) = 0;

        protected:
            bool resolveIp(const std::string& address, int port);
            bool resolveHostname(const std::string& address, int port);
            bool resolveInterface(const std::string& address, int port);

        protected:
            int m_FileDescriptor { -1 };
    };
} // namespace simpleutils::Net


#endif // SIMPLEUTILS_SOCKET_HPP