#include <boost/test/unit_test.hpp>

#include <simpleutils/Threading/ThreadPool.hpp>
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

BOOST_AUTO_TEST_SUITE(ThreadPoolTests)

BOOST_AUTO_TEST_CASE(TestInvalidSize)
{
    std::cout << "SUITE: ThreadPoolTests" << std::endl;
    std::cout << "CASE: TestInvalidSize" << std::endl;

    simpleutils::Threading::ThreadPool pool;
    auto res = pool.Create(0);
    BOOST_CHECK(!res);
}

BOOST_AUTO_TEST_CASE(TestSubmit)
{
    std::cout << "SUITE: ThreadPoolTests" << std::endl;
    std::cout << "CASE: TestSubmit" << std::endl;

    int counters[6] {};
    simpleutils::Threading::ThreadPool::Callback tasks[6] {};
    simpleutils::Threading::ThreadPool pool;

    auto res = pool.Create(4);
    BOOST_CHECK(res);

    for (int i {}; i < 6; ++i)
    {
        tasks[i] = [&, i]() { 
            counters[i] += i;
            simpleutils::Time::Sleep(simpleutils::Time::Milliseconds(1000));
        };
        pool.Submit(tasks[i]);
    }

    pool.Stop();

    for (int i {}; i < 6; ++i)
    {
        BOOST_CHECK_EQUAL(counters[i], i);
    }
}

BOOST_AUTO_TEST_CASE(TestRunnable)
{
    std::cout << "SUITE: ThreadPoolTests" << std::endl;
    std::cout << "CASE: TestRunnable" << std::endl;

    int counters[6] {};
    simpleutils::Threading::ThreadPool pool;

    auto res = pool.Create(4);
    BOOST_CHECK(res);
    MyRunnable runnable {};
    pool.Submit(runnable);
    pool.Stop();
    BOOST_CHECK_EQUAL(runnable.Counter, 1);
}

BOOST_AUTO_TEST_SUITE_END()