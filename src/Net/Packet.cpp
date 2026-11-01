#include <simpleutils/Net/Packet.hpp>

namespace simpleutils::Net
{
    Packet::Packet()
    {
    }

    Packet::~Packet()
    {
    }

    bool Packet::IsValid() const
    {
        return m_IsValid;
    }

    Buffer& Packet::GetBuffer()
    {
        return m_Buffer;
    }

    const Buffer& Packet::GetBuffer() const
    {
        return m_Buffer;
    }

    void Packet::Clear()
    {
        m_Buffer.Clear();
        m_IsValid = false;
    }
} // namespace simpleutils::Net
