#ifndef SIMPLEUTILS_UDPSOCKET_HPP
#define SIMPLEUTILS_UDPSOCKET_HPP

#include <simpleutils/Net/Socket.hpp>

#include <string>

namespace simpleutils::Net
{
    class UdpSocket : public Socket
    {
        public:
            UdpSocket() = default;
            ~UdpSocket() override = default;

            UdpSocket(UdpSocket&& other) noexcept = default;
            UdpSocket& operator=(UdpSocket&& other) noexcept = default;

            bool Bind(const std::string& address, int port);
            bool SetDestination(const std::string& address, int port);

            bool Send(const Packet& packet) override;
            bool SendRaw(const void* data, std::size_t size) override;
            Packet Receive(const Time::Duration& timeout = Time::Milliseconds(0)) override;
            bool ReceiveRaw(void* buffer, std::size_t capacity, std::size_t& bytesReceived, const Time::Duration& timeout = Time::Milliseconds(0)) override;

        private:
            Endpoint m_Destination {};
    };
    
} // namespace simpleutils::Net


#endif // SIMPLEUTILS_UDPSOCKET_HPP