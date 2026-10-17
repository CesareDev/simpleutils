#include <simpleutils/Tasks/Scheduler.hpp>
#include <simpleutils/Tasks/Time.hpp>
#include <simpleutils/Log/Logger.hpp>

int main()
{
    simpleutils::Tasks::Task task1 = []() {
        simpleutils::Log::Debug("Hello 1");
    };

    simpleutils::Tasks::Task task2 = []() {
        simpleutils::Log::Debug("Hello 2");
    };

    simpleutils::Tasks::Scheduler scheduler1 {};
    simpleutils::Tasks::Scheduler scheduler2 {};

    scheduler1.Start(task1, simpleutils::Tasks::Milliseconds(500));
    scheduler2.Start(task2, simpleutils::Tasks::Milliseconds(500));

    simpleutils::Tasks::Sleep(simpleutils::Tasks::Seconds(2));

    return 0;
}