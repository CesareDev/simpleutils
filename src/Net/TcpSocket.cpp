#include <simpleutils/Net/TcpSocket.hpp>

#include <simpleutils/Net/Endpoint.hpp>

#include <sys/socket.h>
#include <unistd.h>

namespace simpleutils::Net
{
    TcpSocket::TcpSocket(int fileDescriptor)
    {
        m_FileDescriptor = fileDescriptor;
    }

    bool TcpSocket::Bind(const std::string& address, int port)
    {
        if (m_FileDescriptor >= 0)
            return false;

        Endpoint endpoint = resolve(address, port);

        if (!endpoint.isValid)
            return false;

        m_FileDescriptor = ::socket(
            endpoint.addr.ss_family,
            SOCK_STREAM,
            0
        );

        if (m_FileDescriptor < 0)
            return false;

        // Allow quicker reuse of a local listening address.
        int reuseAddress = 1;

        if (::setsockopt(
                m_FileDescriptor,
                SOL_SOCKET,
                SO_REUSEADDR,
                &reuseAddress,
                sizeof(reuseAddress)) < 0)
        {
            ::close(m_FileDescriptor);
            m_FileDescriptor = -1;
            return false;
        }

        if (::bind(m_FileDescriptor, reinterpret_cast<const sockaddr*>(&endpoint.addr), endpoint.addrLength) < 0)
        {
            ::close(m_FileDescriptor);
            m_FileDescriptor = -1;
            return false;
        }

        return true;
    }

    bool TcpSocket::Listen(int backlog)
    {
        if (m_FileDescriptor < 0 || backlog < 0)
            return false;

        return ::listen(m_FileDescriptor, backlog) == 0;
    }

    TcpSocket TcpSocket::Accept()
    {
        if (m_FileDescriptor < 0)
            return TcpSocket {};

        int clientDescriptor;

        do
        {
            clientDescriptor = ::accept(
                m_FileDescriptor,
                nullptr,
                nullptr
            );
        }
        while (clientDescriptor < 0 && errno == EINTR);

        if (clientDescriptor < 0)
            return TcpSocket {};

        return TcpSocket(clientDescriptor);
    }

    bool TcpSocket::Connect(const std::string& address, int port)
    {
        if (port == 0)
            return false;

        if (m_FileDescriptor >= 0)
            return false;

        Endpoint endpoint = resolve(address, port);

        if (!endpoint.isValid)
            return false;

        m_FileDescriptor = ::socket(endpoint.addr.ss_family, SOCK_STREAM, 0);
        if (m_FileDescriptor < 0)
            return false;
        
        int connRes = ::connect(m_FileDescriptor, reinterpret_cast<sockaddr*>(&endpoint.addr), endpoint.addrLength);
        if (connRes < 0)
        {
            ::close(m_FileDescriptor);
            m_FileDescriptor = -1;
            return false;
        }

        return true;
    }

    bool TcpSocket::Send(const Packet& packet)
    {
        if (m_FileDescriptor < 0)
            return false;

        const Buffer& payload = packet.GetBuffer();

        if (payload.Remaining() > UINT32_MAX)
            return false;

        Buffer buffer {};

        if (!buffer.Write(static_cast<std::uint32_t>(payload.Remaining())))
            return false;

        if (!buffer.Append(payload))
            return false;

        const std::byte* data = static_cast<const std::byte*>(buffer.GetData());

        std::size_t totalSent {};
        const std::size_t bufferSize = buffer.Remaining();

        while (totalSent < bufferSize)
        {
            auto sent = ::send(
                m_FileDescriptor,
                data + totalSent,
                bufferSize - totalSent,
                MSG_NOSIGNAL
            );

            if (sent < 0)
            {
                if (errno == EINTR)
                    continue;

                return false;
            }
            else if (sent == 0)
            {
                return false;
            }

            totalSent += static_cast<std::size_t>(sent);
        }

        return true;
    }

    Packet TcpSocket::Receive()
    {
        Packet packet {};

        if (m_FileDescriptor < 0)
            return packet;

        // Receive the 4-byte size header.
        std::uint32_t networkSize {};
        std::size_t totalReceived {};

        while (totalReceived < sizeof(networkSize))
        {
            ssize_t received = ::recv(
                m_FileDescriptor,
                reinterpret_cast<std::byte*>(&networkSize) + totalReceived,
                sizeof(networkSize) - totalReceived,
                0
            );

            if (received < 0)
            {
                if (errno == EINTR)
                    continue;

                return packet;
            }
            else if (received == 0)
            {
                return packet;
            }

            totalReceived += static_cast<std::size_t>(received);
        }

        // Deserialize the size through our Buffer class.
        Buffer header {};

        if (!header.Write(&networkSize, sizeof(networkSize)))
            return packet;

        std::uint32_t payloadSize {};

        if (!header.Read(payloadSize))
            return packet;

        // Reject packets that are too large.
        constexpr std::uint32_t MAX_PACKET_SIZE = 16 * 1024 * 1024;

        if (payloadSize > MAX_PACKET_SIZE)
            return packet;

        // Receive the payload.
        std::byte data[4096] {};
        std::size_t totalPayload {};

        while (totalPayload < payloadSize)
        {
            std::size_t toReceive = std::min(
                sizeof(data),
                static_cast<std::size_t>(payloadSize) - totalPayload
            );

            ssize_t received = ::recv(
                m_FileDescriptor,
                data,
                toReceive,
                0
            );

            if (received < 0)
            {
                if (errno == EINTR)
                    continue;

                return packet;
            }
            else if (received == 0)
            {
                return packet;
            }

            if (!packet.GetBuffer().Write(data, static_cast<std::size_t>(received)))
            {
                return packet;
            }

            totalPayload += static_cast<std::size_t>(received);
        }

        packet.m_IsValid = true;
        return packet;
    }

    bool TcpSocket::IsOpen() const
    {
        return m_FileDescriptor >= 0;
    }
} // namespace simpleutils::Net
