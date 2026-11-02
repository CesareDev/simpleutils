#include <boost/test/unit_test.hpp>

#include <simpleutils/Net/Buffer.hpp>

class Test : public simpleutils::Net::Serializable
{
    public:
        Test() = default;
        ~Test() override = default;

    protected:
        bool Serialize(simpleutils::Net::Buffer& buffer) const override
        {
            return buffer.Write(memberInt) && buffer.Write(memberFloat) && buffer.Write(memberString);
        }

        bool Deserialize(simpleutils::Net::Buffer& buffer) override
        {
            return buffer.Read(memberInt) && buffer.Read(memberFloat) && buffer.Read(memberString);
        }
    
    public:
        int memberInt {};
        float memberFloat {};
        std::string memberString {};
};

BOOST_AUTO_TEST_SUITE(BufferTests)

BOOST_AUTO_TEST_CASE(TestWriteRead)
{
    std::cout << "SUITE: BufferTests" << std::endl;
    std::cout << "CASE: TestWriteRead" << std::endl;

    simpleutils::Net::Buffer buffer {};
    
    int w_value = 67;
    int r_value {};
    BOOST_CHECK(buffer.Write(w_value));
    BOOST_CHECK(buffer.Read(r_value));
    BOOST_CHECK_EQUAL(w_value, r_value);
}

BOOST_AUTO_TEST_CASE(TestWriteReadSerializable)
{
    std::cout << "SUITE: BufferTests" << std::endl;
    std::cout << "CASE: TestWriteRead" << std::endl;

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
}

BOOST_AUTO_TEST_SUITE_END()