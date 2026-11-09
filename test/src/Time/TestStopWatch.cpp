#include <boost/test/unit_test.hpp>

#include <simpleutils/Time/StopWatch.hpp>

BOOST_AUTO_TEST_SUITE(StopWatchTests)

BOOST_AUTO_TEST_CASE(TestStopWatch)
{
    std::cout << "SUITE: StopWatchTests" << std::endl;
    std::cout << "CASE: TestStopWatch" << std::endl;

    simpleutils::Time::StopWatch stopwatch {};

    BOOST_CHECK(!stopwatch.IsRunning());
    BOOST_CHECK_EQUAL(stopwatch.Elapsed().ToChrono().count(), 0);

    stopwatch.Start();

    simpleutils::Time::Sleep(simpleutils::Time::Milliseconds(100));

    stopwatch.Stop();

    BOOST_CHECK(!stopwatch.IsRunning());
    BOOST_CHECK_GE(stopwatch.Elapsed().ToChrono().count(), simpleutils::Time::Milliseconds(100).ToChrono().count());
}

BOOST_AUTO_TEST_SUITE_END()