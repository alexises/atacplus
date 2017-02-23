#include "network/TacacsPacketHeader.h"
#include "network/EncodingException.h"
#include "network/DecodingException.h"
#include "network/Buffer.h"

#include <boost/test/unit_test.hpp>
#include <cstring>

BOOST_AUTO_TEST_SUITE(tacacsPacketHeader)
BOOST_AUTO_TEST_CASE( check_basic_auth_encode )
{
    const uint8_t data[] = "\xc1\x01\x01\x01"
                           "\x00\x00\x00\x01"
                           "\x00\x00\x00\x00";
    uint8_t buff[12];
    TacacsPacketHeader h(0xc1, 0x01, 1, 0x01, 1, 0);
    int size = h.encode(buff, 12);

    BOOST_CHECK(size == 12);
    BOOST_CHECK(memcmp(data, buff, 12) == 0);
}

BOOST_AUTO_TEST_CASE( check_basic_auth_decode )
{
    const uint8_t data[] = "\xc1\x01\x01\x01"
                           "\x00\x00\x00\x01"
                           "\x00\x00\x00\x00";
    Buffer bData(data, 12);
    TacacsPacketHeader* h = TacacsPacketHeader::decode(bData);
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
    const uint8_t data1[] = "\xc0\x01\x01\x01" // check flags
                            "\x00\x00\x00\x01"
                            "\x00\x00\x00\x00";
    const uint8_t data2[] = "\xc1\x02\x01\x01" // check authorization
                            "\x00\x00\x00\x01"
                            "\x00\x00\x00\x00";
    const uint8_t data3[] = "\xc1\x03\x01\x01" // check accounting
                            "\x00\x00\x00\x00"
                            "\x00\x00\x00\x00";
    const uint8_t data4[] = "\xc1\x03\x01\x00" // check flags
                            "\x00\x00\x00\x01"
                            "\x00\x00\x00\x00";
    Buffer bData1(data1, 12);
    Buffer bData2(data2, 12);
    Buffer bData3(data3, 12);
    Buffer bData4(data4, 12);
    TacacsPacketHeader* h;
    h = TacacsPacketHeader::decode(bData1);
    delete h;
    h = TacacsPacketHeader::decode(bData2);
    delete h;
    h = TacacsPacketHeader::decode(bData3);
    delete h;
    h = TacacsPacketHeader::decode(bData4);
    delete h;
}

BOOST_AUTO_TEST_CASE( check_invalid_expression )
{
    const uint8_t data1[] = "\xd0\x01\x01\x01" // bad major version
                            "\x00\x00\x00\x01"
                            "\x00\x00\x00\x00";
    const uint8_t data2[] = "\xc4\x01\x01\x01" // bad minor version
                            "\x00\x00\x00\x01"
                            "\x00\x00\x00\x00";
    const uint8_t data3[] = "\xc1\x04\x01\x01" // bad packet type
                            "\x00\x00\x00\x01"
                            "\x00\x00\x00\x00";
    const uint8_t data4[] = "\xc1\x01\x01\xf0" // bad flags
                            "\x00\x00\x00\x01"
                            "\x00\x00\x00\x00";
    //const uint8_t data5[] = "\xc1\x01\x01\x01" // bad size
    //                        "\x00\x00\x00\x01"
    //                        "\x00\x00\x00\x0c";
    //test useless now (the size it check on sub packet)
    Buffer bData1(data1, 12);
    Buffer bData2(data2, 12);
    Buffer bData3(data3, 12);
    Buffer bData4(data4, 12);
    //Buffer bData5(data5, 12);
    BOOST_CHECK_THROW(TacacsPacketHeader::decode(bData1), DecodingException);
    BOOST_CHECK_THROW(TacacsPacketHeader::decode(bData2), DecodingException);
    BOOST_CHECK_THROW(TacacsPacketHeader::decode(bData3), DecodingException);
    BOOST_CHECK_THROW(TacacsPacketHeader::decode(bData4), DecodingException);
    //BOOST_CHECK_THROW(TacacsPacketHeader::decode(bData5), DecodingException);
}

BOOST_AUTO_TEST_CASE( check_invalid_encoding )
{
   TacacsPacketHeader h(0xc1, 0x01, 1, 0x01, 1, 12);
   uint8_t buff[5];
   BOOST_CHECK_THROW(h.encode(buff, 5), EncodingException);
}

BOOST_AUTO_TEST_SUITE_END()
