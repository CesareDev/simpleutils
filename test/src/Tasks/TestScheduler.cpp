#include <boost/test/unit_test.hpp>

#include <simpleutils/Tasks/Scheduler.hpp>

BOOST_AUTO_TEST_SUITE(SchedulerTests)

BOOST_AUTO_TEST_CASE(TestPeriodicTask)
{
    std::cout << "SUITE: SchedulerTests" << std::endl;
    std::cout << "CASE: TestPeriodicTask" << std::endl;

    int counter {};
    simpleutils::Tasks::Task task = [&]() {
        if (counter < 4)
            counter++;
    };
    simpleutils::Tasks::Scheduler scheduler {};
    scheduler.Start(task, simpleutils::Time::Milliseconds(250));
    simpleutils::Time::Sleep(simpleutils::Time::Seconds(1));
    scheduler.Stop();

    BOOST_CHECK_EQUAL(counter, 4);
}

BOOST_AUTO_TEST_CASE(TestPeriodicRepetitionTask)
{
    std::cout << "SUITE: SchedulerTests" << std::endl;
    std::cout << "CASE: TestPeriodicRepetitionTask" << std::endl;

    int repetition = 10;
    int counter {};
    simpleutils::Tasks::Task task = [&]() {
        counter++;
    };
    simpleutils::Tasks::Scheduler scheduler {};
    scheduler.StartFor(task, simpleutils::Time::Milliseconds(10), repetition);
    simpleutils::Time::Sleep(simpleutils::Time::Seconds(1));
    scheduler.Stop();

    BOOST_CHECK_EQUAL(counter, repetition);
}

BOOST_AUTO_TEST_SUITE_END()