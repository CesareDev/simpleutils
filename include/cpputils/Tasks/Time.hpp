#ifndef SIMPLEUTILS_TIME_HPP
#define SIMPLEUTILS_TIME_HPP

#include <chrono>
#include <cstdint>

namespace simpleutils::Tasks
{
    class Duration
    {
        public:
            virtual ~Duration() = default;
            virtual std::chrono::nanoseconds ToChrono() const = 0;
        protected:
            explicit Duration(int64_t value);
        protected:
            int64_t m_Value {};
    };

    class Hours : public Duration
    {
        public:
            explicit Hours(int64_t value);
            ~Hours() = default;
            std::chrono::nanoseconds ToChrono() const override;
    };

    class Minutes : public Duration
    {
        public:
            explicit Minutes(int64_t value);
            ~Minutes() = default;
            std::chrono::nanoseconds ToChrono() const override;
    };

    class Seconds : public Duration
    {
        public:
            explicit Seconds(int64_t value);
            ~Seconds() = default;
            std::chrono::nanoseconds ToChrono() const override;
    };

    class Milliseconds : public Duration
    {
        public:
            explicit Milliseconds(int64_t value);
            ~Milliseconds() = default;
            std::chrono::nanoseconds ToChrono() const override;
    };

    class Microseconds : public Duration
    {
        public:
            explicit Microseconds(int64_t value);
            ~Microseconds() = default;
            std::chrono::nanoseconds ToChrono() const override;
    };

    class Nanoseconds : public Duration
    {
        public:
            explicit Nanoseconds(int64_t value);
            virtual ~Nanoseconds() = default;
            std::chrono::nanoseconds ToChrono() const override;
    };

    void Sleep(const Duration& duration);
} // namespace simpleutils::Tasks


#endif