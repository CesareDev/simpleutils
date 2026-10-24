#ifndef SIMPLEUTILS_TASK_HPP
#define SIMPLEUTILS_TASK_HPP

#include <functional>

namespace simpleutils::Tasks
{
    typedef std::function<void()> Task;
} // namespace simpleutils:Tasks


#endif