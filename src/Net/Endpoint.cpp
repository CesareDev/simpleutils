#include <simpleutils/Net/Endpoint.hpp>

#include <arpa/inet.h>

namespace simpleutils::Net
{
    std::uint16_t Endpoint::GetPort() const
    {
        if (!isValid)
                return 0;

        if (addr.ss_family == AF_INET)
        {
            const auto* ipv4 =
                reinterpret_cast<const sockaddr_in*>(&addr);

            return ntohs(ipv4->sin_port);
        }

        if (addr.ss_family == AF_INET6)
        {
            const auto* ipv6 =
                reinterpret_cast<const sockaddr_in6*>(&addr);

            return ntohs(ipv6->sin6_port);
        }

        return 0;
    }

    std::string Endpoint::GetAddress() const
    {
        if (!isValid)
            return "";

        char buffer[INET6_ADDRSTRLEN] {};

        if (addr.ss_family == AF_INET)
        {
            const auto* ipv4 =
                reinterpret_cast<const sockaddr_in*>(&addr);

            if (inet_ntop(AF_INET, &ipv4->sin_addr, buffer, sizeof(buffer)) == nullptr)
                return "";
        }
        else if (addr.ss_family == AF_INET6)
        {
            const auto* ipv6 =
                reinterpret_cast<const sockaddr_in6*>(&addr);

            if (inet_ntop(AF_INET6, &ipv6->sin6_addr, buffer, sizeof(buffer)) == nullptr)
                return "";
        }
        else
        {
            return "";
        }

        return std::string(buffer);
    }
} // namespace simpleutils::Net
