#include <simpleutils/Net/TcpSocket.hpp>

#include <simpleutils/Net/Endpoint.hpp>

#include <sys/socket.h>
#include <unistd.h>

namespace simpleutils::Net
{
    bool TcpSocket::Connect(const std::string& address, int port)
    {
        if (m_FileDescriptor >= 0)
            return false;

        Endpoint endpoint = resolve(address, port);

        m_FileDescriptor = socket(endpoint.addr.ss_family, SOCK_STREAM, 0);
        if (m_FileDescriptor < 0)
            return false;
        
        int connRes = connect(m_FileDescriptor, reinterpret_cast<sockaddr*>(&endpoint.addr), endpoint.addrLength);
        if (connRes < 0)
        {
            close(m_FileDescriptor);
            m_FileDescriptor = -1;
            return false;
        }

        return true;
    }

    std::size_t TcpSocket::Send(const void* data, std::size_t size)
    {
    }

    std::size_t TcpSocket::Receive(void* buffer, std::size_t capacity)
    {
    }
} // namespace simpleutils::Net
