#include "config/parser.h"
#include "parser.hpp"
#include "scanner.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(parser_test)
BOOST_AUTO_TEST_CASE(basic_test)
{
    yy_scan_string("server");
    yyparse();
}

BOOST_AUTO_TEST_SUITE_END()
