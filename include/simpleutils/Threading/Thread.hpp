
#ifndef SIMPLEUTILS_THREAD_HPP
#define SIMPLEUTILS_THREAD_HPP

#include <simpleutils/Threading/Runnable.hpp>

#include <thread>
#include <functional>
#include <atomic>

namespace simpleutils::Threading
{
    class Thread
    {
        public:
            using Callback = std::function<void()>;

        public:
            Thread() = default;
            ~Thread();

            Thread(const Thread&) = delete;
            Thread& operator=(const Thread&) = delete;

            bool Start(const Callback& callback);
            bool Start(Runnable& runnable);
            void Join();

            bool IsRunning() const;
            bool IsJoinable() const;

        private:
            std::thread m_Thread {};
            std::atomic<bool> m_IsRunning {};
    };
}

#endif // SIMPLEUTILS_THREAD_HPP
