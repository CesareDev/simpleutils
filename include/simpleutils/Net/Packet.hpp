#ifndef SIMPLEUTILS_PACKET_HPP
#define SIMPLEUTILS_PACKET_HPP

#include <simpleutils/Net/Buffer.hpp>

namespace simpleutils::Net
{
    class Packet
    {
        public:
            Packet();
            ~Packet();

            bool IsValid() const;
            Buffer& GetBuffer();
            const Buffer& GetBuffer() const;
            void Clear();

        private:
            Buffer m_Buffer {};
            bool m_IsValid {};

            friend class TcpSocket;
            friend class UdpSocket;
    };
} // namespace simpleutils::Net


#endif // SIMPLEUTILS_PACKET_HPP