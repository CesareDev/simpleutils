#ifndef SIMPLEUTILS_THREADPOOL_HPP
#define SIMPLEUTILS_THREADPOOL_HPP

#include <simpleutils/Tasks/Task.hpp>

namespace simpleutils::Tasks
{
    class ThreadPool
    {
        public:
            ThreadPool();
            ~ThreadPool();

            void Submit(const Task& task);

        private:
    };
} // namespace simpleutils::Tasks


#endif // SIMPLEUTILS_THREADPOOL_HPP