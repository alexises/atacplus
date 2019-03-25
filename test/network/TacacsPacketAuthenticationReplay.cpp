#include <boost/test/unit_test.hpp>

#include "network/Buffer.h"
#include "network/TacacsPacketAuthenticationReplay.h"
#include "network/DecodingException.h"
#include "network/BufferExaustionException.h"

BOOST_AUTO_TEST_SUITE(tacacsPacketAuthenticationReplay)

BOOST_AUTO_TEST_CASE(basic_decode)
{
    TacacsPacketContext context(TacacsConnectionType::Server);
    context.setDecodeHeader(false);
    uint8_t* a = (uint8_t*) "\x01\x00\x00\x00"
                            "\x00\x00";
    Buffer aa(a, 8);
    TacacsPacketAuthenticationReplay obj(&context, aa);
    BOOST_CHECK(obj.getStatus() == AuthenticationStatus::Pass);
    BOOST_CHECK(obj.getFlags() == 0);
    BOOST_CHECK(obj.getPromptMsg()->getSize() == 0);
    BOOST_CHECK(obj.getData()->getSize() == 0);
    BOOST_CHECK(obj.getSize() == 6);
}

BOOST_AUTO_TEST_CASE(decoding_fail)
{
    TacacsPacketContext context(TacacsConnectionType::Server);
    context.setDecodeHeader(false);
    uint8_t* a = (uint8_t*) "\xff\x00\x00\x00" //bad status
                            "\x00\x00";
    uint8_t* b = (uint8_t*) "\x01\x02\x00\x00" //bad flags
                            "\x00\x00";
    uint8_t* c = (uint8_t*) "\x01\x0f\x01\x00" //bad total size
                            "\x01\x00";
    uint8_t* d = (uint8_t*) "\x01\x00\x00\x00"; //bad min size
    Buffer aa(a, 6);
    Buffer bb(b, 6);
    Buffer cc(c, 6);
    Buffer dd(d, 4);

    BOOST_CHECK_THROW(new TacacsPacketAuthenticationReplay(&context, aa), DecodingException);
    BOOST_CHECK_THROW(new TacacsPacketAuthenticationReplay(&context, bb), DecodingException);
    BOOST_CHECK_THROW(new TacacsPacketAuthenticationReplay(&context, cc), BufferExaustionException);
    BOOST_CHECK_THROW(new TacacsPacketAuthenticationReplay(&context, dd), BufferExaustionException);
}

BOOST_AUTO_TEST_CASE(variable_parameter_check)
{
    TacacsPacketContext context(TacacsConnectionType::Server);
    context.setDecodeHeader(false);
    uint8_t* a = (uint8_t*) "\x05\x01\x00\x04"
                            "\x00\x03"
                            "AAAA"
                            "BBB";
    Buffer aa(a, 13);
    FixedLengthString promptMsgStr("AAAA", 4);
    FixedLengthString dataStr("BBB", 3);

    TacacsPacketAuthenticationReplay obj(&context, aa);
    BOOST_CHECK(obj.getSize() == 13);
    FixedLengthString *promptMsg = obj.getPromptMsg();
    FixedLengthString *data = obj.getData();

    BOOST_CHECK(*promptMsg == promptMsgStr);
    BOOST_CHECK(*data == dataStr);
}

BOOST_AUTO_TEST_CASE(test_encoding)
{
    TacacsPacketContext context(TacacsConnectionType::Server);
    context.setDecodeHeader(false);
    FixedLengthString* fPromptMsg = new FixedLengthString("AAAA", 4);
    FixedLengthString* fData = new FixedLengthString("BBB", 3);
    TacacsPacketAuthenticationReplay packet(&context, (uint8_t) 5, (uint8_t) 1,
                                    fPromptMsg, fData);
    char result[] = "\x05\x01\x00\x04"
                    "\x00\x03"
                    "AAAA"
                    "BBB";

    Buffer bOut;
    FixedLengthString resultStr(result, 13);
    FixedLengthString packetStr(13);
    packet.encode(bOut);
    bOut >> packetStr;

    BOOST_CHECK(resultStr == packetStr);
}

BOOST_AUTO_TEST_SUITE_END()
