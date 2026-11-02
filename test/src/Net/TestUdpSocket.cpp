#include <boost/test/unit_test.hpp>

#include <simpleutils/Net/UdpSocket.hpp>

#include <thread>

BOOST_AUTO_TEST_SUITE(UdpSocketTests)

BOOST_AUTO_TEST_CASE(TestPacket)
{
    std::cout << "SUITE: UdpSocketTests" << std::endl;
    std::cout << "CASE: TestPacket" << std::endl;

    simpleutils::Net::UdpSocket server {};
    server.Bind("127.0.0.1", 0);
    simpleutils::Net::Endpoint serverLocalEndpoint = server.GetLocalEndpoint();
    BOOST_CHECK(serverLocalEndpoint.isValid);
    std::thread clientThread([serverLocalEndpoint]() {
        simpleutils::Net::UdpSocket client {};
        simpleutils::Time::Sleep(simpleutils::Time::Seconds(1));
        simpleutils::Net::Packet packet;
        BOOST_CHECK(client.SetDestination(serverLocalEndpoint.GetAddress(), serverLocalEndpoint.GetPort()));
        BOOST_CHECK(packet.GetBuffer().Write("Hello World!"));
        BOOST_CHECK(client.Send(packet));
    });
    auto receive = server.Receive();
    BOOST_CHECK(receive.IsValid());
    std::string msg {};
    BOOST_CHECK(receive.GetBuffer().Read(msg));
    BOOST_CHECK_EQUAL(msg, "Hello World!");
    if (clientThread.joinable())
        clientThread.join();
}

BOOST_AUTO_TEST_CASE(TestTimeout)
{
    simpleutils::Net::UdpSocket server {};
    BOOST_CHECK(server.Bind("127.0.0.1", 0));
    auto receive = server.Receive(simpleutils::Time::Seconds(1));
    BOOST_CHECK(!receive.IsValid());
}

BOOST_AUTO_TEST_SUITE_END()