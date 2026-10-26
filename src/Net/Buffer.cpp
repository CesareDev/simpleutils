
#include <simpleutils/Net/Buffer.hpp>
#include <simpleutils/Net/Serializable.hpp>

#include <arpa/inet.h>

#include <algorithm>
#include <cstring>
#include <limits>
#include <new>
#include <stdexcept>
#include <utility>

namespace
{
    bool isLittleEndian()
    {
        const std::uint16_t value = 1;
        return *reinterpret_cast<const std::uint8_t*>(&value) == 1;
    }

    std::uint8_t byteswap(std::uint8_t value)
    {
        return value;
    }

    std::uint16_t byteswap(std::uint16_t value)
    {
        return htons(value);
    }

    std::uint32_t byteswap(std::uint32_t value)
    {
        return htonl(value);
    }

    std::uint64_t byteswap(std::uint64_t value)
    {
        if (!isLittleEndian())
            return value;

        return (static_cast<std::uint64_t>(
                    byteswap(static_cast<std::uint32_t>(value & 0xffffffffULL))
                ) << 32)
             | byteswap(static_cast<std::uint32_t>(value >> 32));
    }

    std::int8_t byteswap(std::int8_t value)
    {
        return value;
    }

    std::int16_t byteswap(std::int16_t value)
    {
        return static_cast<std::int16_t>(
            byteswap(static_cast<std::uint16_t>(value))
        );
    }

    std::int32_t byteswap(std::int32_t value)
    {
        return static_cast<std::int32_t>(
            byteswap(static_cast<std::uint32_t>(value))
        );
    }

    std::int64_t byteswap(std::int64_t value)
    {
        return static_cast<std::int64_t>(
            byteswap(static_cast<std::uint64_t>(value))
        );
    }

    float byteswap(float value)
    {
        std::uint32_t tmp;
        std::memcpy(&tmp, &value, sizeof(tmp));

        tmp = byteswap(tmp);

        std::memcpy(&value, &tmp, sizeof(value));
        return value;
    }

    double byteswap(double value)
    {
        std::uint64_t tmp;
        std::memcpy(&tmp, &value, sizeof(tmp));

        tmp = byteswap(tmp);

        std::memcpy(&value, &tmp, sizeof(value));
        return value;
    }
}

namespace simpleutils::Net
{
    const void* Buffer::GetData() const
    {
        if (Remaining() == 0)
            return nullptr;

        return m_Data.data() + m_ReadCursor;
    }

    std::size_t Buffer::Size() const
    {
        return m_WriteCursor;
    }

    std::size_t Buffer::Remaining() const
    {
        return m_WriteCursor - m_ReadCursor;
    }

    void Buffer::Clear()
    {
        m_ReadCursor = 0;
        m_WriteCursor = 0;
        m_Data.clear();
    }

    void Buffer::Reset()
    {
        Clear();
        std::vector<std::byte>().swap(m_Data);
    }

    bool Buffer::Append(const Buffer& other)
    {
        if (this == &other)
        {
            Buffer copy = other;
            return write_raw(copy.GetData(), copy.Remaining());
        }

        return write_raw(other.GetData(), other.Remaining());
    }

    // Write signed integers

    bool Buffer::Write(std::int8_t value)
    {
        value = byteswap(value);
        return write_raw(&value, sizeof(value));
    }

    bool Buffer::Write(std::int16_t value)
    {
        value = byteswap(value);
        return write_raw(&value, sizeof(value));
    }

    bool Buffer::Write(std::int32_t value)
    {
        value = byteswap(value);
        return write_raw(&value, sizeof(value));
    }

    bool Buffer::Write(std::int64_t value)
    {
        value = byteswap(value);
        return write_raw(&value, sizeof(value));
    }

    bool Buffer::Write(std::uint8_t value)
    {
        value = byteswap(value);
        return write_raw(&value, sizeof(value));
    }

    bool Buffer::Write(std::uint16_t value)
    {
        value = byteswap(value);
        return write_raw(&value, sizeof(value));
    }

    bool Buffer::Write(std::uint32_t value)
    {
        value = byteswap(value);
        return write_raw(&value, sizeof(value));
    }

    bool Buffer::Write(std::uint64_t value)
    {
        value = byteswap(value);
        return write_raw(&value, sizeof(value));
    }

