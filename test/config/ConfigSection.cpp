#include "config/ServerConfigSection.h"
#include "config/ConfigElementNotFoundException.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(configSection)
BOOST_AUTO_TEST_CASE(basic_test)
{
    ServerConfigSection s;
    BOOST_CHECK(s["port"].get() == "49");
    s["port"] = "42";
    BOOST_CHECK(s["port"].get() == "42");
    BOOST_CHECK(s["listen"].get() == "");
    s["listen"] = "0.0.0.0";
    BOOST_CHECK(s["listen"].get() == "0.0.0.0");
}

BOOST_AUTO_TEST_CASE(check_unknow_key)
{
    ServerConfigSection s;
    BOOST_CHECK_THROW(s["invalid"] = "42", ConfigElementNotFoundException);
}
BOOST_AUTO_TEST_SUITE_END()
