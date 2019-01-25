#include "parser.h"
#include "parser.hpp"
#include <cstdio>
#include "ServerConfigSection.h"

void yyerror (char const *s) {
    fprintf (stderr, "%s\n", s);
}

parser_context* parse()
{
    parser_context* ctx = new parser_context;
    ctx->server = new ServerConfigSection();
    ctx->current = NULL;
    yyparse(ctx);
    return ctx;
}
