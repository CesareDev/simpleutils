#include <boost/test/unit_test.hpp>

#include <simpleutils/Threading/Thread.hpp>
#include <simpleutils/Threading/Runnable.hpp>
#include <simpleutils/Time/Time.hpp>

class MyRunnable : public simpleutils::Threading::Runnable
{
    public:
        MyRunnable() = default;
        ~MyRunnable() override = default;

        void Run() override
        {
            ++Counter;
            simpleutils::Time::Sleep(simpleutils::Time::Milliseconds(500));
        }

    public:
        int Counter {};
};

BOOST_AUTO_TEST_SUITE(ThreadTests)

BOOST_AUTO_TEST_CASE(TestStart)
{
    std::cout << "SUITE: ThreadTests" << std::endl;
    std::cout << "CASE: TestStart" << std::endl;

    simpleutils::Threading::Thread thread {};
    int counter {};
    thread.Start([&counter]() {
        for (int i; i < 10; ++i)
        {
            ++counter;
            simpleutils::Time::Sleep(simpleutils::Time::Milliseconds(100));
        }
    });

    thread.Join();
    BOOST_CHECK_EQUAL(counter, 10);
}

BOOST_AUTO_TEST_CASE(TestRunnable)
{
    std::cout << "SUITE: ThreadTests" << std::endl;
    std::cout << "CASE: TestRunnable" << std::endl;

    simpleutils::Threading::Thread thread {};
    MyRunnable runnable;
    thread.Start(runnable);
    thread.Join();
    BOOST_CHECK_EQUAL(runnable.Counter, 1);
}

BOOST_AUTO_TEST_SUITE_END()