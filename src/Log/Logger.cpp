#include <simpleutils/Log/Logger.hpp>

#include <iostream>
#include <mutex>

static std::mutex print_mutex {};

namespace simpleutils::Log
{
    void Log(const char* level, const char* date, const char* time, const std::string& stream)
    {
        std::unique_lock<std::mutex> print_lock(print_mutex);
        
        std::cout << "[" <<  level << "] "
                  << "[" <<  date << " " <<  time << "] "
                  <<  stream << std::endl;
    }

    void Info(const std::string& stream)
    {
        Log("INFO", __DATE__, __TIME__, stream);
    }

    void Debug(const std::string& stream)
    {
        Log("DEBUG", __DATE__, __TIME__, stream);
    }

    void Error(const std::string& stream)
    {
        Log("ERROR", __DATE__, __TIME__, stream);
    }

    void Fatal(const std::string& stream)
    {
        Log("FATAL", __DATE__, __TIME__, stream);
    }
} // namespace simpleutils::Log
