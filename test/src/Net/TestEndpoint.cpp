#include <boost/test/unit_test.hpp>

#include <simpleutils/Net/TcpSocket.hpp>
#include <simpleutils/Net/Endpoint.hpp>

BOOST_AUTO_TEST_SUITE(EndpointTest)

BOOST_AUTO_TEST_CASE(TestAddress)
{
    std::cout << "SUITE: EndpointTest" << std::endl;
    std::cout << "CASE: TestAddress" << std::endl;

    simpleutils::Net::TcpSocket socket {};
    socket.Bind("127.0.0.1", 0);
    simpleutils::Net::Endpoint serverLocalEndpoint = socket.GetLocalEndpoint();
    BOOST_CHECK(serverLocalEndpoint.isValid);
    BOOST_CHECK_EQUAL(serverLocalEndpoint.GetAddress(), "127.0.0.1");
}

BOOST_AUTO_TEST_CASE(TestPort)
{
    std::cout << "SUITE: EndpointTest" << std::endl;
    std::cout << "CASE: TestPort" << std::endl;

    simpleutils::Net::TcpSocket socket {};
    socket.Bind("127.0.0.1", 12345);
    simpleutils::Net::Endpoint serverLocalEndpoint = socket.GetLocalEndpoint();
    BOOST_CHECK(serverLocalEndpoint.isValid);
    BOOST_CHECK_EQUAL(serverLocalEndpoint.GetPort(), 12345);
}

BOOST_AUTO_TEST_SUITE_END()