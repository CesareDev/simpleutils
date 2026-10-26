#include <simpleutils/Net/Socket.hpp>

#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <stdexcept>
#include <ifaddrs.h>
#include <netdb.h>

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

    Endpoint Socket::resolve(const std::string& address, int port)
    {
        if (port <= 0 || port > 65535)
            return {};

        Endpoint endpoint = resolveIp(address, port);

        if (endpoint.isValid)
            return endpoint;

        endpoint = resolveInterface(address, port);

        if (endpoint.isValid)
            return endpoint;

        endpoint = resolveHostname(address, port);

        if (endpoint.isValid)
            return endpoint;

        return {};
    }

    Endpoint Socket::resolveIp(const std::string& address, int port)
    {
        Endpoint endpoint {};

        sockaddr_in ipv4 {};

        // Try IPv4
        if (inet_pton(AF_INET, address.c_str(), &ipv4.sin_addr) == 1)
        {
            ipv4.sin_family = AF_INET;
            ipv4.sin_port = htons(port);

            std::memcpy(&endpoint.addr, &ipv4, sizeof(ipv4));
            endpoint.addrLength = sizeof(ipv4);
            endpoint.isValid = true;
            return endpoint;
        }

        sockaddr_in6 ipv6 {};

        // Try IPv6
        if (inet_pton(AF_INET6, address.c_str(), &ipv6.sin6_addr) == 1)
        {
            ipv6.sin6_family = AF_INET6;
            ipv6.sin6_port = htons(port);

            std::memcpy(&endpoint.addr, &ipv6, sizeof(ipv6));
            endpoint.addrLength = sizeof(ipv6);
            endpoint.isValid = true;
            return endpoint;
        }

        return endpoint;
    }

    Endpoint Socket::resolveHostname(const std::string& address, int port)
    {
        Endpoint endpoint {};

        addrinfo hints {};
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = 0;

        addrinfo* results = nullptr;

        int result = getaddrinfo(
            address.c_str(),
            std::to_string(port).c_str(),
            &hints,
            &results
        );

        if (result != 0)
            return endpoint;

        for (addrinfo* current = results; current != nullptr; current = current->ai_next)
        {
            if (current->ai_addr == nullptr)
                continue;

            if (current->ai_family != AF_INET && current->ai_family != AF_INET6)
                continue;

            if (current->ai_addrlen > sizeof(endpoint.addr))
                continue;

            std::memcpy(
                &endpoint.addr,
                current->ai_addr,
                current->ai_addrlen
            );

            endpoint.addrLength = current->ai_addrlen;
            endpoint.isValid = true;

            break;
        }

        freeaddrinfo(results);

        return endpoint;;
    }

    Endpoint Socket::resolveInterface(const std::string& address, int port)
    {
        Endpoint endpoint {};

        ifaddrs* interfaces = nullptr;

        if (getifaddrs(&interfaces) != 0)
            return endpoint;

        for (ifaddrs* current = interfaces; current != nullptr; current = current->ifa_next)
        {
            if (current->ifa_addr == nullptr)
                continue;

            if (address != current->ifa_name)
                continue;

            if (current->ifa_addr->sa_family == AF_INET)
            {
                sockaddr_in ipv4 = *reinterpret_cast<sockaddr_in*>(current->ifa_addr);

                ipv4.sin_port = htons(port);

                std::memcpy(&endpoint.addr, &ipv4, sizeof(ipv4));
                endpoint.addrLength = sizeof(ipv4);
                endpoint.isValid = true;
                break;
            }
            else if (current->ifa_addr->sa_family == AF_INET6)
            {
                sockaddr_in6 ipv6 = *reinterpret_cast<sockaddr_in6*>(current->ifa_addr);

                ipv6.sin6_port = htons(port);

                std::memcpy(&endpoint.addr, &ipv6, sizeof(ipv6));
                endpoint.addrLength = sizeof(ipv6);
                endpoint.isValid = true;
                break;
            }
        }

        freeifaddrs(interfaces);
        return endpoint;
    }
} // namespace simpleutils::Net
