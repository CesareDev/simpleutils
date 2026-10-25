#ifndef SIMPLEUTILS_TCPSOCKET_HPP
#define SIMPLEUTILS_TCPSOCKET_HPP

#include <simpleutils/Net/Socket.hpp>

#include <string>

namespace simpleutils::Net
{
    class TcpSocket : public Socket
    {
        public:
            bool Connect(const std::string& address, int port);
            std::size_t Send(const void* data, std::size_t size) override;
            std::size_t Receive(void* buffer, std::size_t capacity) override;
    };
    
} // namespace simpleutils::Net


#endif // SIMPLEUTILS_TCPSOCKET_HPP