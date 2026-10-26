#ifndef SIMPLEUTILS_ENDPOINT_HPP
#define SIMPLEUTILS_ENDPOINT_HPP

#include <sys/socket.h>

namespace simpleutils::Net
{
    struct Endpoint
    {
        sockaddr_storage addr {};
        socklen_t addrLength {};
        bool isValid {};
    };
    
} // namespace simpleutils::Net


#endif // SIMPLEUTILS_ENDPOINT_HPP