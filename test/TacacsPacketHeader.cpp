#include "network/TacacsPacketHeader.h"
#include "network/EncodingException.h"
#include "network/DecodingException.h"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TacacsPacketHeader
#include <boost/test/unit_test.hpp>
#include <cstring>

BOOST_AUTO_TEST_CASE( check_basic_auth_encode )
{
    const unsigned char data[] = "\xc1\x01\x01\x01"
                                 "\x00\x00\x00\x01"
                                 "\x00\x00\x00\x00";
    unsigned char buff[12];
    TacacsPacketHeader h(0xc1, 0x01, 1, 0x01, 1, 0);
    int size = h.encode(buff, 12);

    BOOST_CHECK(size == 12);
    BOOST_CHECK(memcmp(data, buff, 12) == 0);
}

BOOST_AUTO_TEST_CASE( check_basic_auth_decode )
{
    const unsigned char data[] = "\xc1\x01\x01\x01"
                                 "\x00\x00\x00\x01"
                                 "\x00\x00\x00\x00";
    TacacsPacketHeader* h = TacacsPacketHeader::decode(data, 12);
    BOOST_CHECK( h->getMajorVersion() == 12 );
    BOOST_CHECK( h->getMinorVersion() == 1 );
    BOOST_CHECK( h->getPacketType() == 1 );
    BOOST_CHECK( h->getSeqNo() == 1 );
    BOOST_CHECK( h->getFlags() == 1 );
    BOOST_CHECK( h->getSessionId() == 1 );
    BOOST_CHECK( h->getLength() == 0 );
    delete h;
}

BOOST_AUTO_TEST_CASE( check_valid_args )
{
    const unsigned char data1[] = "\xc0\x01\x01\x01" // check flags
                                  "\x00\x00\x00\x01"
                                  "\x00\x00\x00\x00";
    const unsigned char data2[] = "\xc1\x02\x01\x01" // check authorization
                                  "\x00\x00\x00\x01"
                                  "\x00\x00\x00\x00";
    const unsigned char data3[] = "\xc1\x03\x01\x01" // check accounting
                                  "\x00\x00\x00\x00"
                                  "\x00\x00\x00\x00";
    const unsigned char data4[] = "\xc1\x03\x01\x00" // check flags
                                  "\x00\x00\x00\x01"
                                  "\x00\x00\x00\x00";
    TacacsPacketHeader* h;
    h = TacacsPacketHeader::decode(data1, 12, "test");
    delete h;
    h = TacacsPacketHeader::decode(data2, 12, "test");
    delete h;
    h = TacacsPacketHeader::decode(data3, 12, "test");
    delete h;
    h = TacacsPacketHeader::decode(data4, 12, "test");
    delete h;
}

BOOST_AUTO_TEST_CASE( check_invalid_expression )
{
    const unsigned char data1[] = "\xd0\x01\x01\x01" // bad major version
                                  "\x00\x00\x00\x01"
                                  "\x00\x00\x00\x00";
    const unsigned char data2[] = "\xc4\x01\x01\x01" // bad minor version
                                  "\x00\x00\x00\x01"
                                  "\x00\x00\x00\x00";
    const unsigned char data3[] = "\xc1\x04\x01\x01" // bad packet type
                                  "\x00\x00\x00\x01"
                                  "\x00\x00\x00\x00";
    const unsigned char data4[] = "\xc1\x01\x01\xf0" // bad flags
                                  "\x00\x00\x00\x01"
                                  "\x00\x00\x00\x00";
    const unsigned char data5[] = "\xc1\x01\x01\x01" // bad size
	                          "\x00\x00\x00\x01"
				  "\x00\x00\x00\x0c";
    BOOST_CHECK_THROW(TacacsPacketHeader::decode(data1, 12), DecodingException);
    BOOST_CHECK_THROW(TacacsPacketHeader::decode(data2, 12), DecodingException);
    BOOST_CHECK_THROW(TacacsPacketHeader::decode(data3, 12), DecodingException);
    BOOST_CHECK_THROW(TacacsPacketHeader::decode(data4, 12), DecodingException);
    BOOST_CHECK_THROW(TacacsPacketHeader::decode(data5, 12), DecodingException);
}

BOOST_AUTO_TEST_CASE( check_invalid_encoding )
{
   TacacsPacketHeader h(0xc1, 0x01, 1, 0x01, 1, 12);
   unsigned char buff[5];
   BOOST_CHECK_THROW(h.encode(buff, 5), EncodingException);
}


