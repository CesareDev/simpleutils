
#ifndef SIMPLEUTILS_THREAD_HPP
#define SIMPLEUTILS_THREAD_HPP

#include <thread>
#include <functional>

namespace simpleutils::Threading
{
    using Callback = std::function<void()>;

    class Thread
    {
        public:
            Thread() = default;
            ~Thread();

            Thread(const Thread&) = delete;
            Thread& operator=(const Thread&) = delete;

            bool Start(const Callback& callback);
            void Join();

            bool IsRunning() const;
            bool IsJoinable() const;

        private:
            std::thread m_Thread {};
    };
}

#endif // SIMPLEUTILS_THREAD_HPP
