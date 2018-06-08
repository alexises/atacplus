#include <boost/test/unit_test.hpp>

#include "network/TcpServer.h"
#include "network/TcpClient.h"
#include "network/DecodingException.h"

BOOST_AUTO_TEST_SUITE(tcpServer)

BOOST_AUTO_TEST_CASE(basic_usage_server)
{
    TcpServer server;
    BOOST_CHECK(server.isUsable() == false);
    server.listen("0.0.0.0", 4444);
    BOOST_CHECK(server.isUsable() == true);
}

BOOST_AUTO_TEST_CASE(basic_usage_client)
{
    TcpClient client;
    BOOST_CHECK(client.isUsable() == false);
    client.connect("8.8.8.8", 53);
    BOOST_CHECK(client.isUsable() == true);
}

BOOST_AUTO_TEST_CASE(dns_usage_client)
{
    TcpClient client;
    BOOST_CHECK(client.isUsable() == false);
    client.connect("www.goole.fr", 80);
    BOOST_CHECK(client.isUsable() == true);
}

BOOST_AUTO_TEST_SUITE_END()
