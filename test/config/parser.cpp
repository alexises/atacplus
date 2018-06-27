#include "config/parser.h"
#include "parser.hpp"
#include "scanner.h"
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(parser_test)
BOOST_AUTO_TEST_CASE(basic_test)
{
    yy_scan_string("server");
    BOOST_CHECK(yylex() == SERVER);
    BOOST_CHECK(yylex() == 0);
    yylex_destroy();
}

BOOST_AUTO_TEST_CASE(space_test)
{
    yy_scan_string("{ }");
    BOOST_CHECK(yylex() == OPEN_BRACKET);
    BOOST_CHECK(yylex() == CLOSE_BRACKET);
    BOOST_CHECK(yylex() == 0);
    yylex_destroy();
}

BOOST_AUTO_TEST_CASE(string_test)
{
    yy_scan_string("'foo' \"bar\""); 
    BOOST_CHECK(yylex() == STRING);
    BOOST_CHECK(std::string("foo") == yylval.char_val);
    delete[] yylval.char_val;
    BOOST_CHECK(yylex() == STRING);
    BOOST_CHECK(std::string("bar") == yylval.char_val);
    delete[] yylval.char_val;
    BOOST_CHECK(yylex() == 0);
    yylex_destroy();
}

BOOST_AUTO_TEST_CASE(escaped_string_test)
{
    yy_scan_string("'f\\'oo' \"b\\\"ar\""); 
    BOOST_CHECK(yylex() == STRING);
    BOOST_CHECK(std::string("f'oo") == yylval.char_val);
    delete[] yylval.char_val;
    BOOST_CHECK(yylex() == STRING);
    BOOST_CHECK(std::string("b\"ar") == yylval.char_val);
    delete[] yylval.char_val;
    BOOST_CHECK(yylex() == 0);
    yylex_destroy();
}

BOOST_AUTO_TEST_CASE(multiple_escaped_string)
{
    yy_scan_string("'f\\'\\\\oo' \"b\\\"a\\\\r\""); 
    BOOST_CHECK(yylex() == STRING);
    BOOST_CHECK(std::string("f'\\oo") == yylval.char_val);
    delete[] yylval.char_val;
    BOOST_CHECK(yylex() == STRING);
    BOOST_CHECK(std::string("b\"a\\r") == yylval.char_val);
    delete[] yylval.char_val;
    BOOST_CHECK(yylex() == 0);
    yylex_destroy();
}

BOOST_AUTO_TEST_CASE(test_param_name)
{
    yy_scan_string("server client"); 
    BOOST_CHECK(yylex() == SERVER);
    BOOST_CHECK(yylex() == CONFIG_NAME);
    BOOST_CHECK(std::string("client") == yylval.char_val);
    yylex_destroy();
}

BOOST_AUTO_TEST_SUITE_END()
