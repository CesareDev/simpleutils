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

            TcpSocket(TcpSocket&& other) noexcept = default;
            TcpSocket& operator=(TcpSocket&& other) noexcept = default;

            bool Bind(const std::string& address, int port);
            bool Listen(int backlog = 10);
            TcpSocket Accept();
            bool Connect(const std::string& address, int port);

            bool Send(const Packet& packet) override;
            bool SendRaw(const void* data, std::size_t size) override;
            Packet Receive(const Time::Duration& timeout = Time::Milliseconds(0)) override;
            bool ReceiveRaw(void* buffer, std::size_t capacity, std::size_t& bytesReceived, const Time::Duration& timeout = Time::Milliseconds(0)) override;

            bool IsOpen() const;

        private:
            explicit TcpSocket(int fileDescriptor);
    };
    
} // namespace simpleutils::Net


#endif // SIMPLEUTILS_TCPSOCKET_HPP