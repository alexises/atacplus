#include "parser.h"
#include <cstdio>

void yyerror(yyscan_t scanner, ParserContext* ctx, char const *s) {
    fprintf (stderr, "%s\n", s);
}
