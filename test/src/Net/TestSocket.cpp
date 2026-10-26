#include <boost/test/unit_test.hpp>

#include <simpleutils/Net/Socket.hpp>

struct SuiteHelper
{
    SuiteHelper()  { std::cout << ">>> SUITE: SocketTests <<<" << std::endl; }
    ~SuiteHelper() { std::cout << ">>> SUITE: SocketTests <<<" << std::endl; }
};

class TestSocket : simpleutils::Net::Socket
{
    public:
        std::size_t Send(const void* data, std::size_t size) override { return 0; }
        std::size_t Receive(void* buffer, std::size_t capacity) override { return 0; }

        simpleutils::Net::Endpoint Resolve(const std::string& address, int port)
        {
            return resolve(address, port);
        }
};

BOOST_FIXTURE_TEST_SUITE(SocketTests, SuiteHelper)

BOOST_AUTO_TEST_CASE(TestAddressSolver)
{
    std::cout << "CASE: TestAddressSolver [START]" << std::endl;
    
    TestSocket socket {};
    
    simpleutils::Net::Endpoint ep1 = socket.Resolve("127.0.0.1", 12345);
    BOOST_CHECK(ep1.isValid);

    simpleutils::Net::Endpoint ep2 = socket.Resolve("lo", 12345);
    BOOST_CHECK(ep2.isValid);

    simpleutils::Net::Endpoint ep3 = socket.Resolve("example.com", 12345);
    BOOST_CHECK(ep3.isValid);

    simpleutils::Net::Endpoint epPort = socket.Resolve("127.0.0.1", -1);
    BOOST_CHECK(!epPort.isValid);

    simpleutils::Net::Endpoint epAddr = socket.Resolve("foo", 12345);
    BOOST_CHECK(!epAddr.isValid);

    std::cout << "CASE: TestAddressSolver [END]" << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()