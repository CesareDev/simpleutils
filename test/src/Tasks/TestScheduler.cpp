#include <boost/test/unit_test.hpp>

#include <simpleutils/Tasks/Scheduler.hpp>

BOOST_AUTO_TEST_SUITE(SchedulerTests)

BOOST_AUTO_TEST_CASE(TestPeriodicTask)
{
    int counter {};
    simpleutils::Tasks::Task task = [&]() {
        counter++;
    };
    simpleutils::Tasks::Scheduler scheduler {};
    scheduler.Start(task, simpleutils::Tasks::Milliseconds(250));
    simpleutils::Tasks::Sleep(simpleutils::Tasks::Seconds(1));
    scheduler.Stop();

    BOOST_CHECK_EQUAL(counter, 4);
}

BOOST_AUTO_TEST_CASE(TestPeriodicRepetitionTask)
{
    int repetition = 10;
    int counter {};
    simpleutils::Tasks::Task task = [&]() {
        counter++;
    };
    simpleutils::Tasks::Scheduler scheduler {};
    scheduler.StartFor(task, simpleutils::Tasks::Milliseconds(10), repetition);
    simpleutils::Tasks::Sleep(simpleutils::Tasks::Seconds(1));
    scheduler.Stop();

    BOOST_CHECK_EQUAL(counter, repetition);
}

BOOST_AUTO_TEST_SUITE_END()