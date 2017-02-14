#include "network/FixedLengthString.h"
#include "network/PreconditionFailException.h"

#include <boost/test/unit_test.hpp>
#include <cstring>

BOOST_AUTO_TEST_SUITE(fixedLengthString)
BOOST_AUTO_TEST_CASE(check_size)
{
    FixedLengthString f("testtest", 8);
    FixedLengthString g("testtest", 4);

    BOOST_CHECK(f.getSize() == 8);
    BOOST_CHECK(g.getSize() == 4);
}

BOOST_AUTO_TEST_CASE(check_access)
{
    const char* compare = "testtest";
    FixedLengthString f("testtest", 8);
    for (int i = 0; i < f.getSize(); ++i)
    {
        BOOST_CHECK(compare[i] == f[i]);
    }
}

BOOST_AUTO_TEST_CASE(check_replace)
{
    FixedLengthString f("testtest", 8);
    FixedLengthString g("aaaaaaaa", 8);
    for (int i = 0; i < f.getSize(); ++i)
    {
	f[i] = g[i];
    }
    BOOST_CHECK(f.getSize() == 8);
    for (int j = 0; j < f.getSize(); ++j)
    {
        BOOST_CHECK(f[j] == g[j]);
    }
    BOOST_CHECK_THROW(f[10], PreconditionFailException);
}

BOOST_AUTO_TEST_CASE(check_copy)
{
    FixedLengthString f("testtest", 8);
    FixedLengthString g(f);

    BOOST_CHECK(f.getSize() == g.getSize());
}

BOOST_AUTO_TEST_CASE(check_convert)
{
    FixedLengthString f("fo\0", 3);
    std::string s = f.toString();
    for (int i = 0; i < f.getSize(); ++i)
    {
	BOOST_CHECK(f[i] == s[i]);
    }
}

BOOST_AUTO_TEST_SUITE_END()
