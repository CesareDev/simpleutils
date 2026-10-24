#include <boost/test/unit_test.hpp>

#include <simpleutils/Config/IniLoader.hpp>

BOOST_AUTO_TEST_SUITE(IniLoaderTests)

BOOST_AUTO_TEST_CASE(TestLoad)
{
    simpleutils::Config::IniLoader loader {};
    BOOST_CHECK(loader.LoadFromFile("config/TEST.ini"));
}

BOOST_AUTO_TEST_CASE(TestGetString)
{
    simpleutils::Config::IniLoader loader {};
    BOOST_CHECK(loader.LoadFromFile("config/TEST.ini"));
    BOOST_CHECK_EQUAL(loader.GetString("SECTION_1", "ENTRY_1"), "String 1");
    BOOST_CHECK_EQUAL(loader.GetString("SECTION_2", "ENTRY_1"), "String 2");
}

BOOST_AUTO_TEST_CASE(TestGetInt)
{
    simpleutils::Config::IniLoader loader {};
    BOOST_CHECK(loader.LoadFromFile("config/TEST.ini"));
    BOOST_CHECK_EQUAL(loader.GetInt("SECTION_1", "ENTRY_2"), 12345);
    BOOST_CHECK_EQUAL(loader.GetInt("SECTION_2", "ENTRY_2"), 54321);
}

BOOST_AUTO_TEST_CASE(TestGetBool)
{
    simpleutils::Config::IniLoader loader {};
    BOOST_CHECK(loader.LoadFromFile("config/TEST.ini"));
    BOOST_CHECK_EQUAL(loader.GetBool("SECTION_1", "ENTRY_3"), true);
    BOOST_CHECK_EQUAL(loader.GetBool("SECTION_2", "ENTRY_3"), true);
}

BOOST_AUTO_TEST_SUITE_END()