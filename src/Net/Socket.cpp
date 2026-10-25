#include <simpleutils/Net/Socket.hpp>

#include <unistd.h>

namespace simpleutils::Net
{
    Socket::Socket()
    {
    }

    Socket::~Socket()
    {
        if (m_FileDescriptor >= 0)
            close(m_FileDescriptor);            
    }

    bool Socket::resolveIp(const std::string& address, int port)
    {
        return true;
    }

    bool Socket::resolveHostname(const std::string& address, int port)
    {
        return true;
    }

    bool Socket::resolveInterface(const std::string& address, int port)
    {
        return true;
    }
} // namespace simpleutils::Net
