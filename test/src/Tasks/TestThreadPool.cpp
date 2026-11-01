#include <boost/test/unit_test.hpp>

#include <simpleutils/Tasks/ThreadPool.hpp>
#include <simpleutils/Tasks/Time.hpp>
#include <simpleutils/Log/Logger.hpp>

BOOST_AUTO_TEST_SUITE(ThreadPoolTests)

BOOST_AUTO_TEST_CASE(TestInvalidSize)
{
    std::cout << "SUITE: ThreadPoolTests" << std::endl;
    std::cout << "CASE: TestInvalidSize" << std::endl;

    simpleutils::Tasks::ThreadPool pool;
    auto res = pool.Create(0);
    BOOST_CHECK(!res);
}

BOOST_AUTO_TEST_CASE(TestSubmit)
{
    std::cout << "SUITE: ThreadPoolTests" << std::endl;
    std::cout << "CASE: TestSubmit" << std::endl;

    int counters[6] {};
    simpleutils::Tasks::Task tasks[6] {};
    simpleutils::Tasks::ThreadPool pool;

    auto res = pool.Create(4);
    BOOST_CHECK(res);

    for (int i {}; i < 6; ++i)
    {
        tasks[i] = [&, i]() { 
            counters[i] += i;
            simpleutils::Tasks::Sleep(simpleutils::Tasks::Milliseconds(1000));
        };
        pool.Submit(tasks[i]);
    }

    pool.Stop();

    for (int i {}; i < 6; ++i)
    {
        BOOST_CHECK_EQUAL(counters[i], i);
    }
}

BOOST_AUTO_TEST_SUITE_END()