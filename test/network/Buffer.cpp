#include <boost/test/unit_test.hpp>
#include <network/Buffer.h>
#include <network/PreconditionFailException.h>

BOOST_AUTO_TEST_SUITE(BufferTest)
BOOST_AUTO_TEST_CASE(check_basic_read)
{
    Buffer a((uint8_t *) "\x00", 1);
    Buffer b((uint8_t *) "\x01", 1);
    Buffer c((uint8_t *) "\xff", 1);
    uint8_t aa = 0x99;
    uint8_t bb = 0x99;
    uint8_t cc = 0x99;
    a >> aa;
    b >> bb;
    c >> cc;
    BOOST_CHECK(aa == 0x00);
    BOOST_CHECK(bb == 0x01);
    BOOST_CHECK(cc == 0xff);
}

BOOST_AUTO_TEST_CASE(check_endianess)
{
    Buffer a((uint8_t *) "\x00\x01\x02\x03", 4);
    Buffer b((uint8_t *) "\x00\x01\x02\x03", 4);
    uint16_t aa;
    uint16_t ab;
    uint32_t bb;
    a >> aa;
    a >> ab;
    b >> bb;
    BOOST_CHECK(aa == 0x0100);
    BOOST_CHECK(ab == 0x0302);
    BOOST_CHECK(bb == 0x03020100);
}

BOOST_AUTO_TEST_CASE(test_write)
{
    Buffer b(8);
    BOOST_CHECK(b.availableRead() == 0);
    BOOST_CHECK(b.availableWrite() == 8);
    b.write((uint8_t *) "\x00\x01", 2);
    b.write((uint8_t *) "\x02\x03", 2);
    BOOST_CHECK(b.availableRead() == 4);
    BOOST_CHECK(b.availableWrite() == 4);
    uint32_t bb;
    b >> bb;
    BOOST_CHECK(bb == 0x03020100);
}

BOOST_AUTO_TEST_CASE(check_exception)
{
    Buffer b(1);
    uint8_t a;
    BOOST_CHECK_THROW(b >> a, PreconditionFailException);
    BOOST_CHECK_THROW(b.write((uint8_t *) "\00\01", 2), PreconditionFailException);
    b.write((uint8_t *) "\x00", 1);
    BOOST_CHECK_THROW(b.write((uint8_t *) "\00", 1), PreconditionFailException);
}

BOOST_AUTO_TEST_SUITE_END()
