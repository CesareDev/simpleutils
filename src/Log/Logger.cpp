#include <simpleutils/Log/Logger.hpp>

#include <iostream>
#include <mutex>

static std::mutex print_mutex {};

namespace simpleutils::Log
{
    void Log(const char* level, const char* date, const char* time, const std::string& msg)
    {
        std::unique_lock<std::mutex> print_lock(print_mutex);
        
        std::cout << "[" <<  level << "] "
                  << "[" <<  date << " " <<  time << "] "
                  << msg << std::endl;
    }

    void Info(const std::string& msg)
    {
        Log("INFO", __DATE__, __TIME__, msg);
    }

    void Debug(const std::string& msg)
    {
        Log("DEBUG", __DATE__, __TIME__, msg);
    }

    void Error(const std::string& msg)
    {
        Log("ERROR", __DATE__, __TIME__, msg);
    }

    void Fatal(const std::string& msg)
    {
        Log("FATAL", __DATE__, __TIME__, msg);
    }
} // namespace simpleutils::Log
