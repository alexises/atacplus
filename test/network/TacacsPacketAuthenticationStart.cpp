#include <boost/test/unit_test.hpp>

#include "network/Buffer.h"
#include "network/TacacsPacketAuthenticationStart.h"

BOOST_AUTO_TEST_SUITE(tacacsPacketAuthenticationStart)

BOOST_AUTO_TEST_CASE(basic_decode)
{
    uint8_t* a = (uint8_t*) "\x01\x0f\x01\x01"
                            "\x00\x00\x00\x00";
    Buffer aa(a, 8);
    TacacsPacketAuthenticationStart* obj = TacacsPacketAuthenticationStart::decode(aa);
    BOOST_CHECK(obj->getAction() == TacacsAuthenticationAction::Login);
    BOOST_CHECK(obj->getPrivLvl() == 15);
    BOOST_CHECK(obj->getAuthenType() == TacacsAuthenticationType::Ascii);
    BOOST_CHECK(obj->getService() == TacacsAuthenticationService::Login);
    BOOST_CHECK(obj->getUser()->getSize() == 0);
    BOOST_CHECK(obj->getPort()->getSize() == 0);
    BOOST_CHECK(obj->getRemoteAddr()->getSize() == 0);
    BOOST_CHECK(obj->getData()->getSize() == 0);
    BOOST_CHECK(obj->getSize() == 8);
}

BOOST_AUTO_TEST_SUITE_END()

