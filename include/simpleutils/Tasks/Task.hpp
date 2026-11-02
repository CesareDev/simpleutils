#ifndef SIMPLEUTILS_TASK_HPP
#define SIMPLEUTILS_TASK_HPP

#include <simpleutils/Net/Socket.hpp>

#include <functional>

namespace simpleutils::Tasks
{
    typedef std::function<void()> SchedulerTask;
    typedef std::function<void()> ThreadPoolTask;
    typedef std::function<void(Net::Socket&)> PollingTask;
} // namespace simpleutils:Tasks


#endif