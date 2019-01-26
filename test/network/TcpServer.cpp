#include <boost/test/unit_test.hpp>
#include <iostream>

#include "network/TcpServer.h"
#include "network/TcpClient.h"
#include "network/Buffer.h"
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
    client.connect("www.github.com", 80);
    BOOST_CHECK(client.isUsable() == true);
}

BOOST_AUTO_TEST_CASE(client_server_crosstest)
{
    TcpServer server;
    TcpClient client;
    Buffer rBuffClient, wBuffClient,
           rBuffServer, wBuffServer;

    //initiate connection
    server.listen("127.0.0.1", 4444);
    client.connect("127.0.0.1", 4444);
    BufferedTcpSocket* serverClient = server.accept();
    BOOST_CHECK(serverClient->isUsable() == true);

    //create and set buffer
    client.setBuffer(&rBuffClient, &wBuffClient);
    serverClient->setBuffer(&rBuffServer, &wBuffServer);
    
    //check client sending
    wBuffClient << (uint8_t) 'a' << (uint8_t) 'b';
    client.processBytes(false, true);
    serverClient->processBytes(true, false);
    uint8_t c;
    rBuffServer >> c;
    BOOST_CHECK(c == 'a');
    rBuffServer >> c;
    BOOST_CHECK(c == 'b');

    //check server sending
    wBuffServer << (uint8_t) 'c' << (uint8_t) 'd';
    serverClient->processBytes(false, true);
    client.processBytes(true, false);
    rBuffClient >> c;
    BOOST_CHECK(c == 'c');
    rBuffClient >> c;
    BOOST_CHECK(c == 'd');

    //cleanup
    delete serverClient;
}

BOOST_AUTO_TEST_SUITE_END()
