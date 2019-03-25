#include <boost/test/unit_test.hpp>

#include "network/Buffer.h"
#include "network/TacacsPacketAuthenticationStart.h"
#include "network/DecodingException.h"
#include "network/TacacsPacketContext.h"
#include "network/BufferExaustionException.h"

BOOST_AUTO_TEST_SUITE(tacacsPacketAuthenticationStart)

BOOST_AUTO_TEST_CASE(basic_decode)
{
    TacacsPacketContext context(TacacsConnectionType::Server);
    context.setDecodeHeader(false);
    uint8_t* a = (uint8_t*) "\x01\x0f\x01\x01"
                            "\x00\x00\x00\x00";
    Buffer aa(a, 8);
    TacacsPacketAuthenticationStart obj(&context, aa);
    BOOST_CHECK(obj.getAction() == TacacsAuthenticationAction::Login);
    BOOST_CHECK(obj.getPrivLvl() == 15);
    BOOST_CHECK(obj.getAuthenType() == TacacsAuthenticationType::Ascii);
    BOOST_CHECK(obj.getService() == TacacsAuthenticationService::Login);
    BOOST_CHECK(obj.getUser()->getSize() == 0);
    BOOST_CHECK(obj.getPort()->getSize() == 0);
    BOOST_CHECK(obj.getRemoteAddr()->getSize() == 0);
    BOOST_CHECK(obj.getData()->getSize() == 0);
    BOOST_CHECK(obj.getSize() == 8);
}

BOOST_AUTO_TEST_CASE(decoding_fail)
{
    TacacsPacketContext context(TacacsConnectionType::Server);
    context.setDecodeHeader(false);
    uint8_t* a = (uint8_t*) "\x05\x0f\x01\x01" //bad action
                            "\x00\x00\x00\x00";
    uint8_t* b = (uint8_t*) "\x01\x10\x01\x01" //bad privLvl
                            "\x00\x00\x00\x00";
    uint8_t* c = (uint8_t*) "\x01\x0f\x0f\x01" //bad authenType
                            "\x00\x00\x00\x00";
    uint8_t* d = (uint8_t*) "\x01\x0f\x01\x10" //bad service
                            "\x00\x00\x00\x00";
    uint8_t* e = (uint8_t*) "\x01\x0f\x01\x01" //bad total size
                            "\x01\x01\x01\x01";
    uint8_t* f = (uint8_t*) "\x01\x0f\x01\x01"; //bad min size
    Buffer aa(a, 8);
    Buffer bb(b, 8);
    Buffer cc(c, 8);
    Buffer dd(d, 8);
    Buffer ee(e, 8);
    Buffer ff(f, 4);

    BOOST_CHECK_THROW(new TacacsPacketAuthenticationStart(&context, aa), DecodingException);
    BOOST_CHECK_THROW(new TacacsPacketAuthenticationStart(&context, bb), DecodingException);
    BOOST_CHECK_THROW(new TacacsPacketAuthenticationStart(&context, cc), DecodingException);
    BOOST_CHECK_THROW(new TacacsPacketAuthenticationStart(&context, dd), DecodingException);
    BOOST_CHECK_THROW(new TacacsPacketAuthenticationStart(&context, ee), BufferExaustionException);
    BOOST_CHECK_THROW(new TacacsPacketAuthenticationStart(&context, ff), BufferExaustionException);
}

BOOST_AUTO_TEST_CASE(variable_parameter_check)
{
    TacacsPacketContext context(TacacsConnectionType::Server);
    context.setDecodeHeader(false);
    uint8_t* a = (uint8_t*) "\x01\x0f\x01\x01"
                            "\x01\x02\x03\x04"
                            "ABBC"
                            "CCDD"
                            "DD";
    Buffer aa(a, 18);
    FixedLengthString userStr("A", 1);
    FixedLengthString portStr("BB", 2);
    FixedLengthString remoteAddrStr("CCC", 3);
    FixedLengthString dataStr("DDDD", 4);

    TacacsPacketAuthenticationStart obj(&context, aa);
    BOOST_CHECK(obj.getSize() == 18);
    FixedLengthString *user = obj.getUser();
    FixedLengthString *port = obj.getPort();
    FixedLengthString *remoteAddr = obj.getRemoteAddr();
    FixedLengthString *data = obj.getData();

    BOOST_CHECK(*user == userStr);
    BOOST_CHECK(*port == portStr);
    BOOST_CHECK(*remoteAddr == remoteAddrStr);
    BOOST_CHECK(*data == dataStr);
}

BOOST_AUTO_TEST_CASE(test_encoding)
{
    TacacsPacketContext context(TacacsConnectionType::Server);
    context.setDecodeHeader(false);
    FixedLengthString* fA = new FixedLengthString("A", 1);
    FixedLengthString* fB = new FixedLengthString("BB", 2);
    FixedLengthString* fC = new FixedLengthString("CCC", 3);
    FixedLengthString* fD = new FixedLengthString("DDDD", 4);
    TacacsPacketAuthenticationStart packet(&context, (uint8_t) 1, (uint8_t) 15, (uint8_t) 1, (uint8_t) 1,
                                    fA, fB, fC, fD);
    char result[] = "\x01\x0f\x01\x01"
                    "\x01\x02\x03\x04"
                    "ABBC"
                    "CCDD"
                    "DD";
    Buffer bOut;
    FixedLengthString resultStr(result, 18);
    FixedLengthString packetStr(18);
    packet.encode(bOut);
    bOut >> packetStr;

    BOOST_CHECK(resultStr == packetStr);
}

BOOST_AUTO_TEST_SUITE_END()
