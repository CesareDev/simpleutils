#ifndef SIMPLEUTILS_LOGGER_HPP
#define SIMPLEUTILS_LOGGER_HPP

#include <string>

namespace simpleutils::Log
{
    void Log(const char* level, const char* date, const char* time, const std::string& stream);
    void Info(const std::string& stream);
    void Debug(const std::string& stream);
    void Error(const std::string& stream);
    void Fatal(const std::string& stream);
} // namespace simpleutils::Log

#endif