    bool Buffer::Write(float value)
    {
        value = byteswap(value);
        return write_raw(&value, sizeof(value));
    }

    bool Buffer::Write(double value)
    {
        value = byteswap(value);
        return write_raw(&value, sizeof(value));
    }

    bool Buffer::Write(const std::string& value)
    {
        if (value.size() > std::numeric_limits<std::uint64_t>::max())
            return false;

        const std::size_t originalCursor = m_WriteCursor;

        if (!Write(static_cast<std::uint64_t>(value.size())))
            return false;

        if (!write_raw(value.data(), value.size()))
        {
            m_WriteCursor = originalCursor;
            m_Data.resize(originalCursor);
            return false;
        }

        return true;
    }

    bool Buffer::Write(const void* data, std::size_t size)
    {
        return write_raw(data, size);
    }

    bool Buffer::Write(const Serializable& value)
    {
        return value.Serialize(*this);
    }

    bool Buffer::Read(std::int8_t& value)
    {
        if (!read_raw(&value, sizeof(value)))
            return false;

        value = byteswap(value);
        return true;
    }

    bool Buffer::Read(std::int16_t& value)
    {
        if (!read_raw(&value, sizeof(value)))
            return false;

        value = byteswap(value);
        return true;
    }

    bool Buffer::Read(std::int32_t& value)
    {
        if (!read_raw(&value, sizeof(value)))
            return false;

        value = byteswap(value);
        return true;
    }

    bool Buffer::Read(std::int64_t& value)
    {
        if (!read_raw(&value, sizeof(value)))
            return false;

        value = byteswap(value);
        return true;
    }

    bool Buffer::Read(std::uint8_t& value)
    {
        if (!read_raw(&value, sizeof(value)))
            return false;

        value = byteswap(value);
        return true;
    }

    bool Buffer::Read(std::uint16_t& value)
    {
        if (!read_raw(&value, sizeof(value)))
            return false;

        value = byteswap(value);
        return true;
    }

    bool Buffer::Read(std::uint32_t& value)
    {
        if (!read_raw(&value, sizeof(value)))
            return false;

        value = byteswap(value);
        return true;
    }

    bool Buffer::Read(std::uint64_t& value)
    {
        if (!read_raw(&value, sizeof(value)))
            return false;

        value = byteswap(value);
        return true;
    }

    // Read floating-point values

    bool Buffer::Read(float& value)
    {
        if (!read_raw(&value, sizeof(value)))
            return false;

        value = byteswap(value);
        return true;
    }

    bool Buffer::Read(double& value)
    {
        if (!read_raw(&value, sizeof(value)))
            return false;

        value = byteswap(value);
        return true;
    }

    // Read strings and raw data

    bool Buffer::Read(std::string& value)
    {
        const std::size_t originalCursor = m_ReadCursor;

        std::uint64_t size = 0;

        if (!Read(size))
            return false;

        if (size > Remaining() || size > value.max_size())
        {
            m_ReadCursor = originalCursor;
            return false;
        }

        std::string temp;
        temp.resize(static_cast<std::size_t>(size));

        if (!read_raw(temp.data(), temp.size()))
        {
            m_ReadCursor = originalCursor;
            return false;
        }

        value = std::move(temp);

        return true;
    }

    bool Buffer::Read(void* data, std::size_t size)
    {
        return read_raw(data, size);
    }

    bool Buffer::Read(Serializable& value)
    {
        return value.Deserialize(*this);
    }

    // Internal raw operations

    bool Buffer::write_raw(const void* data, std::size_t size)
    {
        if (size == 0)
            return true;

        if (data == nullptr)
            return false;

        if (size > m_Data.max_size() - m_WriteCursor)
            return false;

        m_Data.resize(m_WriteCursor + size);
        
        std::memcpy(m_Data.data() + m_WriteCursor, data, size);
        m_WriteCursor += size;

        return true;
    }

    bool Buffer::read_raw(void* dest, std::size_t size)
    {
        if (size > Remaining())
            return false;

        if (size == 0)
            return true;

        if (dest == nullptr)
            return false;

        std::memcpy(dest, m_Data.data() + m_ReadCursor, size);
        m_ReadCursor += size;

        return true;
    }
}
