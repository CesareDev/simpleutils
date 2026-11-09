
#include <boost/test/unit_test.hpp>

#include <simpleutils/IO/File.hpp>

BOOST_AUTO_TEST_SUITE(FileTests)

BOOST_AUTO_TEST_CASE(TestWriteRead)
{
    const std::string path = "config/IOTestFile.txt";
    const std::string message = "Hello simpleutils!";

    simpleutils::IO::File file {};

    BOOST_REQUIRE(file.Open(path, simpleutils::IO::FileMode::Write));
    BOOST_REQUIRE(file.Write(message));
    BOOST_REQUIRE(file.Flush());

    BOOST_CHECK_EQUAL(file.GetSize(), message.size());

    file.Close();

    BOOST_REQUIRE(file.Open(path, simpleutils::IO::FileMode::Read));

    std::string content {};

    BOOST_REQUIRE(file.ReadAll(content));
    BOOST_CHECK_EQUAL(content, message);

    file.Close();

    BOOST_REQUIRE(file.Open(path, simpleutils::IO::FileMode::Write));
    BOOST_REQUIRE(file.Write(""));
    BOOST_REQUIRE(file.Flush());

    BOOST_CHECK_EQUAL(file.GetSize(), 0);

    file.Close();
}

BOOST_AUTO_TEST_SUITE_END()
