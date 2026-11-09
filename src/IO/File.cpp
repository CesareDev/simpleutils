
#include <simpleutils/IO/File.hpp>

#include <filesystem>
#include <iterator>
#include <limits>
#include <system_error>

namespace simpleutils::IO
{
    File::~File()
    {
        Close();
    }

    bool File::Open(const std::string& filePath, FileMode mode)
    {
        if (IsOpen())
            return false;

        std::ios::openmode flags = std::ios::binary;

        switch (mode)
        {
            case FileMode::Read:
                flags |= std::ios::in;
                break;
            case FileMode::Write:
                flags |= std::ios::out | std::ios::trunc;
                break;
            case FileMode::Append:
                flags |= std::ios::out | std::ios::app;
                break;
            case FileMode::ReadWrite:
                flags |= std::ios::in | std::ios::out;
                break;
            default:
                return false;
        }

        m_Stream.open(filePath, flags);

        if (!IsOpen())
            return false;

        m_FilePath = filePath;

        return true;
    }

    void File::Close()
    {
        if (IsOpen())
            m_Stream.close();

        m_FilePath.clear();
    }

    bool File::IsOpen() const
    {
        return m_Stream.is_open();
    }

    bool File::IsEOF() const
    {
        return m_Stream.eof();
    }

    bool File::HasError() const
    {
        if (m_Stream.bad())
            return true;

        return m_Stream.fail() && !m_Stream.eof();
    }

    bool File::ReadLine(std::string& line)
    {
        if (!IsOpen() || !m_Stream)
            return false;

        return static_cast<bool>(std::getline(m_Stream, line));
    }

    bool File::ReadAll(std::string& content)
    {
        if (!IsOpen() || !m_Stream)
            return false;

        content.assign(std::istreambuf_iterator<char>(m_Stream), std::istreambuf_iterator<char>());

        return !m_Stream.bad();
    }

    bool File::Write(const std::string& text)
    {
        if (!IsOpen() || !m_Stream)
            return false;

        if (text.size() > static_cast<std::size_t>(std::numeric_limits<std::streamsize>::max()))
            return false;

        m_Stream.write(text.data(), static_cast<std::streamsize>(text.size()));

        return static_cast<bool>(m_Stream);
    }

    bool File::Read(std::vector<std::byte>& data, std::size_t size)
    {
        if (!IsOpen() || !m_Stream)
            return false;

        if (size > static_cast<std::size_t>(std::numeric_limits<std::streamsize>::max()))
            return false;

        if (size == 0)
        {
            data.clear();
            return true;
        }

        data.resize(size);

        m_Stream.read(reinterpret_cast<char*>(data.data()), static_cast<std::streamsize>(size));

        std::size_t bytesRead = static_cast<std::size_t>(m_Stream.gcount());

        data.resize(bytesRead);

        // A short read at EOF is acceptable.
        return !m_Stream.bad() && (static_cast<bool>(m_Stream) || m_Stream.eof());
    }

    bool File::Write(const std::vector<std::byte>& data)
    {
        if (!IsOpen() || !m_Stream)
            return false;

        if (data.size() > static_cast<std::size_t>(std::numeric_limits<std::streamsize>::max()))
            return false;

        if (data.empty())
            return true;

        m_Stream.write(reinterpret_cast<const char*>(data.data()), static_cast<std::streamsize>(data.size()));

        return static_cast<bool>(m_Stream);
    }

    bool File::Flush()
    {
        if (!IsOpen() || !m_Stream)
            return false;

        m_Stream.flush();

        return static_cast<bool>(m_Stream);
    }

    std::size_t File::GetSize() const
    {
        if (!IsOpen())
            return 0;

        std::error_code error {};

        std::uintmax_t size = std::filesystem::file_size(m_FilePath, error);

        if (error)
            return 0;

        if (size > std::numeric_limits<std::size_t>::max())
            return 0;

        return static_cast<std::size_t>(size);
    }
}
