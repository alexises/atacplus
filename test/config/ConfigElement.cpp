#include "config/ConfigElement.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(configElement)
BOOST_AUTO_TEST_CASE(basic_test)
{
    ConfigElement a("a", "a", true);
    ConfigElement b("b", "", false);
    ConfigElement c("c", "", true);

    BOOST_CHECK(a.isValid());
    BOOST_CHECK(b.isValid());
    BOOST_CHECK(!c.isValid());
}

BOOST_AUTO_TEST_CASE(value_check)
{
    ConfigElement a("a", "", true);
    BOOST_CHECK(!a.isValid());
    BOOST_CHECK(a.get() == "");
    a = "a";
    BOOST_CHECK(a.isValid());
    BOOST_CHECK(a.get() == "a");
}

BOOST_AUTO_TEST_SUITE_END()
