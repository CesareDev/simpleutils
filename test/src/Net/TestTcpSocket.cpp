#include <boost/test/unit_test.hpp>

#include <simpleutils/Net/TcpSocket.hpp>
#include <simpleutils/Tasks/Time.hpp>

#include <thread>

BOOST_AUTO_TEST_SUITE(TcpSocketTests)

BOOST_AUTO_TEST_CASE(TestPacket)
{
    std::cout << "SUITE: TcpSocketTests" << std::endl;
    std::cout << "CASE: TestPacket" << std::endl;
    
    simpleutils::Net::TcpSocket server {};
    BOOST_CHECK(server.Bind("127.0.0.1", 0));
    BOOST_CHECK(server.Listen());
    simpleutils::Net::Endpoint serverLocalEndpoint = server.GetLocalEndpoint();
    BOOST_CHECK(serverLocalEndpoint.isValid);
    std::thread clientThread([serverLocalEndpoint](){
        simpleutils::Net::TcpSocket client {};
        simpleutils::Tasks::Sleep(simpleutils::Tasks::Seconds(1));
        BOOST_CHECK(client.Connect(serverLocalEndpoint.GetAddress(), serverLocalEndpoint.GetPort()));
        simpleutils::Net::Packet packet;
        BOOST_CHECK(packet.GetBuffer().Write("Hello World!"));
        BOOST_CHECK(client.Send(packet));
    });
    auto client = server.Accept();
    BOOST_CHECK(client.IsOpen());
    auto receive = client.Receive();
    std::string msg {};
    BOOST_CHECK(receive.GetBuffer().Read(msg));
    BOOST_CHECK_EQUAL(msg, "Hello World!");
    if (clientThread.joinable())
        clientThread.join();
}

BOOST_AUTO_TEST_SUITE_END()