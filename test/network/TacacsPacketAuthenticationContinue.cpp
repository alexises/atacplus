#include <boost/test/unit_test.hpp>

#include "network/Buffer.h"
#include "network/TacacsPacketAuthenticationContinue.h"
#include "network/DecodingException.h"

BOOST_AUTO_TEST_SUITE(tacacsPacketAuthenticationContinue)

BOOST_AUTO_TEST_CASE(basic_decode)
{
    uint8_t* a = (uint8_t*) "\x00\x00\x00\x00"
                            "\x01";
    Buffer aa(a, 8);
    TacacsPacketAuthenticationContinue* obj = TacacsPacketAuthenticationContinue::decode(aa);
    BOOST_CHECK(obj->getFlags() == AuthenticationContinueFlags::ContinueAbort);
    delete obj;
}

BOOST_AUTO_TEST_CASE(decoding_fail)
{

    uint8_t* a = (uint8_t*) "\x00\x00\x00\x00" //bad flags
                            "\x02";
    uint8_t* b = (uint8_t*) "\x01\x0f\x01\x00" //bad total size
                            "\x01";
    uint8_t* c = (uint8_t*) "\x00\x00\x00\x00"; //bad min size
    Buffer aa(a, 5);
    Buffer bb(b, 5);
    Buffer cc(c, 4);

    BOOST_CHECK_THROW(TacacsPacketAuthenticationContinue::decode(aa), DecodingException);
    BOOST_CHECK_THROW(TacacsPacketAuthenticationContinue::decode(bb), DecodingException);
    BOOST_CHECK_THROW(TacacsPacketAuthenticationContinue::decode(cc), DecodingException);
}

BOOST_AUTO_TEST_CASE(variable_parameter_check)
{
    uint8_t* a = (uint8_t*) "\x00\x04\x00\x03"
                            "\x00"
                            "AAAA"
                            "BBB";
    Buffer aa(a, 12);
    FixedLengthString userMsgStr("AAAA", 4);
    FixedLengthString dataStr("BBB", 3);

    TacacsPacketAuthenticationContinue* obj = TacacsPacketAuthenticationContinue::decode(aa);
    BOOST_CHECK(obj->getSize() == 12);
    FixedLengthString *userMsg = obj->getUserMsg();
    FixedLengthString *data = obj->getData();

    BOOST_CHECK(*userMsg == userMsgStr);
    BOOST_CHECK(*data == dataStr);
}

BOOST_AUTO_TEST_CASE(test_encoding)
{
    FixedLengthString* fUserMsg = new FixedLengthString("AAAA", 4);
    FixedLengthString* fData = new FixedLengthString("BBB", 3);
    TacacsPacketAuthenticationContinue packet(fUserMsg, fData, 
                        AuthenticationContinueFlags::NoFlags);
    char result[] = "\x00\x04\x00\x03"
                    "\x00"
                    "AAAA"
                    "BBB";

    Buffer bOut;
    FixedLengthString resultStr(result, 12);
    FixedLengthString packetStr(12);
    packet.encode(bOut);
    bOut >> packetStr;

    BOOST_CHECK(resultStr == packetStr);
}

BOOST_AUTO_TEST_SUITE_END()
