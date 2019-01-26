#ifndef PARSER_H
#define PARSER_H
#include "ParserContext.h"

union parser_data {
    int int_val;
    char* char_val;
};

typedef void* yyscan_t;

void yyerror(yyscan_t scanner, ParserContext* ctx, char const *s);
#endif
