#include "network/TacacsPacketHeader.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TacacsPacketHeader
#include <boost/test/unit_test.hpp>
#include <cstring>

BOOST_AUTO_TEST_CASE( check_basic_auth_encode )
{
    const char data[] = "\xc1\x01\x01\x01"
                        "\x00\x00\x00\x01"
                        "\x00\x00\x00\x0c";
    char buff[12];
    TacacsPacketHeader h(0xc1, 0x01, 1, 0x01, 1, 12);
    int size = h.encode(buff, 12);

    BOOST_CHECK(size == 12);
    BOOST_CHECK(strncmp(data, buff, 12) == 0);
}

BOOST_AUTO_TEST_CASE( check_basic_auth_decode )
{
    const char data[] = "\xc1\x01\x01\x01"
                        "\x00\x00\x00\x01"
                        "\x00\x00\x00\x0c";
    TacacsPacketHeader* h = TacacsPacketHeader::decode(data, 12);
    BOOST_CHECK( h->getMajorVersion() == 12 );
    BOOST_CHECK( h->getMinorVersion() == 1 );
    BOOST_CHECK( h->getPacketType() == 1 );
    BOOST_CHECK( h->getSeqNo() == 1 );
    BOOST_CHECK( h->getFlags() == 1 );
    BOOST_CHECK( h->getSessionId() == 1 );
    BOOST_CHECK( h->getLength() == 12 );
    delete h;
}

