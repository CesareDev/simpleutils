
#ifndef SIMPLEUTILS_FILE_HPP
#define SIMPLEUTILS_FILE_HPP

#include <cstddef>
#include <fstream>
#include <string>
#include <vector>

namespace simpleutils::IO
{
    enum class FileMode
    {
        Read,
        Write,
        Append,
        ReadWrite
    };

    class File
    {
        public:
            File() = default;
            ~File();

            File(const File&) = delete;
            File& operator=(const File&) = delete;

            bool Open(const std::string& filePath, FileMode mode);
            void Close();

            bool IsOpen() const;
            bool IsEOF() const;
            bool HasError() const;

            bool ReadLine(std::string& line);
            bool ReadAll(std::string& content);
            bool Write(const std::string& text);

            bool Read(std::vector<std::byte>& data, std::size_t size);
            bool Write(const std::vector<std::byte>& data);

            bool Flush();
            std::size_t GetSize() const;

        private:
            std::fstream m_Stream {};
            std::string m_FilePath {};
    };
}

#endif // SIMPLEUTILS_FILE_HPP
