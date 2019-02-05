#include "config/parser.h"
#include "parser.hpp"
#include "scanner.h"
#include "config/ConfigElementNotFoundException.h"
#include <boost/test/unit_test.hpp>
#include <sstream>

BOOST_AUTO_TEST_SUITE(parser_test)
BOOST_AUTO_TEST_CASE(basic_test)
{
    yyscan_t ctx;
    YYSTYPE out;
    std::stringstream buff("server");
    yylex_init_extra(&buff, &ctx);
    BOOST_CHECK(yylex(&out, ctx) == SERVER);
    BOOST_CHECK(yylex(&out, ctx) == 0);
    yylex_destroy(ctx);
}

BOOST_AUTO_TEST_CASE(space_test)
{
    yyscan_t ctx;
    YYSTYPE out;
    std::stringstream buff("{ }");
    yylex_init_extra(&buff, &ctx);
    BOOST_CHECK(yylex(&out, ctx) == OPEN_BRACKET);
    BOOST_CHECK(yylex(&out, ctx) == CLOSE_BRACKET);
    BOOST_CHECK(yylex(&out, ctx) == 0);
    yylex_destroy(ctx);
}

BOOST_AUTO_TEST_CASE(string_test)
{
    yyscan_t ctx;
    YYSTYPE out;
    std::stringstream buff("'foo' \"bar\"");
    yylex_init_extra(&buff, &ctx);
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
    std::stringstream buff("'f\\'oo' \"b\\\"ar\"");
    yylex_init_extra(&buff, &ctx);
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
    std::stringstream buff("'f\\'\\\\oo' \"b\\\"a\\\\r\"");
    yylex_init_extra(&buff, &ctx);
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
    std::stringstream buff("server client");
    yylex_init_extra(&buff, &ctx);
    BOOST_CHECK(yylex(&out, ctx) == SERVER);
    BOOST_CHECK(yylex(&out, ctx) == CONFIG_NAME);
    BOOST_CHECK(std::string("client") == out.char_val);
    delete[] out.char_val;
    yylex_destroy(ctx);
}

BOOST_AUTO_TEST_CASE(test_parser)
{
    ParserContext parseCtx;
    char str[] = "server { \n"
               "  listen '1.2.3.4';\n"
               "  port '80';\n";
    std::stringstream buff(str);
    parseCtx.parse(buff);
}

BOOST_AUTO_TEST_CASE(test_parser_bad_param)
{
    ParserContext parseCtx;
    char str[] = "server { \n"
               "  bind '1.2.3.4';\n"
               "  port '80';\n"
               "}";
    std::stringstream buff(str);
    BOOST_CHECK_THROW(parseCtx.parse(buff), ConfigElementNotFoundException);
}
BOOST_AUTO_TEST_SUITE_END()
