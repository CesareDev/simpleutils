#include <boost/test/unit_test.hpp>

#include <simpleutils/Config/IniLoader.hpp>

struct SuiteHelper
{
    SuiteHelper()  { std::cout << ">>> SUITE: IniLoaderTests <<<" << std::endl; }
    ~SuiteHelper() { std::cout << ">>> SUITE: IniLoaderTests <<<" << std::endl; }
};

BOOST_FIXTURE_TEST_SUITE(IniLoaderTests, SuiteHelper)

BOOST_AUTO_TEST_CASE(TestLoad)
{
    std::cout << "CASE: TestLoad [START]" << std::endl;

    simpleutils::Config::IniLoader loader {};
    BOOST_CHECK(loader.LoadFromFile("config/TEST.ini"));

    std::cout << "CASE: TestLoad [END]" << std::endl;
}

BOOST_AUTO_TEST_CASE(TestGetString)
{
    std::cout << "CASE: TestGetString [START]" << std::endl;

    simpleutils::Config::IniLoader loader {};
    BOOST_CHECK(loader.LoadFromFile("config/TEST.ini"));
    BOOST_CHECK_EQUAL(loader.GetString("SECTION_1", "ENTRY_1"), "String 1");
    BOOST_CHECK_EQUAL(loader.GetString("SECTION_2", "ENTRY_1"), "String 2");

    std::cout << "CASE: TestGetString [END]" << std::endl;
}

BOOST_AUTO_TEST_CASE(TestGetInt)
{
    std::cout << "CASE: TestGetInt [START]" << std::endl;

    simpleutils::Config::IniLoader loader {};
    BOOST_CHECK(loader.LoadFromFile("config/TEST.ini"));
    BOOST_CHECK_EQUAL(loader.GetInt("SECTION_1", "ENTRY_2"), 12345);
    BOOST_CHECK_EQUAL(loader.GetInt("SECTION_2", "ENTRY_2"), 54321);

    std::cout << "CASE: TestGetInt [END]" << std::endl;
}

BOOST_AUTO_TEST_CASE(TestGetBool)
{
    std::cout << "CASE: TestGetBool [START]" << std::endl;

    simpleutils::Config::IniLoader loader {};
    BOOST_CHECK(loader.LoadFromFile("config/TEST.ini"));
    BOOST_CHECK_EQUAL(loader.GetBool("SECTION_1", "ENTRY_3"), true);
    BOOST_CHECK_EQUAL(loader.GetBool("SECTION_2", "ENTRY_3"), true);

    std::cout << "CASE: TestGetBool [END]" << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()