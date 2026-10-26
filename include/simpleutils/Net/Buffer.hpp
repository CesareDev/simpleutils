
#ifndef SIMPLEUTILS_BUFFER_HPP
#define SIMPLEUTILS_BUFFER_HPP

#include <simpleutils/Net/Serializable.hpp>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace simpleutils::Net
{
    class Buffer
    {
        public:
            const void* GetData() const;
            std::size_t Size() const;
            std::size_t Remaining() const;

            void Clear();
            void Reset();
            bool Append(const Buffer& other);

            bool Write(std::int8_t value);
            bool Write(std::int16_t value);
            bool Write(std::int32_t value);
            bool Write(std::int64_t value);
            bool Write(std::uint8_t value);
            bool Write(std::uint16_t value);
            bool Write(std::uint32_t value);
            bool Write(std::uint64_t value);
            bool Write(float value);
            bool Write(double value);
            bool Write(const std::string& value);
            bool Write(const void* data, std::size_t size);
            bool Write(const Serializable& value);

            bool Read(std::int8_t& value);
            bool Read(std::int16_t& value);
            bool Read(std::int32_t& value);
            bool Read(std::int64_t& value);
            bool Read(std::uint8_t& value);
            bool Read(std::uint16_t& value);
            bool Read(std::uint32_t& value);
            bool Read(std::uint64_t& value);
            bool Read(float& value);
            bool Read(double& value);
            bool Read(std::string& value);
            bool Read(void* data, std::size_t size);
            bool Read(Serializable& value);

        private:
            bool write_raw(const void* data, std::size_t size);
            bool read_raw(void* dest, std::size_t size);

        private:
            std::vector<std::byte> m_Data;
            std::size_t m_WriteCursor {};
            std::size_t m_ReadCursor {};
    };
}

#endif // SIMPLEUTILS_BUFFER_HPP
