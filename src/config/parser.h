#ifndef PARSER_H
#define PARSER_H
#include "ConfigSection.h"

union parser_data {
    int int_val;
    char* char_val;
};

struct parser_context{
    ConfigSection* server;
    ConfigSection* current;
};

parser_context* parse();
void yyerror (parser_context* ctx, char const *);
#endif
