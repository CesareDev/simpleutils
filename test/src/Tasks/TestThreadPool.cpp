#include <boost/test/unit_test.hpp>

#include <simpleutils/Tasks/ThreadPool.hpp>
#include <simpleutils/Tasks/Time.hpp>
#include <simpleutils/Log/Logger.hpp>

BOOST_AUTO_TEST_SUITE(ThreadPoolTests)

BOOST_AUTO_TEST_CASE(TestInvalidSize)
{
    bool exception {};
    try
    {
        simpleutils::Tasks::ThreadPool pool(0);    
    }
    catch (const std::invalid_argument& e)
    {
        exception = true;
    }
    
    BOOST_CHECK(exception);
}

BOOST_AUTO_TEST_CASE(TestSubmit)
{
    int counters[6] {};
    simpleutils::Tasks::Task tasks[6] {};
    simpleutils::Tasks::ThreadPool pool(4);

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