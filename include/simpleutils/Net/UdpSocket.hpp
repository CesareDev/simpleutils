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

            bool Bind(const std::string& address, int port);
            bool SetDestination(const std::string& address, int port);

            bool Send(const Packet& packet) override;
            Packet Receive() override;

        private:
            Endpoint m_Destination {};
    };
    
} // namespace simpleutils::Net


#endif // SIMPLEUTILS_UDPSOCKET_HPP