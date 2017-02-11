#include "network/crypto.h"
#include "network/TacacsPacketHeader.h"

#define BOOST_TEST_MODULE TacacsPacketHeader
#include <boost/test/unit_test.hpp>
#include <cstring>
const unsigned char datachunk1[] = "\x00\x01\x02\x03"
                                   "\x04\x05\x06\x07"
                                   "\x08\x09\x0a\x0b"
		    	           "\x0c\x0d\x0e\x0f";
const unsigned char datachunk2[] = "\x00\x01\x02\x03"
                                   "\x04\x05\x06\x07"
                                   "\x08\x09\x0a\x0b"
                                   "\x0c\x0d\x0e\xff"
				   "\x10\x11\x12\x13"
				   "\x14\x15\x16\x17"
				   "\x18\x19\x1a\x1b"
				   "\x1c\x1d\x1e\x1f";

BOOST_AUTO_TEST_CASE( small_decode_encode )
{
    unsigned char* encoded1 = encodeTacacsPacket(datachunk1, 16, "test",
		                        1, 1, TACACS_MAJOR + TACACS_MINOR_ONE);
    unsigned char* encoded2 = encodeTacacsPacket(datachunk2, 32, "test",
		                        1, 1, TACACS_MAJOR + TACACS_MINOR_ONE);
    unsigned char* decoded1 = encodeTacacsPacket(encoded1, 16, "test",
		                        1, 1, TACACS_MAJOR + TACACS_MINOR_ONE);
    unsigned char* decoded2 = encodeTacacsPacket(encoded2, 32, "test",
		                        1, 1, TACACS_MAJOR + TACACS_MINOR_ONE);

    BOOST_CHECK(memcmp(datachunk1, decoded1, 16) == 0);
    BOOST_CHECK(memcmp(datachunk2, decoded2, 32) == 0);
    delete[] encoded1;
    delete[] encoded2;
    delete[] decoded1;
    delete[] decoded2;
}

BOOST_AUTO_TEST_CASE( check_unfinished_chunk )
{
    unsigned char* encoded2 = encodeTacacsPacket(datachunk2, 24, "test",
                                        1, 1, TACACS_MAJOR + TACACS_MINOR_ONE);
    unsigned char* decoded2 = encodeTacacsPacket(encoded2, 24, "test",
                                        1, 1, TACACS_MAJOR + TACACS_MINOR_ONE);
    BOOST_CHECK(memcmp(datachunk2, decoded2, 24) == 0);
    delete[] encoded2;
    delete[] decoded2;
}

BOOST_AUTO_TEST_CASE( check_multiple_decoding_fail )
{
    unsigned char* encoded2 = encodeTacacsPacket(datachunk2, 32, "test",
                                        1, 1, TACACS_MAJOR + TACACS_MINOR_ONE);
    unsigned char* decoded1 = encodeTacacsPacket(encoded2, 32, "notest",
                                        1, 1, TACACS_MAJOR + TACACS_MINOR_ONE);
    unsigned char* decoded2 = encodeTacacsPacket(encoded2, 32, "test",
                                        1, 1, TACACS_MAJOR + TACACS_MINOR_DEFAULT);
    unsigned char* decoded3 = encodeTacacsPacket(encoded2, 32, "test",
                                        2, 1, TACACS_MAJOR + TACACS_MINOR_ONE);
    unsigned char* decoded4 = encodeTacacsPacket(encoded2, 32, "test",
                                        1, 2, TACACS_MAJOR + TACACS_MINOR_ONE);
    BOOST_CHECK(memcmp(datachunk2, decoded1, 32) != 0);
    BOOST_CHECK(memcmp(datachunk2, decoded2, 32) != 0);
    BOOST_CHECK(memcmp(datachunk2, decoded3, 32) != 0);
    BOOST_CHECK(memcmp(datachunk2, decoded4, 32) != 0);
    delete[] decoded1;
    delete[] decoded2;
    delete[] decoded3;
    delete[] decoded4;
    delete[] encoded2;
}
