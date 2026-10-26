#include <boost/test/unit_test.hpp>

#include <simpleutils/Net/Buffer.hpp>

struct SuiteHelper
{
    SuiteHelper()  { std::cout << ">>> SUITE: BufferTests <<<" << std::endl; }
    ~SuiteHelper() { std::cout << ">>> SUITE: BufferTests <<<" << std::endl; }
};

class Test : public simpleutils::Net::Serializable
{
    public:
        bool Serialize(simpleutils::Net::Buffer& buffer) const override
        {
            auto resInt = buffer.Write(memberInt);
            auto resFloat = buffer.Write(memberFloat);
            auto resString = buffer.Write(memberString);

            return resInt && resFloat && resString;
        }

        bool Deserialize(simpleutils::Net::Buffer& buffer) override
        {
            auto resInt = buffer.Read(memberInt);
            auto resFloat = buffer.Read(memberFloat);
            auto resString = buffer.Read(memberString);

            return resInt && resFloat && resString;
        }
    
    public:
        int memberInt {};
        float memberFloat {};
        std::string memberString {};
};

BOOST_FIXTURE_TEST_SUITE(BufferTests, SuiteHelper)

BOOST_AUTO_TEST_CASE(TestWriteRead)
{
    std::cout << "CASE: TestWriteRead [START]" << std::endl;

    simpleutils::Net::Buffer buffer {};
    
    int w_value = 67;
    int r_value {};
    BOOST_CHECK(buffer.Write(w_value));
    BOOST_CHECK(buffer.Read(r_value));
    BOOST_CHECK_EQUAL(w_value, r_value);

    std::cout << "CASE: TestWriteRead [END]" << std::endl;
}

BOOST_AUTO_TEST_CASE(TestWriteReadSerializable)
{
    std::cout << "CASE: TestWriteReadSerializable [START]" << std::endl;

    simpleutils::Net::Buffer buffer {};
    Test w_testClass {};
    w_testClass.memberInt = 67;
    w_testClass.memberFloat = 67.69f;
    w_testClass.memberString = "Hello World!";
    Test r_testClass {};

    BOOST_CHECK(buffer.Write(w_testClass));
    BOOST_CHECK(buffer.Read(r_testClass));
    BOOST_CHECK_EQUAL(w_testClass.memberInt, r_testClass.memberInt);
    BOOST_CHECK_EQUAL(w_testClass.memberFloat, r_testClass.memberFloat);
    BOOST_CHECK_EQUAL(w_testClass.memberString, r_testClass.memberString);

    std::cout << "CASE: TestWriteReadSerializable [END]" << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()