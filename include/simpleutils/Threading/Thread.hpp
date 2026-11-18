
#ifndef SIMPLEUTILS_THREAD_HPP
#define SIMPLEUTILS_THREAD_HPP

#include <simpleutils/Threading/Runnable.hpp>
#include <simpleutils/Common/ReturnCode.hpp>

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

            Common::ReturnCode Start(const Callback& callback);
            Common::ReturnCode Start(Runnable& runnable);
            Common::ReturnCode Join();

            bool IsRunning() const;
            bool IsJoinable() const;

        private:
            std::thread m_Thread {};
            std::atomic<bool> m_IsRunning {};
    };
}

#endif // SIMPLEUTILS_THREAD_HPP
