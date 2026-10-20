#ifndef SIMPLEUTILS_LOGGER_HPP
#define SIMPLEUTILS_LOGGER_HPP

#include <string>

namespace simpleutils::Log
{
    void Log(const char* level, const char* date, const char* time, const std::string& msg);
    void Info(const std::string& msg);
    void Debug(const std::string& msg);
    void Error(const std::string& msg);
    void Fatal(const std::string& msg);
} // namespace simpleutils::Log

#endif