#include "config/parser.h"
#include "parser.hpp"
#include "scanner.h"
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(parser_test)
BOOST_AUTO_TEST_CASE(basic_test)
{
    yyscan_t ctx;
    YYSTYPE out;
    yylex_init(&ctx);
    yy_scan_string("server", ctx);
    BOOST_CHECK(yylex(&out, ctx) == SERVER);
    BOOST_CHECK(yylex(&out, ctx) == 0);
    yylex_destroy(ctx);
}

BOOST_AUTO_TEST_CASE(space_test)
{
    yyscan_t ctx;
    YYSTYPE out;
    yylex_init(&ctx);
    yy_scan_string("{ }", ctx);
    BOOST_CHECK(yylex(&out, ctx) == OPEN_BRACKET);
    BOOST_CHECK(yylex(&out, ctx) == CLOSE_BRACKET);
    BOOST_CHECK(yylex(&out, ctx) == 0);
    yylex_destroy(ctx);
}

BOOST_AUTO_TEST_CASE(string_test)
{
    yyscan_t ctx;
    YYSTYPE out;
    yylex_init(&ctx);
    yy_scan_string("'foo' \"bar\"", ctx); 
    BOOST_CHECK(yylex(&out, ctx) == STRING);
    BOOST_CHECK(std::string("foo") == out.char_val);
    delete[] out.char_val;
    BOOST_CHECK(yylex(&out, ctx) == STRING);
    BOOST_CHECK(std::string("bar") == out.char_val);
    delete[] out.char_val;
    BOOST_CHECK(yylex(&out, ctx) == 0);
    yylex_destroy(ctx);
}

BOOST_AUTO_TEST_CASE(escaped_string_test)
{
    yyscan_t ctx;
    YYSTYPE out;
    yylex_init(&ctx);
    yy_scan_string("'f\\'oo' \"b\\\"ar\"", ctx); 
    BOOST_CHECK(yylex(&out, ctx) == STRING);
    BOOST_CHECK(std::string("f'oo") == out.char_val);
    delete[] out.char_val;
    BOOST_CHECK(yylex(&out, ctx) == STRING);
    BOOST_CHECK(std::string("b\"ar") == out.char_val);
    delete[] out.char_val;
    BOOST_CHECK(yylex(&out, ctx) == 0);
    yylex_destroy(ctx);
}

BOOST_AUTO_TEST_CASE(multiple_escaped_string)
{
    yyscan_t ctx;
    YYSTYPE out;
    yylex_init(&ctx);
    yy_scan_string("'f\\'\\\\oo' \"b\\\"a\\\\r\"", ctx); 
    BOOST_CHECK(yylex(&out, ctx) == STRING);
    BOOST_CHECK(std::string("f'\\oo") == out.char_val);
    delete[] out.char_val;
    BOOST_CHECK(yylex(&out, ctx) == STRING);
    BOOST_CHECK(std::string("b\"a\\r") == out.char_val);
    delete[] out.char_val;
    BOOST_CHECK(yylex(&out, ctx) == 0);
    yylex_destroy(ctx);
}

BOOST_AUTO_TEST_CASE(test_param_name)
{
    yyscan_t ctx;
    YYSTYPE out;
    yylex_init(&ctx);
    yy_scan_string("server client", ctx); 
    BOOST_CHECK(yylex(&out, ctx) == SERVER);
    BOOST_CHECK(yylex(&out, ctx) == CONFIG_NAME);
    BOOST_CHECK(std::string("client") == out.char_val);
    yylex_destroy(ctx);
}

BOOST_AUTO_TEST_SUITE_END()
