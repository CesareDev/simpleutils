#include <boost/test/unit_test.hpp>

#include <simpleutils/Net/Socket.hpp>

class TestSocket : public simpleutils::Net::Socket
{
    public:
        bool Send(const simpleutils::Net::Packet& packet) override { return false; }
        bool SendRaw(const void* data, std::size_t size) override { return false; }
        simpleutils::Net::Packet Receive(const simpleutils::Time::Duration& timeout) override { return {}; }
        bool ReceiveRaw(void* buffer, std::size_t capacity, std::size_t& bytesReceived, const simpleutils::Time::Duration& timeout = simpleutils::Time::Milliseconds(0)) { return false; }

        simpleutils::Net::Endpoint Resolve(const std::string& address, int port)
        {
            return resolve(address, port);
        }
};

BOOST_AUTO_TEST_SUITE(SocketTests)

BOOST_AUTO_TEST_CASE(TestAddressSolver)
{
    std::cout << "SUITE: SocketTests" << std::endl;
    std::cout << "CASE: TestAddressSolver" << std::endl;
    
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
}

BOOST_AUTO_TEST_SUITE_END()