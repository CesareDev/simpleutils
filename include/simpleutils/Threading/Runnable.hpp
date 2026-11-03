#ifndef SIMPLEUTILS_RUNNABLE_HPP
#define SIMPLEUTILS_RUNNABLE_HPP

namespace simpleutils::Threading
{
    class Runnable
    {
        public:
            virtual ~Runnable() = default;
            virtual void Run() = 0;
    };
} // namespace simpleutils::Threading


#endif // SIMPLEUTILS_RUNNABLE_HPP