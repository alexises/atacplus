#include "network/crypto.h"
#include "network/TacacsPacketHeader.h"
#include "network/Buffer.h"
#include "network/FixedLengthString.h"
#include <boost/test/unit_test.hpp>
#include <cstring>

BOOST_AUTO_TEST_SUITE(crypto)
const uint8_t datachunk1[] = "\x00\x01\x02\x03"
                             "\x04\x05\x06\x07"
                             "\x08\x09\x0a\x0b"
                             "\x0c\x0d\x0e\x0f";
const uint8_t datachunk2[] = "\x00\x01\x02\x03"
                             "\x04\x05\x06\x07"
                             "\x08\x09\x0a\x0b"
                             "\x0c\x0d\x0e\xff"
                             "\x10\x11\x12\x13"
                             "\x14\x15\x16\x17"
                             "\x18\x19\x1a\x1b"
                             "\x1c\x1d\x1e\x1f";
FixedLengthString test("test", 4);
FixedLengthString notest("notest", 6);

BOOST_AUTO_TEST_CASE( small_decode_encode )
{
    Buffer bchk1 = Buffer(datachunk1, 16);
    Buffer bchk2 = Buffer(datachunk2, 32);

    encodeTacacsPacket(bchk1, 16, &test, 1, 1, TACACS_MAJOR + TACACS_MINOR_ONE);
    encodeTacacsPacket(bchk2, 32, &test, 1, 1, TACACS_MAJOR + TACACS_MINOR_ONE);
    encodeTacacsPacket(bchk1, 16, &test, 1, 1, TACACS_MAJOR + TACACS_MINOR_ONE);
    encodeTacacsPacket(bchk2, 32, &test, 1, 1, TACACS_MAJOR + TACACS_MINOR_ONE);

    /**
     * we don't access normaly to the elem
     *
     * Due to the know implementation of Buffer we will get the first index 
     * with the operator[] method
     */
    BOOST_CHECK(memcmp(datachunk1, &bchk1[0], 16) == 0);
    BOOST_CHECK(memcmp(datachunk2, &bchk2[0], 32) == 0);
}

BOOST_AUTO_TEST_CASE( check_unfinished_chunk )
{
    Buffer bchk2(datachunk2, 24);
    encodeTacacsPacket(bchk2, 24, &test, 1, 1, TACACS_MAJOR + TACACS_MINOR_ONE);
    encodeTacacsPacket(bchk2, 24, &test, 1, 1, TACACS_MAJOR + TACACS_MINOR_ONE);
    BOOST_CHECK(memcmp(datachunk2, &bchk2[0], 24) == 0);
}

BOOST_AUTO_TEST_CASE( check_multiple_decoding_fail )
{
    Buffer bchk2(datachunk2, 32);
    Buffer bchk3(datachunk2, 32);
    Buffer bchk4(datachunk2, 32);
    Buffer bchk5(datachunk2, 32);
    encodeTacacsPacket(bchk2, 32, &test, 1, 1, TACACS_MAJOR + TACACS_MINOR_ONE);
    encodeTacacsPacket(bchk2, 32, &notest, 1, 1, TACACS_MAJOR + TACACS_MINOR_ONE);

    encodeTacacsPacket(bchk3, 32, &test, 1, 1, TACACS_MAJOR + TACACS_MINOR_DEFAULT);
    encodeTacacsPacket(bchk4, 32, &test, 2, 1, TACACS_MAJOR + TACACS_MINOR_ONE);
    encodeTacacsPacket(bchk5, 32, &test, 1, 2, TACACS_MAJOR + TACACS_MINOR_ONE);
    BOOST_CHECK(memcmp(datachunk2, &bchk2[0], 32) != 0);
    BOOST_CHECK(memcmp(datachunk2, &bchk3[0], 32) != 0);
    BOOST_CHECK(memcmp(datachunk2, &bchk4[0], 32) != 0);
    BOOST_CHECK(memcmp(datachunk2, &bchk5[0], 32) != 0);
}

BOOST_AUTO_TEST_SUITE_END()
