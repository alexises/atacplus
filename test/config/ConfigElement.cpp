#include "config/ConfigElement.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(fixedLengthString)
BOOST_AUTO_TEST_CASE(basic_test)
{
    ConfigElement a("a", "a", true);
    ConfigElement b("b", "", false);
    ConfigElement c("c", "", true);

    BOOST_CHECK(a.isValid());
    BOOST_CHECK(b.isValid());
    BOOST_CHECK(!c.isValid());
}

BOOST_AUTO_TEST_SUITE_END()
