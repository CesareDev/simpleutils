#include <boost/test/unit_test.hpp>

#include <simpleutils/Net/SocketPolling.hpp>
#include <simpleutils/Net/UdpSocket.hpp>

#include <thread>

BOOST_AUTO_TEST_SUITE(SocketPollingTests)

BOOST_AUTO_TEST_CASE(TestPoll)
{
    simpleutils::Net::UdpSocket socket1 {};
    simpleutils::Net::UdpSocket socket2 {};

    BOOST_CHECK(socket1.Bind("0.0.0.0", 0));
    BOOST_CHECK(socket2.Bind("0.0.0.0", 0));

    simpleutils::Net::SocketPolling polling {};

    BOOST_CHECK(polling.Add(socket1));
    BOOST_CHECK(polling.Add(socket2));

    bool firstReceive {};
    bool secondReceive {};

    simpleutils::Net::UdpSocket sender {};

    simpleutils::Net::Packet packet1 {};
    BOOST_CHECK(sender.SetDestination(socket1.GetLocalEndpoint().GetAddress(), socket1.GetLocalEndpoint().GetPort()));
    BOOST_CHECK(packet1.GetBuffer().Write("Hello1"));
    BOOST_CHECK(sender.Send(packet1));

    simpleutils::Net::Packet packet2 {};
    BOOST_CHECK(sender.SetDestination(socket2.GetLocalEndpoint().GetAddress(), socket2.GetLocalEndpoint().GetPort()));
    BOOST_CHECK(packet2.GetBuffer().Write("Hello2"));
    BOOST_CHECK(sender.Send(packet2));

    simpleutils::Net::Callback callback = [&firstReceive, &secondReceive](simpleutils::Net::Socket& socket) {
        simpleutils::Net::Packet packet = socket.Receive();
        BOOST_CHECK(packet.IsValid());
        std::string msg {};
        BOOST_CHECK(packet.GetBuffer().Read(msg));
        if (msg == "Hello1")
            firstReceive = true;
        else if (msg == "Hello2")
            secondReceive = true;
    };

    while (!firstReceive || !secondReceive)
    {
        polling.Process(callback);
    }
}

BOOST_AUTO_TEST_SUITE_END()