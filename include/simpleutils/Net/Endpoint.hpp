#ifndef SIMPLEUTILS_ENDPOINT_HPP
#define SIMPLEUTILS_ENDPOINT_HPP

#include <sys/socket.h>

#include <cstdint>
#include <string>

namespace simpleutils::Net
{
    struct Endpoint
    {
        sockaddr_storage addr {};
        socklen_t addrLength {};
        bool isValid {};

        std::uint16_t GetPort() const;
        std::string GetAddress() const;
    };
    
} // namespace simpleutils::Net


#endif // SIMPLEUTILS_ENDPOINT_HPP