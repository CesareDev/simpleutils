#include <boost/test/unit_test.hpp>

#include <simpleutils/Tasks/Scheduler.hpp>

struct SuiteHelper
{
    SuiteHelper()  { std::cout << ">>> SUITE: SchedulerTests <<<" << std::endl; }
    ~SuiteHelper() { std::cout << ">>> SUITE: SchedulerTests <<<" << std::endl; }
};

BOOST_FIXTURE_TEST_SUITE(SchedulerTests, SuiteHelper)

BOOST_AUTO_TEST_CASE(TestPeriodicTask)
{
    std::cout << "CASE: TestPeriodicTask [START]" << std::endl;

    int counter {};
    simpleutils::Tasks::Task task = [&]() {
        counter++;
    };
    simpleutils::Tasks::Scheduler scheduler {};
    scheduler.Start(task, simpleutils::Tasks::Milliseconds(250));
    simpleutils::Tasks::Sleep(simpleutils::Tasks::Seconds(1));
    scheduler.Stop();

    BOOST_CHECK_EQUAL(counter, 4);

    std::cout << "CASE: TestPeriodicTask [END]" << std::endl;
}

BOOST_AUTO_TEST_CASE(TestPeriodicRepetitionTask)
{
    std::cout << "CASE: TestPeriodicRepetitionTask [START]" << std::endl;

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

    std::cout << "CASE: TestPeriodicRepetitionTask [END]" << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()