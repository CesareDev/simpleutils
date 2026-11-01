#ifndef SIMPLEUTILS_TCPSOCKET_HPP
#define SIMPLEUTILS_TCPSOCKET_HPP

#include <simpleutils/Net/Socket.hpp>

#include <string>

namespace simpleutils::Net
{
    class TcpSocket : public Socket
    {
        public:
            TcpSocket() = default;
            ~TcpSocket() override = default;

            bool Bind(const std::string& address, int port);
            bool Listen(int backlog = 10);
            TcpSocket Accept();
            bool Connect(const std::string& address, int port);

            bool Send(const Packet& packet) override;
            Packet Receive() override;

            bool IsOpen() const;

        private:
            explicit TcpSocket(int fileDescriptor);
    };
    
} // namespace simpleutils::Net


#endif // SIMPLEUTILS_TCPSOCKET_HPP