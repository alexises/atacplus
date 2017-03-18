#include <boost/test/unit_test.hpp>

#include "network/Buffer.h"
#include "network/TacacsPacketAuthenticationStart.h"
#include "network/DecodingException.h"
#include "network/TacacsPacketContext.h"

BOOST_AUTO_TEST_SUITE(tacacsPacketWithHeader)
BOOST_AUTO_TEST_CASE(basic_encode_decode)
{
    TacacsPacketContext c(TacacsConnectionType::Server);
    Buffer out(2048);
    FixedLengthString* key = new FixedLengthString("test", 4);
    c.setKey(key);

    FixedLengthString* user = new FixedLengthString("test", 4);
    FixedLengthString* port = new FixedLengthString("foo", 3);
    FixedLengthString* remoteAddr = new FixedLengthString("127.0.0.1", 9);
    FixedLengthString* data = new FixedLengthString("bar", 3);
    TacacsPacketAuthenticationStart s(
        &c,
        TacacsAuthenticationAction::Login,
        TACACS_MAX_PRIV_LVL,
        TacacsAuthenticationType::Ascii,
        TacacsAuthenticationService::Login,
        user, port, remoteAddr, data
    );
    s.encode(out);
    TacacsPacketAuthenticationStart sOut(&c, out);
    TacacsPacketHeader* h = s.getHeader();
    TacacsPacketHeader* hOut = sOut.getHeader();

    BOOST_CHECK(h != NULL);
    BOOST_CHECK(hOut != NULL);
    BOOST_CHECK(h->getSize() == hOut->getSize());
    BOOST_CHECK(h->getType() == hOut->getType());
    BOOST_CHECK(h->getPacketType() == hOut->getPacketType());
    BOOST_CHECK(h->getPacketType() == TacacsPacketType::Authentication);
    BOOST_CHECK(h->getSeqNo() == hOut->getSeqNo());
    BOOST_CHECK(h->getSeqNo() == 0);
    BOOST_CHECK(h->getFlags() == hOut->getFlags());
    BOOST_CHECK(h->getSessionId() == hOut->getSessionId());
    BOOST_CHECK(h->getLength() == hOut->getLength());
    BOOST_CHECK(h->getLength() == s.getSize());
    BOOST_CHECK(s.getSize() == sOut.getSize());
    BOOST_CHECK(s.getAction() == sOut.getAction());
    BOOST_CHECK(s.getPrivLvl() == sOut.getPrivLvl());
    BOOST_CHECK(s.getAuthenType() == sOut.getAuthenType());
    BOOST_CHECK(*(s.getUser()) == *(sOut.getUser()));
    BOOST_CHECK(*(s.getPort()) == *(sOut.getPort()));
    BOOST_CHECK(*(s.getRemoteAddr()) == *(sOut.getRemoteAddr()));
    BOOST_CHECK(*(s.getData()) == *(sOut.getData()));
}

BOOST_AUTO_TEST_SUITE_END()

