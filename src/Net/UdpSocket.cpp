#include <simpleutils/Net/UdpSocket.hpp>

#include <unistd.h>

namespace simpleutils::Net
{
    bool UdpSocket::Bind(const std::string& address, int port)
    {
        if (m_FileDescriptor >= 0)
            return false;

        Endpoint endpoint = resolve(address, port);

        if (!endpoint.isValid)
            return false;

        m_FileDescriptor = ::socket(
            endpoint.addr.ss_family,
            SOCK_DGRAM,
            0
        );

        if (m_FileDescriptor < 0)
            return false;

        if (::bind(m_FileDescriptor, reinterpret_cast<const sockaddr*>(&endpoint.addr), endpoint.addrLength) < 0)
        {
            ::close(m_FileDescriptor);
            m_FileDescriptor = -1;
            return false;
        }

        return true;
    }

    bool UdpSocket::SetDestination(const std::string& address, int port)
    {
        if (port == 0)
            return false;

        Endpoint endpoint = resolve(address, port);

        if (!endpoint.isValid)
            return false;

        // An existing socket must use a compatible address family.
        if (m_FileDescriptor >= 0)
        {
            Endpoint local = GetLocalEndpoint();

            if (!local.isValid ||
                local.addr.ss_family != endpoint.addr.ss_family)
                return false;
        }

        m_Destination = endpoint;
        return true;
    }

    bool UdpSocket::Send(const Packet& packet)
    {
        if (!m_Destination.isValid)
            return false;

        // Create the socket if it doesn't exist.
        if (m_FileDescriptor < 0)
        {
            m_FileDescriptor = ::socket(
                m_Destination.addr.ss_family,
                SOCK_DGRAM,
                0
            );

            if (m_FileDescriptor < 0)
                return false;
        }

        const Buffer& payload = packet.GetBuffer();
        ssize_t sent {};

        do
        {
            sent = ::sendto(
                m_FileDescriptor,
                payload.GetData(),
                payload.Remaining(),
                0,
                reinterpret_cast<const sockaddr*>(&m_Destination.addr),
                m_Destination.addrLength
            );
        }
        while (sent < 0 && errno == EINTR);

        return sent >= 0 && static_cast<std::size_t>(sent) == payload.Remaining();
    }

    Packet UdpSocket::Receive()
    {
        Packet packet {};

        if (m_FileDescriptor < 0)
            return packet;

        std::byte data[65536] {};
        ssize_t received {};

        do
        {
            received = ::recvfrom(
                m_FileDescriptor,
                data,
                sizeof(data),
                MSG_TRUNC,
                nullptr,
                nullptr
            );
        }
        while (received < 0 && errno == EINTR);

        if (received < 0)
            return packet;

        // MSG_TRUNC allows Linux to report the full datagram length.
        // Reject a datagram that cannot fit in our buffer.
        if (static_cast<std::size_t>(received) > sizeof(data))
            return packet;

        if (!packet.GetBuffer().Write(data, static_cast<std::size_t>(received)))
        {
            return packet;
        }

        packet.m_IsValid = true;
        return packet;
    }
} // namespace simpleutils::Net
